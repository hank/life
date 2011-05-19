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
    $sql = "SELECT close from OHLC WHERE Stock_id = :sid 
            ORDER BY date DESC LIMIT 1"; 
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':sid' => $stockid));
    $results = $sth->fetchAll();
    $last_price = $results[0]['close'];
    // Using INSERT IGNORE since when we add a duplicate we don't care
    // if it conflicts.
    $sql = "INSERT IGNORE INTO Owns 
                (User_id, Stock_id, date_added, price_on_add, active)
            VALUES (:uid, :sid, NOW(), :price, TRUE)";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':sid' => $stockid, 
                        ':price' => $last_price));
    redirect('mycharts');
  }
  catch(PDOException $e)
  {
      echo $e->getMessage();
  }
?>
<? if(isset($error_message)) { ?>
<p><?= $error_message ?></p>
<? } ?>
