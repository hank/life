<?php
  // THIS FILE MUST NOT PRINT ANYTHING.
  ob_start('ob_gzhandler');

  session_start();
  function logged_in()
  {
    if(array_key_exists('username', $_SESSION)) return true;
    else return false;
  }
  function redirect($page)
  {
    header("Location: $page.php\r\n");
    exit();
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

  // Define password for use in database connections
  $password = rtrim(file_get_contents('credentials.txt'));

  error_reporting(E_ALL);
  $hostname = 'localhost';
  $username = 'root';

?>
