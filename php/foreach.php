<?php
$text = 'hello

I love the world!

Do you believe me?
I Hate you!



Fuck!!!';
$paragraphs = preg_split("/\n{2,}/m", $text);
$out = "";
foreach($paragraphs as $paragraph) {
  $out .= "\n<p>".$paragraph."</p>\n";
}

echo $out;
?>
