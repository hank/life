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
    db_connect();
    // Get all our stock information with associated comments.
    $sql = "SELECT * FROM Owns LEFT OUTER JOIN Comment 
                ON (Owns.Stock_id = Comment.Owns_Stock_id 
                    AND Owns.User_id = Comment.Owns_User_id 
                    AND Owns.User_id = :uid)
                JOIN Stock ON Stock.id = Owns.Stock_id 
                ORDER BY date_added DESC";
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
<?php
if(count($results) == 0) {
  echo "<p>You need to add some charts!
        Type in a ticker on the top right to begin.</p>";
}
else{
?>
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
  <td><a href="mycharts_remove.php?id=<?=$row['id']?>">Remove</a></td>
  <td style="width:400px;">
    <div class="editable_textarea" 
         id="<?=$row['id']."_".$row['ticker']?>_comment" 
         title="Click to edit..."><? if($row['text'] != '') {
         echo $row['text'];
       }
    ?></div>
    <script>
    $(document).ready(function() {
      $(".editable_textarea").editable("mycharts_comment.php", { 
        name : 'text',
        type   : 'textarea',
        submitdata: function(value, settings) {
                return { _method: "post", 
                         ralree : value.id
                };
            },
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

