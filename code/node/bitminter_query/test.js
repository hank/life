var fs = require('fs')
var dateFormat = require('dateformat')
var bitminter = require('bitminter')
var my_util = require('./my_util')
// Put your API key in a file called KEY
fs.readFile('KEY', function(err, data) {
    if(err) throw err;
    // Read key from file
    data = data.toString().replace(/(\n|\r)+$/,'');
    bitminter.apikey = data;

    // Fetch data
    bitminter.get( 'users', function( err, user ) {
        if(err) throw err;
        for(var i=0; i<user.workers.length; ++i)
        {
            console.log(user.workers[i]);
            console.log("Worker: " + user.workers[i].name);
            /* Last Work Received */
            if(user.workers[i].last_work == 0) {
               console.log("Last work received: Never");
            } else {   
                var last_work = new Date(user.workers[i].last_work * 1000);
                if(my_util.is_today(last_work)) {
                    console.log("Last work received: Today " + dateFormat(last_work, "HH:MM"));
                } else {
                    console.log("Last work received: " + dateFormat(last_work, "yyyymmdd HH:MM"));
                }
            }
        }
    });
    bitminter.get( 'pool/blocks?commodity=BTC', function( err, blocks ) {
        //console.log( err || blocks )
    });
});
