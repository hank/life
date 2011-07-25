var http = require('http')
var qs = require('querystring')

var srv = http.createServer(function(req, res) {
  if(req.method == "POST") {
    var data = "";
    req.on('data', function(chunk) {data += chunk})
    req.on('end', function() {
      var POST = qs.parse(data)
      res.writeHead(200, {"Content-Type" : "text/html"})
      res.write(JSON.stringify(POST))
      console.log(JSON.stringify(POST))
      res.end()
    })
  } else {
    res.writeHead(200, {"Content-Type" : "text/html"})
    res.end("<p>Make a post request, bro!</p>" +
      "<form method=post action=/>" +
      "<input type=text name='foo'/>" +
      "<input type=submit />" +
      "</form>"
    )
  }
}).listen(8080, "127.0.0.1")
