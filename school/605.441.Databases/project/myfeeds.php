<?php 
  include_once("support.inc.php");
  include_once("rss_fetch.inc");

  function print_results($results, $show_xs = true)
  {
    foreach($results as $feed) {
        $rss = fetch_rss($feed['link']);
        if(!$rss) {
            echo "Error reading feed from {$feed['link']}";
        }
        else {
            echo "<h4>{$feed['name']}";
            if($show_xs) {
              echo " <small>[ <a href=\"myfeeds_remove.php?link={$feed['link']}\">x</a> ]</small>";
            }
            echo "</h4>";
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
    }
  }

  if(!logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    // Connect to database
    db_connect();
    // Get all our Feeds
    $sql = "SELECT * FROM User_Feed WHERE User_id = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $results = $sth->fetchAll();

    // Get Yahoo! feeds for all stocks in Owns
http://finance.yahoo.com/rss/headline?s=NFLX
    $sql = "SELECT ticker FROM Stock, Owns
            WHERE Stock.id = Owns.Stock_id AND User_id = :uid";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $tickers = $sth->fetchAll();
    $stocks_results = array();
    foreach($tickers as $t) {
        array_push($stocks_results, array(
          'name' => "Yahoo! Finance: {$t['ticker']}",
          'link' => "http://finance.yahoo.com/rss/headline?s={$t['ticker']}"));
    }
    
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>My Feeds</h3>
<?php
if(count($results) == 0) {
  echo "<p>You need to add some feeds!</p>";
}
else {
    echo "<div>";
    print_results($results);
    echo "</div>";
}
?>
<h3>News for My Charts</h3>
<?
if(count($stocks_results) == 0) {
  echo "<p>You need to add some charts!</p>";
}
else {
    echo "<div>";
    print_results($stocks_results, false);
    echo "</div>";
}
?>
<h4>Add Feed</h4>
<form action="myfeeds_add.php" method="post">
  <label for="url">Url</label>
  <input type="text" name="url" size="80"/>
  <input type="submit" value="Add" />
</form>
<? include_once('footer.php'); ?>
</body>
</html>

