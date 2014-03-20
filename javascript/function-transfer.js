
function say(something) {
  console.log(something);
}

function execute(someFunction, value){
  someFunction(value);
}

execute(say, "hello, the world!");

// Transfer it at the same time of definition
execute(function(something){
  console.log("I won't say: %s", something);
}, "fuck!");