var util  = require('util'),
    sys   = require('sys'),
    spawn = require('child_process').spawn,
    ruby  = spawn('ruby', [__dirname + '/process.rb']);

function trim(str) {
  return str.replace(/^\s+|\s+$/, '');
}

ruby.stdout.on('data', function(data) {
  console.log('stdout: ' + trim(data.toString()));
});

ruby.stdout.on('end', function(data) {
  ruby.stdout.flush();
});

ruby.stderr.on('data', function(data) {
  console.log('stderr: ' + data);
});

ruby.on('exit', function(code, signal) {
  if(code != null) console.log('exit: ' + code);
  else if(signal != null) console.log('killed: ' + signal);
});

ruby.stdin.write("ping\n");
ruby.stdin.end();
