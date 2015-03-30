<?php
function weekday_cn($wday) {
  $result = "";
  switch($wday) {
    case 0:
      $result = "星期日";
      break;
    case 1:
      $result = "星期一";
      break;
    case 2:
      $result = "星期二";
      break;
    case 3:
      $result = "星期三";
      break;
    case 4:
      $result = "星期四";
      break;
    case 5:
      $result = "星期五";
      break;
    default:
      $result = "星期六";
  }
  return $result;
}

$today = getdate();
$result = "当前时间是" . $today["year"] . "年" .
          $today["mon"] . "月" . $today["mday"] . "日 ";
$result .= $today["hours"] . ":" . $today["minutes"] . ":" . $today["seconds"];
$result .= " " . weekday_cn($today["wday"]);
echo $result;

$datetime = date("Y-m-d H:i:s");
//$datetime = strftime('%Y-%m-%d %H:%M:%S');
echo "当前时间是$datetime.\n";

$time_array = strptime($datetime, '%Y-%m-%d %H:%M:%S');
$year = $time_array['tm_year'] + 1900;
$month = $time_array['tm_mon'] + 1;
$day = $time_array['tm_mday'];
$hour = $time_array['tm_hour'];
$min = $time_array['tm_min'];
$sec = $time_array['tm_sec'];
echo "$year-$month-$day $hour:$min:$sec\n";
?>