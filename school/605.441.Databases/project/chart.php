<?php 
  ob_start('ob_gzhandler');
  error_reporting(E_ALL);

  function curl_get_file_contents($URL)
  {
      $c = curl_init();
      curl_setopt($c, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($c, CURLOPT_URL, $URL);
      $contents = curl_exec($c);
      curl_close($c);

      if ($contents) return $contents;
          else return FALSE;
  }

  try
  {
    // Define password for use in database connections
    $password = rtrim(file_get_contents('credentials.txt'));
    $hostname = 'localhost';
    $username = 'root';
    // Connect to database
    $dbh = new PDO("mysql:host=$hostname;dbname=5charts", $username, $password);
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
  $dbh->setAttribute (PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  $id = 0;

  if(array_key_exists('id', $_GET))
  {
    $id = $_GET['id'];
    // Get our stock
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    if(($stock = $statement->fetch()) == false)
    {
      echo "Error: ID does not exist.";
      exit;
    }
  }
  else if(array_key_exists('ticker', $_GET))
  {
    $ticker = strtoupper($_GET['ticker']);
    // Get our stock
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE ticker = :ticker");
    $statement->execute(array(':ticker' => $ticker));
    if(($stock = $statement->fetch()) == false)
    {
      // Download the information and insert it in the database

      // We have to get the name of the stock.
      $yahoodata = curl_get_file_contents("http://download.finance.yahoo.com/d/quotes.csv?s=$ticker&f=ne1");
      $arr = explode(',', $yahoodata);
      $name = $arr[0];
      $err = $arr[1];
      if(preg_match("/No such ticker/", $err))
      {
        echo "Error: Ticker $ticker does not exist.";
        exit;
      }
      $name = trim($name, "\" \t\n\r");

      // Download the CSV into a tmpfile
      $tf = tempnam('/tmp', '5charts');
      $ticket = $dbh->quote($ticker);
      $csv = curl_get_file_contents("http://www.google.com/finance/historical?q=$ticker&output=csv");
      $handle = fopen($tf, 'w');
      fwrite($handle, $csv);
      fclose($handle);
      chmod($tf, 0777);

      try
      {
        // Now, make the stock and get the id.
        $statement = $dbh->prepare("INSERT INTO Stock (id, ticker, name) 
          VALUES (NULL, :ticker, :name)"
        );
        $statement->execute(array(':ticker' => $ticker, ":name" => $name));

        // Now, load the file with LOAD DATA
        $id = $dbh->lastInsertId();
        $statement = $dbh->prepare("LOAD DATA LOCAL INFILE :tf INTO TABLE OHLC 
            FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' 
            IGNORE 1 LINES (@in_date, open, high, low, close, volume) 
            SET Stock_id = :id, date = STR_TO_DATE(@in_date, '%d-%b-%y')"
        );
        $statement->execute(array(':tf' => $tf, ':id' => $id));
        // Unlink temp file
        unlink($tf);

      }
      catch(PDOException $e)
      {
        echo $e->getMessage();
      }
    }
    else
    {
      $id = $stock['id'];
    }
    // Finally, select the stock!
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    if(($stock = $statement->fetch()) == false)
    {
      echo "Error: ID does not exist.";
      exit;
    }
  }
  else
  {
    echo "Error: Need to specify id or ticker";
    exit;
  }
  

  try
  {
    // Get the associated OHLC data for the past year.
    $year_ago_date = strtotime("1 year ago");
    $ohlc = $dbh->prepare(
      "SELECT *
         FROM OHLC WHERE Stock_id = :id
         AND date >= FROM_UNIXTIME(:date)
         ORDER BY date ASC"
    );
    $ohlc->execute(array(':id' => $id, ':date' => $year_ago_date));

    // Retrieve chart bound from database with aggregate functions
    $bq = $dbh->prepare("SELECT MIN(low) as low, 
         MAX(high) as high FROM OHLC WHERE Stock_id = :id
         AND date >= FROM_UNIXTIME(:date)
         GROUP BY Stock_id"
    );
    $bq->execute(array(':id' => $id, ':date' => $year_ago_date));
    $bound = $bq->fetch();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
    <script>
        window.onload = function ()
        {
           var data = [
<?php
  $labels = array();
  $months = array("Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug",
                  "Sep", "Oct", "Nov", "Dec");
  $count = 0;
  $high = "";
  $low = "";
  $open = "";
  $close = "";
  while($row = $ohlc->fetch())
  {
    // Get the date
    $date = strptime($row['date'], '%Y-%m-%d %H:%M:%S');
    // First day of the month.  Takes care of months that start on  
    // Saturday and Sunday.
    if($date['tm_mday'] == 1 ||
       ($date['tm_mday'] <= 3 && $date['tm_wday'] == 1))
    {
      $labels[$months[$date['tm_mon']]] = $count;
    }
    // Print out our record in the required format for RGraph
    if(floatval($row['open']) < floatval($row['close']))
    {
      // A good day on the market.  The stock rose!
      $boxtop = $row['close'];
      $boxbottom = $row['open'];
      $color = "#00C000";
    }
    else
    {
      // A good day on the market.  The stock rose!
      $boxtop = $row['open'];
      $boxbottom = $row['close'];
      $color = "#F00000";
    }
    // Can set a bar middle as well, but not necessary now.
    $middle = $boxbottom;
    $high = $row['high'];
    $low = $row['low'];
    $open = $row['open'];
    $close = $row['close'];

    echo "\t\t[$count, [$low, $boxbottom, $middle, $boxtop, $high, '$color']],\n";

    ++$count;
  }
  
?>
            ];
            labels = [
<?php
  // Handle Labels.
  foreach(array_keys($labels) as $label)
  {
    $ind = $labels[$label];
    echo "\t\t[\"{$label}\", $ind],\n";
  }
  $floatlowest = floatval($bound['low']);
?>
            ];
            var scatter1 = new RGraph.Scatter('scatter1', data);
            scatter1.Set('chart.annotatable', true);
            scatter1.Set('chart.contextmenu', [
                                ['Show palette', RGraph.Showpalette],
                                ['Clear', function () {
                                    RGraph.Clear(scatter1.canvas); 
                                    scatter1.Draw();}
                                ],
                                null,
                                ['Get PNG', RGraph.showPNG],
                               ]);
            scatter1.Set('chart.labels', labels);
            scatter1.Set('chart.units.pre', '$');
            scatter1.Set('chart.scale.decimals', 2);
            scatter1.Set('chart.xmax', <?= $count ?>); // Necessary
            scatter1.Set('chart.ymin', <?= $floatlowest - ($floatlowest * 0.02)?>);
            scatter1.Set('chart.text.size', 7);
            scatter1.Set('chart.title', '<?= $stock['ticker'] ?>');
            scatter1.Set('chart.gutter', 50);
            scatter1.Set('chart.title.xaxis', 'Month');
            scatter1.Set('chart.title.xaxis.pos', 0.15);
            scatter1.Set('chart.title.yaxis', 'Price');
            scatter1.Set('chart.title.yaxis.pos', 0.5);
            scatter1.Set('chart.boxplot.width', 2.5); // The default width
            scatter1.Set('chart.crosshairs', true);
            scatter1.Set('chart.crosshairs.coords', true); 
            scatter1.Set('chart.resizable', true); 
            scatter1.Draw();
      }
</script>

<?php
$year = $date['tm_year'] + 1900;
$mon = $date['tm_mon'] + 1;

$diffnum = floatval($close) - floatval($open);
$diffpct = round($diffnum / floatval($open) * 100, 2);
$diffnum = round($diffnum, 2);
if($diffnum < 0) $diff = "<span style='color: red;'>$diffnum ($diffpct%)</span>";
else if($diffnum > 0) $diff = "<span style='color: green;'>$diffnum ($diffpct%)</span>";
else $diff = "<span>$diffnum ($diffpct%)</span>";

?>
</head>
<body>
<? include_once('header.php') ?>
<h2><?= $stock['ticker'] ?>: <?= $stock['name'] ?></h2>
<p>Latest Update: <?= "$mon/{$date['tm_mday']}/$year"?>
<table id='quote'>
<tr>
  <td>Open: <?= $open ?></td>
  <td>High: <?= $high ?></td>
</tr>
<tr>
  <td>Low: <?= $low ?></td>
  <td>Close: <?= $close ?></td>
</tr>
<tr>
  <td colspan=2>Daily Change: <?= $diff ?></td>
</tr>
</table>
<div>
<canvas id="scatter1" width="1000" height="600">[No canvas support]</canvas>
</div>

<? include_once('footer.php') ?>
</body>
</html>
