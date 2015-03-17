<?php
$result = '10a7d9a9a1d700bc9e660177a8dec7a6bd5c44b6';
if(sha1('801102') == $result){
  echo "PASS.\n";
}
else {
  echo "PASSWORD not correct!\n";
}

echo "Input: hello\n";
echo "MD5 result: " . md5("hello") . "\n";

?>
