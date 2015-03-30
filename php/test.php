
<?php
echo "Hello, the World!";
$post_title = 'hello, world';
$post_text = 'I love this world!';
$id = 5;
$datetime = date('Y-m-d H:i:s');
$insert_sql = "insert into article values ($id, NULL, \"$post_title\", \"Jolly Wing\", NULL, \"$post_text\", \"$datetime\", \"$datetime\", 0)";
echo $insert_sql;
echo "\n\\\\\n";
?>
<textarea><?php echo $insert_sql; ?></textarea>
<?php echo $_SERVER['PHP_SELF']; ?>

<?php
$filename_time_prefix = '';
$filename_cat_prefix = '';
$start_year = 2003;
$start_month = '03';
$end_year = 2011;
$end_month = 12;
$filename_time_prefix .= "$start_year$start_month-$end_year$end_month-";
echo $filename_time_prefix;
?>

<?php
$ip = $_SERVER['REMOTE_ADDR'];
echo $ip;
?>