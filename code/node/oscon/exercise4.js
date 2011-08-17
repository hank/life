var http = require('http')
var port = 8080
http.createServer(function(req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'})
  if(req.headers['user-agent'].match(/Webkit/i)) {
    res.end("<marquee" +
            "  scrollamount=50" +
            "  width=100% " +
            "  >I'm Learning Node!</marquee>" + 
            "And you're using a Webkit browser - nice job!"
           )
  }
  else {
    res.end("<marquee" +
            "  scrollamount=50" +
            "  width=100% " +
            "  >I'm Learning Node!</marquee>" + 
            "And you're sucking it up in some crap non-Webkit" +
            "browser"
           )
  }
}).listen(port, "127.0.0.1")
console.log("Server running on " + port)
