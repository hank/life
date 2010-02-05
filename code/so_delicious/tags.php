<html>
<head>
<? include('header.php'); ?>
<link rel="stylesheet" href="style.css" />
<?
$id = $_GET['id'];
if($id) {
  try
  {
    $dbHandle = new PDO('sqlite:delicious.db');
  }
  catch(PDOException $exception) {
    echo 'sqlite:delicious.db';
    die($exception->getMessage());
  }  
  $sqlGetView = "SELECT name from tags where id=$id";
  $result = $dbHandle->query($sqlGetView);
  $tag = $result->fetch();
?>
  <title>So Delicious: Tag
  </head>
  <body>
  <h2>Tag: <?=$tag['name']?></h2>
<?  $sqlGetView = "SELECT bookmarks.name as name, bookmarks.link as link, bookmarks.local_url as local_url FROM bookmarks INNER JOIN taggings ON taggings.bid = bookmarks.id and taggings.tid=$id";
  $result = $dbHandle->query($sqlGetView);
  $bmks = $result->fetchAll(); // store result in array
/*
  echo "<pre>";
  print_r($bmks);
  echo "</pre>";
*/
  echo "<table>";
  foreach($bmks as $bm) {
    echo "<tr>";
    echo "<td>{$bm['id']}</td>";
    echo "<td><a href=\"{$bm['local_url']}\">{$bm['name']}</a></td>";
    echo "</tr>";
  }
  echo "</table>";
}
else {
  try
  {
    $dbHandle = new PDO('sqlite:delicious.db');
  }
  catch(PDOException $exception) {
    echo 'sqlite:delicious.db';
    die($exception->getMessage());
  }  
  $sqlGetView = 'SELECT tags.id as id, tags.name as name, GROUP_CONCAT(taggings.bid) as bookmarks FROM tags LEFT JOIN taggings ON tags.id = taggings.tid GROUP BY tags.id';
  $result = $dbHandle->query($sqlGetView);
  $bmks = $result->fetchAll(); // store result in array
  echo "<pre>";
  //print_r($bmks);
  echo "</pre>";

  echo "<table>";
  foreach($bmks as $t) {
    echo "<tr>";
    echo "<td>{$t['id']}</td>";
    echo "<td><a href=\"{$t['localurl']}\">{$t['name']}</a></td>";
    echo "<td>{$t['bookmarks']}</td>";
    echo "</tr>";
  }
  echo "</table>";
}
?>
</body>
</html>
