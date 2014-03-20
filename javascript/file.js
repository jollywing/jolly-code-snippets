
var fs = require("fs");

var writer = fs.createWriteStream("test.txt");
writer.write("I'm Dickens!\n");
writer.end("Help me improve my finance.\n");