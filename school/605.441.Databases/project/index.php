<?php 
  ob_start('ob_gzhandler');

  // Define password for use in database connections
  $password = rtrim(file_get_contents('credentials.txt'));

  error_reporting(E_ALL);
  $hostname = 'localhost';
  $username = 'root';

  try
  {
    // Connect to database
    $dbh = new PDO("mysql:host=$hostname;dbname=5charts", $username, $password);
    $statement = "SELECT * FROM Stock LIMIT 5";
    $results = $dbh->query($statement);
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
    foreach($results as $row)
    {
      echo <<<EOSTOCK
<li>
  <a href="chart.php?id={$row['id']}" title="{$row['name']}">
   {$row['ticker']}
  </a>
</li>
EOSTOCK;
    }
?>

</body>
</html>
