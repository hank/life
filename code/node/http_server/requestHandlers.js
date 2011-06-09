var qs = require("querystring");
var fs = require("fs");
var helpy = require("../helpy");

function list(response, postData) {
  console.log("Request handler 'list' was called.");
  fs.readdir(".", function(err, files) {
    var fmapped = files.map(function(o){
      return '<a href="/'+o+'">'+o+'</a>';
    });

    var body = '<html>'+
     '<body>'+
     fmapped.join('<br/>') +
     '</body>'+
     '</html>';
    response.writeHead(200, {"Content-Type":"text/html"});
    response.write(body);
    response.end();
  });
}

function start(response, postData) {
  console.log("Request handler 'start' was called.");
  var body = '<html>'+
   '<body>'+
   '<ul><li><a href="/list">List</a></li></ul>'+
   '<form action="upload" method="post">'+
   '<textarea name="text" rows=20 cols=60></textarea>'+
   '<input type="submit" value="Submit text" />'+
   '</form>'+
   '</body>'+
   '</html>';
  response.writeHead(200, {"Content-Type":"text/html"});
  response.write(body);
  response.end();
}

function upload(response, postData) {
  console.log("Request handler 'upload' was called.");
  response.writeHead(200, {"Content-Type":"text/html"});
  response.write("You sent:<pre>"+qs.parse(postData)["text"]+"</pre>");
  response.end();
}

function file(response, filename) {
  console.log("Request handler 'file' was called.");
  // Read the file from the disk
  fs.readFile(filename, "utf8", function(err, data) {
    if(err) throw err;
    // Escape html
    var escapedData = helpy.html.escapeHTML(data);
    response.writeHead(200, {"Content-Type":"text/html"});
    response.write("Here's your file:\n<pre>"+escapedData+"</pre>");
    response.end();
  });
}

exports.start = start;
exports.upload = upload;
exports.file = file;
exports.list = list;
