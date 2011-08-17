var app = require('express').createServer()

app.get('/', function(req, res) {
  res.send("Oh Hello!")
})

app.get(/([0-9]+)/, function(req, res) {
  res.send(req.params)
})

app.all('*', function(req, res) {
  res.send("I don't understand " + req.url)
})

app.listen(3000)
