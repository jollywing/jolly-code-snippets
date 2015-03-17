<?php
$patt = '/\(\([^\(\)]*?\)\)/';
$subj = 'abcdeXeeeY((XabcYcddX))Xmmdkf((adjjkYxxx))';
$result = preg_replace_callback($patt, function ($matches) { 
    return str_replace('Y', '@', str_replace('X', '$', $matches[0]));
  }, $subj);
echo $result . "\n";

$subj = '- hello, Sir Tree.';

$s = 'abcdeXeeeY((XabXYXddX))Xmmdkf((adjjkYxxx))';
$count = 1;

while (0 < $count) {
    $s = preg_replace(
        array(
            '/(?<=\(\()([^\(\)X]*?)X/',
            '/X([^\(\)X]*?)(?=\)\))/',
        ),
        array(
            '\1$',
            '$\1',
        ),
        $s,
        -1,
        $count
    );

    var_dump($s);
}

/*
string(42) "abcdeXeeeY(($abXYXdd$))Xmmdkf((adjjkYxxx))"
string(42) "abcdeXeeeY(($ab$Y$dd$))Xmmdkf((adjjkYxxx))"
string(42) "abcdeXeeeY(($ab$Y$dd$))Xmmdkf((adjjkYxxx))"
 */
?>
