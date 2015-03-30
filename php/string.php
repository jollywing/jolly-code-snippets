<?php
function summarize($text, $maxlen)
{
  if(mb_strlen($text, 'UTF-8') <= $maxlen){
    return $text;
  }
  else {
    $substr = mb_substr($text, 0, $maxlen, 'UTF-8');
    return "$substr...";
  }
}

$text = '我是一只小小小小鸟，

-----
想要飞却怎么样也飞不高。';

$strs = preg_split('/-{5,}/', $text);

echo 'Splited: '. $strs[0] ."\n";

$result = summarize($strs[0], 10);

echo "Original: $text\n";
echo "Length: " . mb_strlen($text, "UTF-8") . "\n";
echo "Summary: $result\n";


?>