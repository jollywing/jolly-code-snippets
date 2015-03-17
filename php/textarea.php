<html>
<head></head>
<body>
<form action="textarea.php">
<textarea name='text'>我知道最后的结果，那绝对不是我。</textarea>
<input type='submit'/>
<?php
if(array_key_exists('text', $_POST)){
echo 'You just input: ' . $_POST['text'];
}
?>
</form>
</body>
</html>