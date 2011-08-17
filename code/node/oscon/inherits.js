var util = require('util'),
    EE   = require('events').EventEmitter

var MyClass = function() {
  EE.call(this)
}

util.inherits(MyClass, EE)

MyClass.prototype.write = function() {
    util.puts("Calling myMethod")
    this.emit("data", data)
}

var thing = new MyClass()
console.log(thing)
thing.on('data', function(chunk) { 
  util.puts("Chunk: " + chunk)
})
