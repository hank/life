<?php
  include_once("support.inc.php");

  $un = $_POST['un'];
  $pw = $_POST['pw'];
  $fn = $_POST['fn'];
  $ln = $_POST['ln'];
  if($_SERVER['REQUEST_METHOD'] == "POST")
  {
    try
    {
      // Check login
      if(strlen($un) < 3) 
        throw new Exception("Username must be at least 3 characters.");
      if(strlen($pw) < 6) 
        throw new Exception("Password must be at least 6 characters.");
      $hash = hash('sha256', 'ITSATRAP!'.$pw);
      // Connect to database
      db_connect();
      $sql = "INSERT INTO User (username, password_hash, last_name, first_name)
              VALUES (:username, :hash, :ln, :fn)";
      $sth = $dbh->prepare($sql);
      if($sth->execute(array(':username' => $un, ':hash' => $hash,
                          ':fn' => $fn, ':ln' => $ln
                         )
      ))
      {
        // Win!  Go back to home
        redirect("login");
      }
      else {
        $error_message = "Error registering.  Try again.";
      }
    }
    catch(Exception $e)
    {
        $error_message = $e->getMessage();
    }
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
<? include_once('header.php'); ?>
<div style="padding: 40px;">
    <h1>Register</h1>
    <form method="post" action="register.php"> 
    <label>First Name:</label><br />
    <input type="text" name="fn" value="<?=$fn?>"> <br />
    <label>Last Name:</label><br />
    <input type="text" name="ln" value="<?=$ln?>"> <br />
    <label>Username:</label><br />
    <input type="text" name="un" value="<?=$un?>"> <br />
    <label>Password:</label><br />
    <input type="password" name="pw"> <br />
    <input type="submit" value="Submit" name="register"> 
</div>
<? include_once('footer.php'); ?>
