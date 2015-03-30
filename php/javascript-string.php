<?php
$str = 'I\'m
like
this
girl.';

function join_multilines($str) {
  /* $strs = preg_split('/\r?\n/', $str);
  $result = implode('\n', $strs); */
  $result = addcslashes($str, "\n\r'");
  var_dump($result);
  return $result;
}
?>

<html>
<head><title>javascript mutliline string</title>
<script language='javascript'>
function echo(str)
{
  alert(str);
}
</script>
</head>
<body>
<?php
$javascript_str = join_multilines($str);
echo "<script>echo('$javascript_str')</script>";
?>
</body>
</html>