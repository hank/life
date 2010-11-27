<?php 
  include_once("support.inc.php");

  if(!logged_in())
  {
        redirect("login");
        exit();
  }

  try
  {
    // Connect to database
    $dbh = new PDO("mysql:host=$hostname;dbname=5charts", $username, $password);
    $sql = "SELECT * FROM Owns, Stock 
                  WHERE Stock.id = Owns.Stock_id AND User_id = :uid ORDER BY date_added DESC";
    $sth = $dbh->prepare($sql);
    $sth->execute(array(':uid' => $_SESSION['userid']));
    $results = $sth->fetchAll();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>My Charts</h3>
<table class="mycharts">
<tr>
  <th>Symbol</th>
  <th>Actions</th>
  <th colspan=3>Comments</th>
</tr>
<?php
    foreach($results as $row)
    {
?>
<tr>
  <td><a href="chart.php?id=<?=$row['id']?>" 
         title="<?=$row['name']?>"><?=$row['ticker']?></a></td>
  <td><a href="remove.php?id=<?=$row['id']?>">Remove</a></td>
  <td style="width:400px;"></td>
</tr>
<?php
   }
?>
</table>

<? include_once('footer.php'); ?>
</body>
</html>
