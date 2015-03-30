
<?php
$a = $_GET['a'];
$b = $_GET['b'];
if($a == NULL) {
  die('$a is a unset variable.');
}
echo "$a + $b = ". $a + $b;
?>