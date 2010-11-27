<?php
  include_once("support.inc.php");

  if(logged_in())
  {
        redirect("mycharts");
        exit();
  }

  if($_SERVER['REQUEST_METHOD'] == "POST")
  {
    // Check login
    $un = $_POST['username'];
    $pw = $_POST['password'];
    $hash = hash('sha256', 'ITSATRAP!'.$pw);
    try
    {
      // Connect to database
      db_connect();
      $sql = "SELECT * FROM User WHERE username = :username 
          AND password_hash = :hash";
      $sth = $dbh->prepare($sql);
      $sth->execute(array(':username' => $un, ':hash' => $hash));
      $results = $sth->fetchAll();
      if(count($results) > 0)
      {
        // Login Successful!
        $_SESSION['userid'] = $results[0]['id'];
        $_SESSION['username'] = $un;
        $_SESSION['time'] = time();
        redirect("mycharts");
      }
      else
      {
        $error_message = "Login Failed.  Try again.";
      }
    }
    catch(PDOException $e)
    {
        echo $e->getMessage();
    }
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
<? include_once('header.php'); ?>
<div style="padding: 40px;">
    <h1>Login</h1>
    <form method="post" action="login.php"> 
    <label>Username:</label><br />
    <input type="text" name="username"><br />
    <label>Password:</label><br />
    <input type="password" name="password"><br />
    <input type="submit" value="Submit" name="login"> 
<div>
<? include_once('footer.php'); ?>
