<?
// create a SQLite3 database file with PDO and return a database handle (Object Oriented)
try
{
  $dbHandle = new PDO('sqlite:delicious.db');
}
catch(PDOException $exception) {
  echo 'sqlite:delicious.db';
  die($exception->getMessage());
}  
$sqlGetView = 'SELECT * FROM bookmarks';
$result = $dbHandle->query($sqlGetView);
$bmks = $result->fetchAll(); // store result in array

echo "<table>";
foreach($bmks as $bm) {
  echo "<tr>";
  echo "<td>{$bm['id']}</td>";
  echo "<td>{$bm['link']}</td>";
  echo "<td><a href=\"{$bm['local_url']}\">{$bm['name']}</a></td>";
  echo "</tr>";
}
echo "</table>";
?>
