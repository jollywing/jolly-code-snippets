<?php
// A key must be a string or a number
$article = array(
"title" => "Why do I like Emacs?",
"content" => 'Emacs is an old aged but very powerful editor!',
'id' => 5,
);

echo "Title: " . $article['title'] . "\n";
echo "Content: " . $article['content'] . "\n";

// 'Hello' will replace 'WaHaHa'
$auto_key_array = array('WaHaHa', 1000, 'death loop', 0 => 'Hello',);
var_dump($auto_key_array);
for($i = 0; $i < count($auto_key_array); $i++){
  echo "array[$i]: ". $auto_key_array[$i] ."\n";
}

// for each
function print_array($array_name){
  $i = 0;
  foreach($array_name as $item){
    echo "$i: $item\n";
    $i ++;
  }
}

$another_array = array(1 => 'I Like Emacs', 3 => 'Vim is also good',);
var_dump($another_array);

$big_array = array_merge($another_array, $auto_key_array);
var_dump($big_array);
print_array($big_array);

// empty array
$e_array = array();

array_push($e_array, 'Yellow', 'Green');
var_dump($e_array);


?>