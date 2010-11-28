<?php 
include_once("support.inc.php");

if(!logged_in())
{
      redirect("login");
      exit();
}

if(!is_admin())
{
      redirect("index");
      exit();
}

if($_SERVER['REQUEST_METHOD'] == "POST") {
  // Execute request.
  $sectors = preg_split("/[\s,]+/", $_POST['sectors']);
  db_connect();
  try {
    $id = $_POST['id'];
    $dbh->beginTransaction();
    // Start by removing all linked sectors - clean slate
    $sth = $dbh->prepare("DELETE FROM Sector_has_Stock WHERE Stock_id = :id");
    $sth->execute(array(':id' => (int)$id));
    // Insert every sector into the Sector table
    // Ignore if it already exists
    foreach($sectors as $sector) {
      $sth = $dbh->prepare("INSERT IGNORE INTO Sector (name) 
                            VALUES (:name)");
      $sth->execute(array(':name' => $sector));
    }
    // Now link it to the stock
    foreach($sectors as $sector) {
      $sth = $dbh->prepare("INSERT IGNORE INTO Sector_has_Stock
                        (Stock_id, Sector_id) 
                        VALUES (:stock, (
                            SELECT id from Sector WHERE name = :sector))");
      $sth->execute(array(':sector' => $sector,
                          ':stock' => (int)$id));
    }
    $dbh->commit();
  }
  catch(PDOException $e)
  {
    $dbh->rollback();
    echo $e->getMessage();
  }

  echo implode(', ', $sectors);
}
else {
  try
  {
    // Connect to database
    db_connect();
    // Get all our stock information with associated comments.
    $sql = "SELECT Stock.id, Stock.ticker, 
                GROUP_CONCAT(Sector.name) as sec_name 
            FROM Stock LEFT JOIN (Sector_has_Stock JOIN Sector) 
            ON Stock.id = Sector_has_Stock.Stock_id 
                AND Sector.id = Sector_has_Stock.Sector_id 
            GROUP BY Stock.id";
    $sth = $dbh->prepare($sql);
    $sth->execute();
    $results = $sth->fetchAll();
  }
  catch(PDOException $e)
  {
    echo $e->getMessage();
  }
?>
<body>
<? include_once('header.php'); ?>
<h3>Sectors</h3>
<?php
if(count($results) == 0) {
  echo "<p>No Stocks Available Yet.
        Type in a ticker on the top right to begin.</p>";
}
else {
?>
<table class="mycharts">
<tr>
  <th>Symbol</th>
  <th>Sectors</th>
</tr>
<?php
    foreach($results as $row)
    {
?>
<tr>
  <td><a href="chart.php?id=<?=$row['id']?>" 
         title="<?=$row['name']?>"><?=$row['ticker']?></a></td>
  <td style="width:400px;">
    <div class="editable_textarea" 
         id="<?=$row['id']."_".$row['ticker']?>_sectors" 
         title="Click to edit..."><? if($row['sec_name'] != '') {
         echo str_replace(',', ', ', $row['sec_name']);
       }
    ?></div>
    <script>
    $(document).ready(function() {
      $(".editable_textarea").editable("sectors.php", { 
        name : 'sectors',
        type : 'textarea',
        submitdata: { _method: "post" },
        select : true,
        submit : 'OK',
        cancel : 'Cancel',
        cssclass : "editable",
        tooltip : "Click to Edit",
      });
    });
    </script>
  </td>
</tr>
<?php
   }
}
?>
</table>

<? include_once('footer.php'); ?>
</body>
</html>
<? } ?>
