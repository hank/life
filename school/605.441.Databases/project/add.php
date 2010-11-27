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
    $dbh = new PDO("mysql:host=$hostname;dbname=5charts", $username, 
            $password);
    $sql = "SELECT close from OHLC WHERE Stock_id = :sid ORDER BY date DESC LIMIT 1"; 
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':sid' => $stockid));
    $results = $sth->fetchAll();
    $last_price = $results[0]['close'];
    $sql = "INSERT INTO Owns (User_id, Stock_id, date_added, price_on_add, active)
            VALUES (:uid, :sid, NOW(), :price, TRUE)";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':sid' => $stockid, ':price' => $last_price));
    if($sth->rowCount() > 0)
    {
      // Insert Success!
      redirect('mycharts');
    }
    else
    {
      $error_message = "Add Failed.  Try again.";
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
