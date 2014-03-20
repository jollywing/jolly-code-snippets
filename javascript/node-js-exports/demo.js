
module.exports="hello, world";

// Since module.exports has been assigned to a string object
// Assignment with exports will be invalid.
exports.add = function(v1, v2){
  return v1 + v2;
};