var http = require('http')

var options = { 'host':'www.nytimes.com',
                'port': 80,
                'path': '/index.html'
              }

http.get(options, function(res) {
  res.on('data', function(chunk) {
    console.log("Chunk: " + chunk)
  })
})
