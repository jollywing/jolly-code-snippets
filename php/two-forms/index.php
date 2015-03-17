<html>
<head>
<meta charset='utf-8' />
<title>TOW FORMS</title>
</head>
<body>
<?php
// 未提交表单的字段不会在$_POST中注册
if(isset($_POST['name'])){
  $name = $_POST['name'];
}
if(isset($_POST['age'])){
  $age = $_POST['age'];
}
?>

<form action='index.php' method='post'>
<input type='text' name='name' value='<?php echo $name; ?>'/>
<input type='submit' name='submit_name' value='提交姓名' />
</form>

<form action='index.php' method='post'>
<input type='text' name='age' value='<?php echo $age; ?>'/>
<input type='submit' name='submit_age' value='提交年纪' />
</form>

</body>
</html>