<?php 
  include_once("support.inc.php");
  include_once("rss_fetch.inc");

  try
  {
    // Connect to database
    db_connect();
    $statement = "SELECT * FROM Stock";
    $results = $dbh->query($statement);
    // Get RSS entries
    $statement = "SELECT * FROM Feeds";
    $rss_results = $dbh->query($statement);
    // Get OHLC data
    // This query finds the most recent 2 rows per Stock
    $statement = "SELECT ticker, close, date 
                  FROM (Stock JOIN OHLC ON Stock.id = OHLC.Stock_id) 
                  WHERE (SELECT COUNT(*) FROM OHLC OHLC2 
                         WHERE OHLC.Stock_id = OHLC2.Stock_id 
                         AND OHLC.date < OHLC2.date) < 2 
                  ORDER BY ticker, date DESC;";
    $ohlc_results = $dbh->query($statement);
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>Symbol Cloud</h3>
<div id="symbol_cloud">
<?php
    // Find the differences in the OHLC
    $tickers = array();
    foreach($results as $row) {
      $tickers[$row['ticker']] = array();
      $tickers[$row['ticker']][0] = $row['num_accesses'];
    }
    foreach(array_chunk($ohlc_results->fetchAll(), 2) as $pair)
    {
      $tickers[$pair[0]['ticker']][1] = 
            ((float)$pair[0]['close'] - (float)$pair[1]['close']) / 
                (float)$pair[1]['close'] * 100;
    }
    // Get tickers => count
    printTagCloud($tickers);
?>
</div>
<h3>RSS Feeds</h3>
<?
// Handle RSS
foreach($rss_results as $feed) {
    $rss = fetch_rss($feed['link']);
?>
    <h4><?=$rss->channel['title']?></h4>
<?
    $i = 0;
    foreach ($rss->items as $item) {
        $title = $item['title'];
        $url   = $item['link'];
        if(strlen($title) == 0 or strlen($url) == 0) continue;
        if(strlen($title) > 150) $title = substr($title, 0, 150)."...";
        echo "<a href=$url>$title</a><br/>";
        $i++;
        if($i > 4) break;
    }
}
?>

<? include_once('footer.php'); ?>
</body>
</html>
