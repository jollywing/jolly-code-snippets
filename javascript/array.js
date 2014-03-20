
var arr = new Array(3);
arr[0] = "Hello";
arr[1] = 1;
arr[2] = "Tree";

// Array.slice(start, end)
// Get a subArray from the Array, from start to end, the end not included.
// The `start' position need to be in front of the 'end',
// otherwise you will get a empty Array
// `start' is neccessary, and `end' is optimal
console.log(arr.slice(0,1)); // ['Hello']
console.log(arr.slice(1)); //[ 1, 'Tree' ]
console.log(arr.slice(-1)); // ['Tree'] the last one