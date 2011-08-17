var http = require('http')
var port = 8080
http.createServer(function(req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'})
  res.end("<marquee" +
          "  scrollamount=50" +
          "  width=100% " +
          "  >I'm Learning Node!</marquee>" + 
          "And you're using " + req.headers['user-agent']
         )
}).listen(port, "127.0.0.1")
console.log("Server running on " + port)
