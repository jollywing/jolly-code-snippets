
var http = require("http");

// onRequest is a callback function
var onRequest = function(request, response){
  console.log("A request is received");
  // 200 indicates http status
  response.writeHead(200, {"Content-type": "text/html"});
  response.write("<h1>Hello, world!</h1>");
  // response completed
  response.end();
}

function start(){
  http.createServer(onRequest).listen(8888);
  console.log("HTTP server started ...");
}

// export start
exports.startup = start;
