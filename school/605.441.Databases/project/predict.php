<?php 
include_once("support.inc.php");
include_once("htmlpurifier/library/HTMLPurifier.standalone.php");

if(!logged_in())
{
      redirect("login");
      exit();
}

if($_SERVER['REQUEST_METHOD'] == "POST") {
  try
  {
    // Connect to database
    db_connect();
    $text = $_POST['text'];
    $purifier = new HTMLPurifier();
    $clean_html = $purifier->purify($text);

    $statement = $dbh->prepare("INSERT INTO Prediction
                                (User_id, Stock_id, text)
                                VALUES (:uid, :sid, :text)");
    $statement->execute(array(':uid' => $_SESSION['userid'],
                              ':sid' => $_POST['id'],
                              ':text' => $text
      ));

    redirect("chart", "id={$_POST['id']}");
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
}
else {
  try
  {
    $id = $_GET['id'];
    db_connect();
    $statement = $dbh->prepare("SELECT * FROM Stock WHERE id = :id");
    $statement->execute(array(':id' => $id));
    if(($stock = $statement->fetch()) == false)
    {
      echo "Error: ID $id does not exist.";
      exit;
    }
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
}
?>
<body>
<? include_once('header.php'); ?>
<h3>Make a Prediction about <?= $stock['ticker'] ?></h3>
<form action="predict.php" method="post">
  <textarea name="text" cols="80" rows="20"></textarea>
  <input type="hidden" name="id" value="<?= $stock['id'] ?>" />
  <input type="submit" value="Add" />
</form>
<? include_once('footer.php'); ?>
</body>
</html>

