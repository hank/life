<?php
  include_once("support.inc.php");
  include_once("rss_fetch.inc");

  if(!logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    $url = $_POST['url'];
    $url_hash = hash('sha256', $url);
    // Connect to database
    db_connect();
    // Get the channel name from the RSS itself
    $rss = fetch_rss($url);
    if(!$rss) {
        redirect("myfeeds");
    }
    $name = $rss->channel['title'];
    // Using INSERT IGNORE since when we add a duplicate we don't care
    // if it conflicts.
    $sql = "INSERT IGNORE INTO User_Feed 
                (User_id, name, link_hash, link)
            VALUES (:uid, :name, :hash, :link)";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':name' => $name, 
                        ':hash' => $url_hash, ':link' => $url));
    redirect('myfeeds');
  }
  catch(PDOException $e)
  {
      echo $e->getMessage();
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
