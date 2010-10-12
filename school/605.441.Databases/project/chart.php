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
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="X-UA-Compatible" content="chrome=1">

    <title>5charts</title>

    <script src="RGraph/libraries/RGraph.common.core.js" ></script>
    <script src="RGraph/libraries/RGraph.common.context.js" ></script>
    <script src="RGraph/libraries/RGraph.common.annotate.js" ></script>
    <script src="RGraph/libraries/RGraph.common.zoom.js" ></script>
    <script src="RGraph/libraries/RGraph.common.tooltips.js" ></script>
    <script src="RGraph/libraries/RGraph.scatter.js" ></script>
    <!--[if IE 8]><script src="../excanvas/excanvas.compressed.js"></script>
    <![endif]-->
    <script>
        window.onload = function ()
        {
           var data = [
<?php
  $labels = array();
  $months = array("Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug",
                  "Sep", "Oct", "Nov", "Dec");
  $count = 0;
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
      $color = "green";
    }
    else
    {
      // A good day on the market.  The stock rose!
      $boxtop = $row['open'];
      $boxbottom = $row['close'];
      $color = "red";
    }
    // Can set a bar middle as well, but not necessary now.
    $middle = $boxbottom;

    echo "\t\t[$count, [{$row['low']}, $boxbottom, $middle, $boxtop, {$row['high']}, '$color']],\n";

    ++$count;
  }
  $ohlc->closeCursor();
  //$bound['high'];
  
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
?>
</head>
<body>
<? include_once('header.php') ?>
<h2><?= $stock['ticker'] ?>: <?= $stock['name'] ?></h2>

<canvas id="scatter1" width="1200" height="800">[No canvas support]</canvas><br />

<? include_once('footer.php') ?>
</body>
</html>
