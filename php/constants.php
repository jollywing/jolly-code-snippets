
<?php
define("FOO", "nitwit");
define("BAR", 1024);
echo FOO."\n";  // don't prefix constant with $
echo BAR."\n";

$a = 3 / 5;
echo "$a\n";

// magic constants
echo "Directory:". __DIR__ ."\n";
echo "File:". __FILE__ ."\n";
echo "Line:". __LINE__ ."\n";
?>