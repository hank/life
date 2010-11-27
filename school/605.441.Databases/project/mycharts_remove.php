<?php
  include_once("support.inc.php");

  if(!logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    $stockid = $_GET['id'];
    // Connect to database
    db_connect();
    $sql = "DELETE FROM Owns WHERE User_id = :uid AND Stock_id = :sid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':sid' => $stockid));
    if($sth->rowCount() > 0)
    {
      // Insert Success!
      redirect('mycharts');
    }
    else
    {
      $error_message = "Remove Failed.  Try again.";
    }
  }
  catch(PDOException $e)
  {
      echo $e->getMessage();
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
