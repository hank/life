<!DOCTYPE html>
<html>
<head>
<meta http-equiv="X-UA-Compatible" content="chrome=1">

<title>5charts</title>
<meta name="keywords" content="" />
<meta name="description" content="" />
<link rel="stylesheet" type="text/css" href="style.css" />
<link rel="stylesheet" type="text/css" title="Red" href="style_red.css" />
<link rel="alternate stylesheet" type="text/css" title="Blue" href="style_blue.css" />
<link rel="alternate stylesheet" type="text/css" title="Green" href="style_green.css" />
<link rel="alternate stylesheet" type="text/css" title="Brown" href="style_brown.css" />
<link rel="alternate stylesheet" type="text/css" title="Magenta" href="style_magenta.css" />
<script src="RGraph/libraries/RGraph.common.core.js" ></script>
<script src="RGraph/libraries/RGraph.common.context.js" ></script>
<script src="RGraph/libraries/RGraph.common.annotate.js" ></script>
<script src="RGraph/libraries/RGraph.common.zoom.js" ></script>
<script src="RGraph/libraries/RGraph.common.tooltips.js" ></script>
<script src="RGraph/libraries/RGraph.scatter.js" ></script>
<!--[if IE 8]><script src="../excanvas/excanvas.compressed.js"></script>
<![endif]-->
<script src="styleswitch.js" type="text/javascript"></script>
</head>
<body>
<div id="header">

	<div id="header_inner" class="fixed">

		<div id="logo">
			<h1><span>5Charts</span> 1.0</h1>
			<h2>By Erik Gregg</h2>
		</div>
		
		<div id="menu">
			<ul>
				<li><a href="/stockproject">Home</a></li>
<? if(preg_match("/chart.php/", $_SERVER['SCRIPT_NAME'])) { ?>
				<li><a href="#" class="active">Chart</a></li>
<? } ?>
			</ul>
		</div>
		
	</div>
</div>

<div id="main">

	<div id="main_inner" class="fixed">

		<div id="primaryContent_columnless">

			<div id="columnA_columnless">

        <div>				
          <form action="chart.php" method="get">
          <label>Ticker</label>
          <input type="text" name="ticker" />
          <input type="submit" value="Chart it!"/>
          </form>
        </div>
