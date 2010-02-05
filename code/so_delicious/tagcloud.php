<html>
<head>
<title>So Delicious: Tag Cloud</title>
<link rel="stylesheet" href="./style.css" />
</head>
<body>
<? include("header.php"); ?>
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
$sqlGetView = 'SELECT tags.id as id, tags.name as name, count(taggings.tid) AS count 
    FROM tags INNER JOIN taggings ON tags.id = taggings.tid 
    GROUP BY taggings.tid ORDER BY tags.name';
$result = $dbHandle->query($sqlGetView);
$tags = $result->fetchAll(); // store result in array

$sqlGetView = 'SELECT COUNT(*) as count FROM taggings';
$result = $dbHandle->query($sqlGetView);
$stuff = $result->fetchAll(); // store result in array
$totaltaggings = $stuff[0]['count'];

$sqlGetView = 'SELECT COUNT(*) as count FROM tags';
$result = $dbHandle->query($sqlGetView);
$stuff = $result->fetchAll(); // store result in array
$totaltags = $stuff[0]['count'];

$base_prop = $totaltaggings/$totaltags;
$base_fsize = 1;
$max_size = 24;
$min_size = 13;
?>

<div class='tagcloud'>
<?
foreach($tags as $t) {
  $size = floor($base_fsize * ($t['count'] * 20 / $base_prop));
  if($size > $max_size) $size = $max_size;
  if($size < $min_size) $size = $min_size;
  echo "<a href=\"tags.php?id={$t['id']}\" class=\"droplet\" style=\"font-size: {$size}px;\">{$t['name']}</a> \n";
}
?>
</div>
</body>
</html>
