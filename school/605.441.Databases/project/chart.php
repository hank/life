<?php 
  include_once("support.inc.php");
  include_once('header.php');

  $id = null;

  if(array_key_exists('id', $_GET))
  {
    $id = $_GET['id'];
    if(strlen($id) == 0)
    {
      echo "You must supply an id";
      exit;
    }
    // Get our stock
    db_connect();
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    if(($stock = $statement->fetch()) == false)
    {
      echo "Error: ID $id does not exist.";
      exit;
    }
    // Find out if our data is dated (over a day old at 4PM)
    $ticker = strtoupper($stock['ticker']);
    $sql = "SELECT COUNT(*) FROM OHLC WHERE Stock_id = :sid 
            AND (date + 0) > (NOW() - (3600 * 41))";
    $statement = $dbh->prepare($sql);
    $statement->execute(array(':sid' => $id));
    if($statement->fetchColumn() == 0) {
      // Download the information and insert it in the database
      download_stock_info($ticker);
    }
  }
  else if(array_key_exists('ticker', $_GET))
  {
    $ticker = strtoupper($_GET['ticker']);
    if(strlen($ticker) == 0)
    {
      echo "You must supply a ticker";
      exit;
    }
    // Get our stock
    db_connect();
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE ticker = :ticker");
    $statement->execute(array(':ticker' => $ticker));
    if(($stock = $statement->fetch()) == false)
    {
      // Download the information and insert it in the database
      $id = download_stock_info($ticker);
    }
    else
    {
      $id = $stock['id'];
    }
  }
  else
  {
    echo "Error: Need to specify id or ticker";
    exit;
  }
  

  try
  {
    // Finally, select the stock!
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    if(($stock = $statement->fetch()) == false)
    {
      echo "Error: ID $id does not exist.";
      exit;
    }
    // We have our stock.  Increment access count
    $statement = $dbh->prepare("UPDATE Stock 
                                SET num_accesses = num_accesses + 1 
                                WHERE id = :id");
    $statement->execute(array(':id' => $id));
    // Get the associated OHLC data for the past year.
    $year_ago_date = strtotime("1 year ago");
    $ohlc = $dbh->prepare(
      "SELECT * FROM OHLC WHERE Stock_id = :id
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
<h2><?= $stock['ticker'] ?>: <?= $stock['name'] ?></h2>
<p><a href="mycharts_add.php?id=<?=$stock['id']?>">Add to My Charts</a></p>
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

<script>
// Special tab append for charting
$('#menu ul').append('<li><a href="#" class="active"><?=$stock['ticker']?></a></li>');
</script>

<? include_once('footer.php') ?>
</body>
</html>
