<?php
// run this with php commandline
if ($argc < 2) {
    echo "Usage: php helloworld.php <something>\n";
    exit(1);
}

echo "Hello, $argv[1]\n";
?>
