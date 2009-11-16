<?php
  $signer_key = $_POST["signer_key"];
  $signee_key = $_POST["signee_key"];
  $signer_email = $_POST["signer_email"];
  $signee_email = $_POST["signee_email"];
  error_reporting(E_ALL);

try {
  // Save a row in the database for the exchange
  $db = new PDO('sqlite:/tmp/keyex.db');

  $db->exec('CREATE TABLE IF NOT EXISTS key_exchanges (
      signer_key STRING, 
      signee_key STRING,
      signer_email STRING
      signee_email STRING,
    )'
  );

  try {
    $sth = $db->prepare("INSERT INTO key_exchanges 
                 (signer_key, signee_key, signer_email, signee_email)
                 VALUES (?, ?, ?, ?)"
    );
  } catch(PDOException $e){ 
              echo $e->getMessage();
              exit();
  } 

  $result = $sth->execute(
    array($signer_key, $signee_key, $signer_email, $signee_email)
  );
} catch (Exception $e) {
    echo 'Caught exception.  Send an email to hank@alaska.edu. ';
    exit();
}
  if($result == TRUE) {
    echo "Thanks.  We'll let you know when the other party responds.";
  } else {
    echo "Sorry pal.  Something went wrong and failed all over itself in the tater base.";
  }
?>
