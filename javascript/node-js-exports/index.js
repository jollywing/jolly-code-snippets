
// demo is exported as a string
var word=require("./demo");

console.log(word);

// Since word is exported as a string object,
// it has no method `add', this will result in an error.
// var sum = word.add(1, 3);

var sum = require("./sum");
console.log(sum.name[2]);
console.log(sum.add(100, 8899));