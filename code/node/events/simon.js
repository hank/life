var Dog = require("./dog").Dog;

var simon = new Dog('simon');

simon.on('bark', function() {
  console.log("'Woof!', says "+this.name);
});

setInterval(function() {
  simon.emit('bark');
}, 500);
