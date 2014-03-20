
// maybe you need `npm install clivas'
var clivas = require('clivas');

var frame = 0;

setInterval(function() {
	clivas.clear(); // clears the canvas
	clivas.line('hello world (#frame '+frame+')');
	clivas.line('{red:also} {green:colors}!');
    clivas.line('{blue+inverse:blue inverse!}');
	frame++;
}, 1000);
