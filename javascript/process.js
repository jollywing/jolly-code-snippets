
// child_process is a builtin library
var proc = require('child_process');
console.log(process.platform);

// NOTE: the callback function need 3 args: error, stdout, stderr
proc.exec('mplayer --version', function(error, stdout, stderr){
  console.log(stdout);});
// proc.execFile('/usr/local/bin/mplayer', '--version');

var media_file = '~/media/gaoyuanlan.mp4';
proc.exec('mplayer -vo x11 '+media_file, function(error, stdout, stderr){});
// proc.execFile('mplayer', media_file);