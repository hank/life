<?php 
  include_once("support.inc.php");
  $uid = null;
  $is_us = false;
  if(!array_key_exists('id', $_GET) and !logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    // Connect to database
    db_connect();
    if(!array_key_exists('id', $_GET)) {
      $uid = $_SESSION['userid'];
      $is_us = true;
    }
    else $uid = $_GET['id'];
    $sql = "SELECT * FROM Recently_Viewed_Stocks JOIN Stock
            ON Recently_Viewed_Stocks.Stock_id = Stock.id
            WHERE User_id = :uid 
            LIMIT 10";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $stocks = $sth->fetchAll();
    $sql = "SELECT * FROM Recently_Viewed_Users JOIN User
            ON Recently_Viewed_Users.User_to = User.id
            WHERE User_from = :uid 
            LIMIT 10";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $users = $sth->fetchAll();
    $sql = "SELECT * FROM Friend JOIN User
            ON Friend.User_to = User.id
            WHERE User_from = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $friends = $sth->fetchAll();
    $sql = "SELECT id, username, first_name, last_name, admin, 
              UNIX_TIMESTAMP(created) created
            FROM User WHERE id = :uid";
    // Fetch predictions for this User
    $pre = $dbh->prepare("SELECT * FROM Prediction JOIN Stock
                          ON Stock.id = Prediction.Stock_id
                          WHERE User_id = :uid
    ");
    $pre->execute(array(':uid' => $uid));
    $predictions = $pre->fetchAll();

    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $uid));
    $user = $sth->fetch();
    if(array_key_exists('id', $_GET) and logged_in()) {
      // Log that we've seen the user
      $sql = $dbh->prepare("INSERT IGNORE INTO `Recently_Viewed_Users`
                            (`User_from`, `User_to`)
                            VALUES (:uid, :other)"
      );
      $sql->execute(array(':uid' => $_SESSION['userid'], ':other' => $user['id']));
      
    }
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
  if($is_us) {
    echo "<p>You haven't made any friends yet</p>";
  }
  else {
    echo "<p>{$user['username']} hasn't made any friends yet</p>";
  }
}
else {
    echo "<div>";
    foreach($friends as $r) {
      echo "<a href=\"profile.php?id={$r['id']}\">{$r['username']}</a><br />";
    }
    echo "</div>";
}
?>
<? 
if(logged_in() and !$is_us) { 
  try {
    // Need to determine if we've already friended this user
    $sql = "SELECT COUNT(*) FROM Friend
            WHERE User_from = :uid
            AND User_to = :other";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], 
                        ':other' => $user['id']));
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
  if($sth->fetchColumn() == 0) {
?>
<a href="friend_add.php?id=<?= $uid ?>">Add <?= $user['username'] ?> as your friend!</a>
<? 
  } 
  else {
?>
  <?= $user['username'] ?> is your friend!
<?
  }
} 
?>
<h3>Recently Viewed Users</h3>
<?php
if(count($users) == 0) {
  echo "<p>{$user['username']} hasn't viewed any users yet</p>";
}
else {
    echo "<div>";
    foreach($users as $r) {
      echo "<a href=\"profile.php?id={$r['User_to']}\">{$r['username']}</a><br />";
    }
    echo "</div>";
}
?>

<h3>Predictions</h3>
<div>
<?php
if(count($predictions) == 0) {
  echo "<p>{$user['username']} hasn't made any predictions yet</p>";
}
else {
  foreach($predictions as $p) {
?>
    <div class="prediction">
      <span class="date"><?= $p['date'] ?></span>
      <span class="user">
        <a href="chart.php?id=<?= $p['id'] ?>"><?= $p['ticker'] ?></a>
      </span>
    <?= $p['text'] ?>
    </div>
<?
  }
}
?>
</div>
<script>
}
?>
<? include_once('footer.php'); ?>
</body>
</html>

