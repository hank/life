var http = require("http");
var url = require("url");

function start(port, route, handle) {
  function onRequest(request, response) {
      var postData = "";
      var path = url.parse(request.url).pathname;
      console.log("Request for "+path+" received!");
      request.setEncoding("utf8");
      request.addListener("data", function(postDataChunk) {
        postData += postDataChunk;
        console.log("Received POST data chunk '" + postDataChunk + "'.");
      });
      request.addListener("end", function() {
        route(handle, path, response, postData);
      });
  }
  http.createServer(onRequest).listen(port);
  console.log("Server Started on port "+port+"...");
}

exports.start = start;
