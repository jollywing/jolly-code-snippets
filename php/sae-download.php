<?php
/*
* get domain and filename by yourself
*/
$domain = "";
$filename = "";

/*
* define content-type
*/
$stor = new SaeStorage();

if( !$stor->fileExist($domain, $filename) )
    die();

$attr = $stor->getAttr($domain, $filename);
header('Content-type: '.$attr['content_type']);
header('Content-Disposition: attachment; filename="'.$filename.'"');

echo $stor->read($domain, $filename);
$stor->delete($domain, $filename);

?>