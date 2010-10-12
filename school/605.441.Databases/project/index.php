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
    $statement = "SELECT * FROM Stock ORDER BY id DESC LIMIT 5";
    $results = $dbh->query($statement);
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>Our 5 most recently added tickers</h3>
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

<? include_once('footer.php'); ?>
</body>
</html>
