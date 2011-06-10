var EventEmitter = require("events").EventEmitter;

function Dog(name)
{
  this.name = name;
}

Dog.prototype.__proto__ = EventEmitter.prototype;
exports.Dog = Dog;
