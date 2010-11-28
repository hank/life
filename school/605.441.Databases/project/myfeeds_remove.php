<?php
  include_once("support.inc.php");

  if(!logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    $id = $_GET['id'];
    // Connect to database
    db_connect();
    $sql = "DELETE FROM User_Feed WHERE User_id = :uid AND id = :id";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':id' => $id));
    if($sth->rowCount() > 0)
    {
      // Insert Success!
      redirect('myfeeds');
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
