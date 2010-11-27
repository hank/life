<?php 
  include_once("support.inc.php");
  include_once("rss_fetch.inc");

  try
  {
    // Connect to database
    db_connect();
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
<ul>
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
</ul>
<h3>RSS Feeds</h3>
<?
// Handle RSS
$rss = fetch_rss("http://feeds.fool.com/usmf/foolwatch");
?>
<h4><?=$rss->channel['title']?></h4>
<?
foreach (array_slice($rss->items, 0, 5) as $item) {
    $title = $item['title'];
    $url   = $item['link'];
    echo "<a href=$url>$title</a><br/>";
}
?>

<? include_once('footer.php'); ?>
</body>
</html>
