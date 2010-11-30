<?php 
  include_once("support.inc.php");

  if(!array_key_exists('id', $_GET) and !logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    // Connect to database
    db_connect();
    if(!array_key_exists('id', $_GET)) $uid = $_SESSION['userid'];
    else $uid = $_GET['id'];
    $sql = "SELECT * FROM Recently_Viewed_Stocks JOIN Stock
            ON Recently_Viewed_Stocks.Stock_id = Stock.id
            WHERE User_id = :uid 
            LIMIT 10";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $stocks = $sth->fetchAll();
    $sql = "SELECT * FROM Friend JOIN User
            ON Friend.User_to = User.id
            WHERE User_from = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $friends = $sth->fetchAll();
    $sql = "SELECT username, first_name, last_name, admin, 
              UNIX_TIMESTAMP(created) created
            FROM User WHERE id = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $user = $sth->fetch();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h1><?= $user['username'] ?>'s Profile</h1>
<ul style="list-style-type: none;">
  <li>Name: <?= $user['first_name']?> <?= $user['last_name']?></li>
  <li>Member Since: <?= date('m/d/Y', $user['created']) ?></li>
<h3>Recently Viewed Charts</h3>
<?php
if(count($stocks) == 0) {
  echo "<p>{$user['username']} hasn't viewed any charts yet</p>";
}
else {
    echo "<div>";
    foreach($stocks as $r) {
      echo "<a href=\"chart.php?id={$r['Stock_id']}\">{$r['ticker']}</a><br />";
    }
    echo "</div>";
}
?>
<h3>Friends</h3>
<?php
if(count($friends) == 0) {
  echo "<p>{$user['username']} hasn't made any friends yet</p>";
}
else {
    echo "<div>";
    foreach($friends as $r) {
      echo "<a href=\"chart.php?id={$r['Stock_id']}\">{$r['ticker']}</a><br />";
    }
    echo "</div>";
}
?>
<? include_once('footer.php'); ?>
</body>
</html>

