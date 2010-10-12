<?php 
  ob_start('ob_gzhandler');


  // Define password for use in database connections
  $password = rtrim(file_get_contents('credentials.txt'));

  error_reporting(E_ALL);
  $hostname = 'localhost';
  $username = 'root';

  $id = $_GET['id'];

  try
  {
    // Connect to database
    $dbh = new PDO("mysql:host=$hostname;dbname=5charts", $username, $password);

    // Get our stock
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    $stock = $statement->fetch();

    // Get the associated OHLC data for the past year.
    $year_ago_date = strtotime("1 year ago");
    $statement = $dbh->prepare(
      "SELECT * FROM OHLC WHERE Stock_id = :id
         AND date >= FROM_UNIXTIME(:date)"
    );
    $statement->execute(array(':id' => $id, ':date' => $year_ago_date));
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="X-UA-Compatible" content="chrome=1">

    <title>5charts</title>
</head>
<body>

<?php
  while($row = $statement->fetch())
  {
    print_r($row);
    echo "<br />";
  }
  
?>

<?php
  $statement->closeCursor();
?>
</body>
</html>
