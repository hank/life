var qs = require("querystring");
var fs = require("fs");
var jade = require("jade");
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
  jade.renderFile('./templates/start.jd', function(err, html) {
    if(err) throw err;
    response.writeHead(200, {"Content-Type":"text/html"});
    response.write(html);
    response.end();
  });
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
