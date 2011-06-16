var EventEmitter = require("events").EventEmitter;

function Dog(name)
{
  this.name = name;
}

Dog.prototype = new EventEmitter;
exports.Dog = Dog;
