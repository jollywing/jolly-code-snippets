
exports.add = function(v1, v2) {
  console.log("exports.add is called");
  return v1 + v2;
};

module.exports.add = function(v1, v2) {
  console.log("module.exports.add is called");
  return v1 + v2;
};

exports.name = ["sum", 'Sum', 'SUM'];
