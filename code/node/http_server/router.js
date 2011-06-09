var fs = require("fs");

function route(handle, path, response, postData)
{
  if(typeof handle[path] === 'function') {
    handle[path](response, postData);
  } else {
    // See if we have a file
    try {
      var filename = path.slice(1);
      console.log('Trying to access '+filename+'.');
      var stat = fs.lstatSync(filename);
      if(stat.isFile() || stat.isSymbolicLink())
      {
        handle["file"](response, filename);
      }
    } catch(e) {
      console.log(e);
      console.log("Handler for " + path + " doesn't exist!");
      response.writeHead(404, {"Content-Type": "text/html"});
      response.write("404 Not Found");
      response.end();
    }
  }
}

exports.route = route;
