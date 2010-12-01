<?php 
  include_once("support.inc.php");
  include_once("rss_fetch.inc");

  try
  {
    // Connect to database
    db_connect();
    $statement = "SELECT * FROM User";
    $results = $dbh->query($statement);
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>Users</h3>
<?php
    if(count($results) == 0) {
      echo "No users yet.";
    }
    else {
      echo "<ul>\n";
      foreach($results as $u) {
?>
      <li><a href="profile.php?id=<?= $u['id'] ?>"><?= $u['username'] ?></a></li>
<?
      }
      echo "</ul>\n";
    }
?>
</div>
<? include_once('footer.php'); ?>
</body>
</html>
