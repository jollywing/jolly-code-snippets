
<html>
<head>
<meta charset='utf-8'/>
<title>URL ENCODING</title>
</head>
<body>
<h1>URL ENCODING</h1>
<?php
$name = '成功日记';
$query_str = 'name=' . urlencode($name);
echo "ENCODED: $query_str\n";
echo "<a href='echo.php?$query_str'>ECHO</a>";
?>
</body>
</html>