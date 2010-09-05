<?
// create a SQLite3 database file with PDO and return a database handle (Object Oriented)
$searchterm = $_GET['q'];
if($searchterm) {
  try
  {
    $dbHandle = new PDO('sqlite:delicious.db');
  }
  catch(PDOException $exception) {
    echo 'sqlite:delicious.db';
    die($exception->getMessage());
  }  
  $sqlGetView = "SELECT * FROM bookmarks 
      WHERE LOWER(link) LIKE '%$searchterm%' 
         OR LOWER(name) LIKE '%$searchterm%'";
  $result = $dbHandle->query($sqlGetView);
  $bmks = $result->fetchAll(); // store result in array
}

?>
<html>
<head>
<link rel="stylesheet" href="./style.css" />
<title>So Delicious Search <?= ": $searchterm" ?></title>
</head>
<body>
<? include('header.php'); ?>
<h2>Search <?= ": $searchterm" ?></h2>
<?
if($bmks) {
  echo "<table>";
  foreach($bmks as $bm) {
    echo "<tr>";
    echo "<td><a href=\"{$bm['local_url']}\">{$bm['name']}</a></td>";
    echo "</tr>";
  }
  echo "</table>";
} else {
  echo "Nothing found for query '$searchterm'";
}
?>
</body>
</html>
