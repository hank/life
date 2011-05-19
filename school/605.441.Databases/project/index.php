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
    $statement = "SELECT * FROM Feed";
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
    // Fetch predictions
    $pre = $dbh->prepare("SELECT * FROM Prediction, Stock, User
                          WHERE Stock.id = Prediction.Stock_id 
                            AND User.id = Prediction.User_id
                          ORDER BY date DESC
    ");
    $pre->execute();
    $predictions = $pre->fetchAll();
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
    if(count($tickers) == 0) {
      echo "No symbols yet.";
    }
    else {
      // Get tickers => count
      printTagCloud($tickers);
    }
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
        if(array_key_exists('title', $item)) $title = $item['title'];
        else $title = "Title not specified";
        if(strlen($title) > 150) $title = substr($title, 0, 150)."...";
        if(array_key_exists('link', $item)) {
          $url = $item['link'];
          if(strlen($title) == 0 or strlen($url) == 0) continue;
          echo "<a href=$url>$title</a><br/>";
        }
        else {
          echo "$title<br />";
        }
        $i++;
        if($i > 4) break;
    }
}
?>

<h3>Community Predictions</h3>
<div>
<?php
if(count($predictions) == 0) {
  echo "<p>{$user['username']} hasn't made any predictions yet</p>";
}
else {
  foreach($predictions as $p) {
?>
    <div class="prediction">
      <span class="date"><?= $p['date'] ?></span>
      <span class="ticker">
        <a href="chart.php?id=<?= $p['Stock_id'] ?>"><?= $p['ticker'] ?></a>
      </span>
      <span class="user">
        <a href="profile.php?id=<?= $p['User_id'] ?>"><?= $p['username'] ?></a>
      </span>
    <?= $p['text'] ?>
    </div>
<?
  }
}
?>
</div>

<? include_once('footer.php'); ?>
</body>
</html>
