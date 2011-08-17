sys     = require('sys');
fs      = require('fs');
Inotify = require('inotify').Inotify;

var inotify = new Inotify();

function callback(ev) {
  console.log(sys.inspect(ev));
}

var home_dir = {
    path:      '/proc/5499/stat'
  , watch_for: Inotify.IN_ALL_EVENTS
  , callback:  callback
};

var home_watch_descriptor = inotify.addWatch(home_dir);
