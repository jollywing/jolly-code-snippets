
<?php
if(isset($_POST['submit'])){
  echo 'validating ...';
  if ($_POST['username'] == 'root' && $_POST['userpasswd'] == '123') {
    echo '<p>PASS!</p>';
  }
  else {
    echo '<p>FAILED!!!</p>';
  }
}
?>