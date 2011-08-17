var http = require('http')
var port = 8080
http.createServer(function(req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'})
  res.end("I'm learning Node")
}).listen(port, "127.0.0.1")
console.log("Server running on " + port)
