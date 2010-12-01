<?php
  // THIS FILE MUST NOT PRINT ANYTHING.
  ob_start('ob_gzhandler');
  session_start();

  $dbname = 'ralreein_5charts';
  $hostname = 'localhost';
  $username = 'ralreein_5charts';

  function db_connect()
  {
    global $dbh, $dbname, $hostname, $username, $password;
    $dbh = new PDO("mysql:host=$hostname;dbname=$dbname", $username, 
            $password);
    $dbh->setAttribute (PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  }

  function logged_in()
  {
    if(array_key_exists('username', $_SESSION)) return true;
    else return false;
  }

  function is_admin()
  {
    if(array_key_exists('admin', $_SESSION) and $_SESSION['admin'] == 1) 
            return true;
    else return false;
  }

  function redirect($page, $args=null)
  {
    if($args == null) {
      header("Location: $page.php\r\n");
    } else {
      header("Location: $page.php?$args\r\n");
    }
    exit();
  }

  function array_flatten($a,$f=array()){
    if(!$a||!is_array($a))return '';
    foreach($a as $k=>$v){
      if(is_array($v))$f=array_flatten($v,$f);
      else $f[$k]=$v;
    }
    return $f;
  }

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

  // Download the information and insert it in the database
  function download_stock_info($ticker)
  {
    global $dbh;
    $yahoodata = curl_get_file_contents(
        "http://download.finance.yahoo.com/d/quotes.csv?s=$ticker&f=ne1"
    );
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
    $csv = curl_get_file_contents(
        "http://www.google.com/finance/historical?q=$ticker&output=csv"
    );
    $handle = fopen($tf, 'w');
    fwrite($handle, $csv);
    fclose($handle);
    chmod($tf, 0777);

    try
    {
      // See if we have the stock already
      $statement = $dbh->prepare("SELECT COUNT(*), id FROM Stock WHERE ticker = :ticker");
      $statement->execute(array(':ticker' => $ticker));
      $id = null;
      $result = $statement->fetch();
      if($result[0] == 0) {
        // We don't have it.
        // Now, make the stock and get the id.
        $statement = $dbh->prepare("INSERT INTO Stock (id, ticker, name) 
          VALUES (NULL, :ticker, :name)"
        );
        $statement->execute(array(':ticker' => $ticker, ":name" => $name));
        $id = $dbh->lastInsertId();
      }
      else {
        // We have it!
        $id = $result[1];
      }

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
      // Unlink temp file
      unlink($tf);
    }
    return $id;
  }

  function get_index(&$item, $key, $index) {
    $item = $item[$index];
  }

  // Print Ticker Cloud
  function printTagCloud($tags) {
    $max_size = 42; // max font size in pixels
    $min_size = 12; // min font size in pixels
  
    // largest and smallest array values
    $count_array = $tags;
    array_walk($count_array, "get_index", 0);
    $max_qty = max(array_values($count_array));
    $min_qty = min(array_values($count_array));
  
    // find the range of values
    $spread = $max_qty - $min_qty;
    if ($spread == 0) { // we don't want to divide by zero
        $spread = 1;
    }
  
    // set the font-size increment
    $step = ($max_size - $min_size) / ($spread);
  
    // loop through the tag array
    foreach ($tags as $key => $value) {
        // calculate font-size
        // find the $value in excess of $min_qty
        // multiply by the font-size increment ($size)
        // and add the $min_size set above
        $count = $value[0];
        $diff = round($value[1], 2);
        $size = round($min_size + (($count - $min_qty) * $step));
        $times = $count == 1 ? "Time" : "Times";
        $green = (int)($diff * 102);
        $red = (int)($diff * -102);
        if($green > 255) $green = 255;
        else if($green < 0) $green = 0;
        if($red > 255) $red = 255;
        else if($red < 0) $red = 0;
        if($diff >= 0) $diff = "+$diff";
        echo "<a class=\"cloud\" href=\"chart.php?ticker=$key\" 
                 style=\"font-size: {$size}px;color: rgb($red, $green, 0);\" 
                 title=\"Accessed $count $times, {$diff}%\">$key</a>
";
    }
  }


  // Define password for use in database connections
  $password = rtrim(file_get_contents('credentials.txt'));

  error_reporting(E_ALL);

?>
