<?php 
  include_once("support.inc.php");

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
    $sql = "SELECT * FROM Recent_Views JOIN Stock
            ON Recent_Views.foreign_id = Stock.id
            WHERE User_id = :uid AND table = 'Stock'";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $stocks = $sth->fetchAll();

    $sql = "SELECT * FROM Recent_Views JOIN User
            ON Recent_Views.foreign_id = User.id
            WHERE User_id = :uid AND table = 'User'";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $users = $sth->fetchAll();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h1><?= $_SESSION['username'] ?>'s Profile</h1>
<h3>Recently Viewed Charts</h3>
<?php
if(count($results) == 0) {
  echo "<p>You haven't viewed any charts yet</p>";
}
else {
    echo "<div>";
    foreach($stocks as $r) {
      echo "<a href=\"chart.php?id={$r['foreign_id']}>{$r['ticker']}</a>";
    }
    echo "</div>";
}
?>
<? include_once('footer.php'); ?>
</body>
</html>

