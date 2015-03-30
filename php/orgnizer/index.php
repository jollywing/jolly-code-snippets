<html>
<head>
<title>org mode parser</title>
</head>
<body>
<form method="post" action="<?php echo $_SERVER['PHP_SELF'];  ?>">
<p>源文件:</p>
<textarea cols="60" rows='5' name='src_text'
          value="<?php if(isset($_POST['src_text'])){echo $_POST['src_text'];} ?>"></textarea>
<p><input type='submit' name='submit'/></p>
</form>
<hr/>
<p>结果：</p>
<?php
if(isset($_POST['submit'])){
  echo '<p>Parsing ...</p>';
  $src = $_POST['src_text'];
  echo '<p>SOURCE</p>';
  echo "<pre>$src</pre>";
  /* if($src == "") {
  echo 'source is empty!';
  exit(1);
  } */
  
  require_once 'classOrgile.php';
  $orger = new orgile();
  $result = $orger->orgileThis($src);
  echo '<p>PREVIEW:</p>';
  echo "<blockquote>$result</blockquote>";
  echo '<p>HTML CODE:</p>';
  echo "<textarea cols='70' rows='15' readonly>$result</textarea>";
}
?>
</body>
</html>