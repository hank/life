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
    $uid = $_GET['id'];
    // Connect to database
    db_connect();
    // Using INSERT IGNORE since when we add a duplicate we don't care
    // if it conflicts.
    $sql = "INSERT IGNORE INTO Friend
                (User_from, User_to)
            VALUES (:user, :uid)";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':user' => $_SESSION['userid'], ':uid' => $uid));
    redirect('profile');
  }
  catch(PDOException $e)
  {
      echo $e->getMessage();
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
