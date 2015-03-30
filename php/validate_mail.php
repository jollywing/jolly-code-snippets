<?php
function is_vail_mail_addr($email){
  $patt = '/^([a-z0-9+_.-])+@([a-z0-9_-]+\.)+[a-z]{2,5}$/i';
  if(preg_match($patt, $email )) {
    return TRUE;
  } else {
	return FALSE;
  }
}

$mails = array('_Iamgood@',
               'solid_tude@163.com',
               'jiqingwu@gmail.com',
               'jiqing-11@sina.com.cn',
               );
foreach($mails as $mail_addr){
  echo "$mail_addr: ";
  if(is_vail_mail_addr($mail_addr)){
    echo "VALID.\n";
  }
  else {
    echo "INVALID!\n";
  }
}

// '.', '+', in a character class need not back slashed.
// '-' is the last character in a character class, it will be regared a normal character
$patt = '/[a-z._+-]+@/i';
if(preg_match($patt, '-')){
  echo "CONTAINED\n";
}
else
echo "NOT contained\n";
?>