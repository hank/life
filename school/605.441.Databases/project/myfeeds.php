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
    // Connect to database
    db_connect();
    // Get all our Feeds
    $sql = "SELECT * FROM User_Feed where User_id = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $results = $sth->fetchAll();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>My Feeds</h3>
<?php
if(count($results) == 0) {
  echo "<p>You need to add some feeds!</p>";
}
else {
    // Handle RSS
    foreach($results as $feed) {
        $rss = fetch_rss($feed['link']);
        if(!$rss) {
            echo "Error reading feed from {$feed['link']}";
        }
        else {
            echo "<h4>{$feed['name']} 
                  <small>( 
                    <a href=\"myfeeds_remove.php?id={$feed['id']}\">x</a>
                         )</small></h4>";
            $i = 0;
            foreach ($rss->items as $item) {
                $title = $item['title'];
                $url   = $item['link'];
                if(strlen($title) == 0 or strlen($url) == 0) continue;
                if(strlen($title) > 150) $title = substr($title, 0, 150)."...";
                echo "<a href=$url>$title</a><br/>";
                $i++;
                if($i > 4) break;
            }
        }
    }
}
?>
<h4>Add Feed</h4>
<form action="myfeeds_add.php" method="post">
  <label for="url">Url</label>
  <input type="text" name="url" size="80"/>
  <input type="submit" value="Add" />
</form>
<? include_once('footer.php'); ?>
</body>
</html>

