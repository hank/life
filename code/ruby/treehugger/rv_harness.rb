
# Mongrel harness for Camping apps with Rv. 
# Version 3

require 'rubygems'
require 'mongrel'
require 'mongrel/camping'
require 'rv'

app_name, port = Rv.env('app'), Rv.env('port')

# Load the Camping app
require app_name
app = Rv.classify(app_name)

# Configure your database
app::Models::Base.establish_connection(
  :adapter => 'sqlite3',
  :dbfile => "/etc/rv/treehugger.db"
)

#app::Models::Base.logger = Logger.new("#{app_name}.log")
app::Models::Base.threaded_connections = false
app.create

Mongrel::Configurator.new :host => '127.0.0.1', :pid_file => Rv.pid_file do
  
  listener :port => port do    
    # setup routes
    uri '/', :handler => Mongrel::Camping::CampingHandler.new(app)
    uri '/static/', :handler => Mongrel::DirHandler.new("static/")    
    uri '/favicon.ico', :handler => Mongrel::Error404Handler.new('')

    # bootstrap the server
    setup_signals
    run
    write_pid_file
    join
  end
    
end

