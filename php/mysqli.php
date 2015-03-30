<?php
// connect to mysql
$mysqli = new mysqli('localhost', 'root', '567890', 'test');
if ($mysqli->connect_errno) {
  die("Failed to Connect to mysql: " . $mysqli->connect_errno);
}

// get a record with admin = $login_user
$sql = "SELECT passwd FROM blog WHERE admin='jolly';select * from blog;";
$result = $mysqli->query($sql);
// disconnect with mysql
$mysqli->close();

$row = $result->fetch_assoc();
echo "jolly's password is ". $row['passwd'] ."\n";
?>