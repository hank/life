<?php
  include_once("support.inc.php");
  include_once("htmlpurifier/library/HTMLPurifier.standalone.php");


  if(!logged_in())
  {
    header("HTTP/1.0 403 Not Authorized\r\n");
    exit();
  }

  if($_SERVER['REQUEST_METHOD'] != "POST")
  {
    header("HTTP/1.0 405 Method Not Allowed\r\n");
    header("Allow: POST\r\n");
    exit();
  }

  $text = "";

  try
  {
    $text = $_POST['text'];
    $purifier = new HTMLPurifier();
    $clean_html = $purifier->purify($text);
    $stockid = $_POST['id'];
    // Connect to database
    db_connect();
    $sql = "INSERT INTO Comment (Owns_User_id, Owns_Stock_id, date, text)
            VALUES (:uid, :sid, NOW(), :text)
            ON DUPLICATE KEY UPDATE date = NOW(), text = :text";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid'], ':sid' => $stockid, 
                        ':text' => $clean_html));

    // Handle mood, if any
    if(array_key_exists('mood', $_POST))
    {
        $last_id = $sth->lastInsertId();
        $sql = "UPDATE Comment mood = :mood WHERE id = :id";
        $sth = $dbh->prepare($sql);
        $sth->execute(array(':id' => $last_id, ':mood' => $_POST['mood']));
    } 
    echo $clean_html;
  }
  catch(PDOException $e)
  {
      echo $e->getMessage();
  }
?>
