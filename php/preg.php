<?php
$str='a b   c';
$times = preg_match_all('|\s+|', $str);
echo "white space occurs for $times times.\n";

// $regex = '/^[\-\+]\s(.*)$\r?\n^[\-\+]\s.*/m';
$regex = '/(^[\-\+]\s.*(\r?\n)+)+/m';
//\r?\n^[\-\+]\s.*/m';
// $regex = '/^[\-\+]\s(.*)$/m';

$long_str = '- shit
- little dog
+ hello kitty
hello';

$times = preg_match_all($regex, $long_str, $out);
echo "total list:" .count($out[0]) ."\n";
foreach ($out[0] as $total_list) {
  echo $total_list ."\n";
}
foreach ($out[1] as $list) {
  echo $list ."\n";
}
echo "list item occurs for $times times.\n";


function itemize($matches) {
  $items = preg_split('+\r?\n+', $matches[0]);
  $out = '';
  foreach($items as $it) {
    if($it != ""){
      echo $it ."\n";
      /* str_replace("- ", '', $it);
      str_replace("+ ", '', $it); */
      $it = preg_replace('/^[\-\+]\s/', "", $it);
      $out .= "<li>" . $it ."</li>\n";
    }
  }
  return "<ul>\n" . $out ."</ul>";
}

function itemizeList($text) {
  $patt = '/(^[\-\+]\s\S+.*?$\r?\n?)+/m';
  // $patt = '/<[ou]l>([\s\S]*?)<\/[ou]l>/mi';
  // NOTICE: anonymous function need php 5.3+
  $result =  preg_replace_callback($patt, "itemize", $text);
  return $result;
}

// NOTICE: anonymous function need php 5.3+
$result =  itemizeList($long_str);
echo "$result\n";

$ol_string = '
1. money
2. is good
34. hello

';

function ol_itemize($matches) {
  $items = preg_split('+\r?\n+', $matches[0]);
  $out = '';
  foreach($items as $it) {
    if($it != ""){
      $it = preg_replace(array('/^[\-\+]\s/', '/^\d+\.\s/'), array("", ''), $it);
      $out .= "<li>" . $it ."</li>\n";
    }
  }
  return "<ol>\n" . $out ."</ol>";
}

$ol_pattern = '/(^\d+\.\s\S+.*?$\r?\n?)+/m';
$ol_html = preg_replace_callback($ol_pattern, "ol_itemize", $ol_string);
echo "$ol_html\n";
?>