<?php
// 四年一闰，百年不闰，四百年再闰
function leap_year($year){
  if($year % 4 == 0 and $year % 100 != 0){
    return TRUE;
  }
  else if($year % 400 == 0) {
    return TRUE;
  }
  return FALSE;
}

$count = 0;

for($i = 2000; $i <= 2013; $i ++){
  if(leap_year($i)){
    echo "$i is leap year.\n";
    $count ++;
  }
  else {
    echo "$i is not leap year.\n";
  }
}

echo "From 2000 to 2013, there are $count leap years in total.\n";
?>