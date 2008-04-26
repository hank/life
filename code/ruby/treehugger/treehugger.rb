#!/usr/bin/env ruby

# Treehugger
# A bash environment daemon by Erik Gregg
# 3/30/08
#
# The server is run like any camping app.  The client connects to 
# port 3301 of the server to get the configuration, like so:
#
# FILENAME=/tmp/treehugger-`date +%s%N`; 2>/dev/null wget -O $FILENAME  http://localhost:3301/out && source $FILENAME && rm $FILENAME


require 'rubygems'
require 'camping'
require 'camping/db'
require 'camping/session'
  
Camping.goes :Treehugger

module Treehugger
    include Camping::Session
end

module Treehugger::Models
    class Alias < Base
      belongs_to :user
      belongs_to :machine
    end
    class EnvVariable < Base
      belongs_to :user
      belongs_to :machine
    end
    class User < Base; end
    class User < Base; end

    class CreateTheBasics < V 1.0
      def self.up
        create_table :treehugger_aliases do |t|
          t.column :name, :string, :limit => 255
          t.column :command, :text
          t.column :user_id, :integer
          t.column :machine_id, :integer
          t.column :active,     :boolean
        end
        create_table :treehugger_env_variables do |t|
          t.column :name, :string, :limit => 255
          t.column :command, :text
          t.column :user_id, :integer
          t.column :machine_id, :integer
          t.column :active,     :boolean
        end
        create_table :treehugger_machines do |t|
          t.column :name,    :string,  :limit => 255
          t.column :active,     :boolean
        end
        create_table :treehugger_users do |t|
          t.column :username,    :string,  :limit => 255
          t.column :password,   :string, :limit => 255
          t.column :active,     :boolean

        end
        User.create :username => 'hank', :password => 'ralree', :active => 1
      end
      def self.down
        drop_table :treehugger_posts
        drop_table :treehugger_users
        drop_table :treehugger_comments
      end
    end
end

module Treehugger::Controllers
    class Index < R '/'
        def get
            @env_vars = EnvVariable.find :all
            @aliases = Alias.find :all
            render :index
        end
    end
     
    class AddEnvVar
        def get
            unless @state.user_id.blank?
                @user = User.find @state.user_id
                @env_var = EnvVariable.new
            end
            render :add_env_var
        end
        def post
            unless @state.user_id.blank?
                env_var = EnvVariable.create :name => input.env_var_title, 
                            :command => input.env_var_command,
                            :machine_id => input.env_var_machine_id,
                            :user_id => @state.user_id
                redirect ViewEnvVar, env_var
            end
        end
    end

    class AddAlias
        def get
            unless @state.user_id.blank?
                @user = User.find @state.user_id
                @alias = Alias.new
            end
            render :add_alias
        end
        def post
            unless @state.user_id.blank?
                aliass = Alias.create :name => input.alias_name, 
                            :command => input.alias_command,
                            :machine_id => input.alias_machine_id,
                            :user_id => @state.user_id
                redirect ViewAlias, aliass
            end
        end
    end

    class Info < R '/info/(\d+)', '/info/(\w+)/(\d+)', '/info', '/info/(\d+)/(\d+)/(\d+)/([\w-]+)'
        def get(*args)
            div do
                code args.inspect; br; br
                code @env.inspect; br
                code "Link: #{R(Info, 1, 2)}"
            end
        end
    end

    class ViewEnvVar < R '/view_env_var/(\d+)'
        def get env_var_id 
            @env_var = EnvVariable.find env_var_id
            render :view_env_var
        end
    end

    class ViewAlias < R '/view_alias/(\d+)'
        def get alias_id
            @alias = Alias.find alias_id
            render :view_alias
        end
    end
     
    class EditEnvVar < R '/edit_env_var/(\d+)', '/edit_env_var'
        def get env_var_id
            unless @state.user_id.blank?
                @user = User.find @state.user_id
            end
            @env_var = EnvVariable.find env_var_id
            render :edit_env_var
        end
     
        def post
            unless @state.user_id.blank?
                @env_var = EnvVariable.find input.env_var_id
                @env_var.update_attributes :name => input.env_var_name, :command => input.env_var_command, :active => input.env_var_active
                redirect ViewEnvVar, @env_var
            end
        end
    end

    class EditAlias < R '/edit_alias/(\d+)', '/edit_alias'
        def get alias_id
            unless @state.user_id.blank?
                @user = User.find @state.user_id
            end
            @alias = Alias.find alias_id
            render :edit_alias
        end
     
        def post
            unless @state.user_id.blank?
                @alias = Alias.find input.alias_id
                @alias.update_attributes :name => input.alias_name, :command => input.alias_command, :active => input.alias_active
                redirect ViewAlias, @alias
            end
        end
    end
     
    class Login
        def post
            @user = User.find :first, :conditions => ['username = ? AND password = ?', input.username, input.password]
     
            if @user
                @login = 'login success !'
                @state.user_id = @user.id
            else
                @login = 'wrong user name or password'
            end
            render :login
        end
    end
     
    class Logout
        def get
            @state.user_id = nil
            render :logout
        end
    end
     
    class Help < R '/help'
      def get
        render :help
      end
    end

    class Text < R '/out'
      def get
        @headers["Content-Type"] = "text/plain; charset=utf-8"
        @body = "# Treehugger Configuration"
        @alii = Alias.find(:all).map{|a| "alias #{a.name}='#{a.command}'"}.join("\n")
        @env = EnvVariable.find(:all).map{|a| "export #{a.name}='#{a.command}'"}.join("\n")
        @body += %{
# Aliases
#{@alii}

# Environment Variables
#{@env}
        }
      end
    end

    class Style < R '/styles.css'
        def get
            @headers["Content-Type"] = "text/css; charset=utf-8"
            @body = %{
                body {
                    font-family: sans-serif;
                }
                div.header {
                    background-color: #efe;
                    margin: 0; padding: 10px;
                }
                h1 {
                    display: inline;
                }
                h2 {
                    border-bottom: 1px solid black;
                }
                div.content {
                    padding: 10px;
                }
                table.varlist {
                  width: 100%;
                  border-width: 1px 1px 1px 1px;
                  border-spacing: 2px;
                  border-style: inset inset inset inset;
                  border-color: gray gray gray gray;
                  border-collapse: separate;
                  background-color: white;
                }
                table.varlist th {
                  border-width: 1px 1px 1px 1px;
                  padding: 2px 2px 2px 2px;
                  border-style: outset outset outset outset;
                  border-color: green green green green;
                  background-color: white;
                  -moz-border-radius: 3px 3px 3px 3px;
                }
                table.varlist td {
                  border-width: 1px 1px 1px 1px;
                  padding: 2px 2px 2px 2px;
                  border-style: outset outset outset outset;
                  border-color: green green green green;
                  background-color: white;
                  -moz-border-radius: 3px 3px 3px 3px;
                }
            }
        end
    end
end

module Treehugger::Views

    def layout
      html do
        head do
          title 'treehugger'
          link :rel => 'stylesheet', :type => 'text/css', 
               :href => '/styles.css', :media => 'screen'
        end
        body do
          div.header do
            h1 { a 'treehugger', :href => R(Index) }
            a 'wtf?', :href => R(Help), :style => "font-size='30%';float:right;"
          end
          div.content do
            self << yield
          end
        end
      end
    end

    def index
      h2 'Environment Variables'
      if @env_vars.empty?
        p 'No environment variables found.'
      else
        table.varlist do 
          for env_var in @env_vars
            _env_var(env_var)
          end
        end
      end
      p { a 'Add', :href => R(AddEnvVar) }
      h2 'Aliases'
      if @aliases.empty?
        p 'No aliases found.'
      else
        table.varlist do 
          for aliass in @aliases
            _alias(aliass)
          end
        end
      end
      p { a 'Add', :href => R(AddAlias) }
    end

    def login
      p { b @login }
      p { a 'Continue', :href => R(Index) }
    end

    def logout
      p "You have been logged out."
      p { a 'Continue', :href => R(Index) }
    end

    def add_env_var
      if @user
        _env_var_form(@env_var, :action => R(AddEnvVar))
      else
        _login
      end
    end

    def add_alias
      if @user
        _alias_form(@alias, :action => R(AddAlias))
      else
        _login
      end
    end

    def edit_env_var
      if @user
        _env_var_form(@env_var, :action => R(EditEnvVar))
      else
        _login
      end
    end

    def edit_alias
      if @user
        _alias_form(@alias, :action => R(EditAlias))
      else
        _login
      end
    end

    def view_env_var
      h2 @env_var.name
      p @env_var.command
    end

    def help
      p "Simply jam this in your ~/.bashrc"
      pre %{
      thupdate() {
        FILENAME=/tmp/treehugger-`date +%s%N`; 
        2>/dev/null wget -O $FILENAME  http://treehugger.who.ath.cx/out && \\ 
          source $FILENAME && \\
          rm $FILENAME;
      }
      thupdate
      }
    end

    def view_alias
      h2 @alias.name
      p @alias.command
    end

    # partials
    def _login
      form :action => R(Login), :method => 'post' do
        label 'Username', :for => 'username'; br
        input :name => 'username', :type => 'text'; br

        label 'Password', :for => 'password'; br
        input :name => 'password', :type => 'text'; br

        input :type => 'submit', :name => 'login', :value => 'Login'
      end
    end

    def _env_var(env_var)
      tr do
        td { b env_var.name }
        td env_var.command
        td do
          [a("Edit", :href => R(EditEnvVar, env_var)), 
           a("View", :href => R(ViewEnvVar, env_var))].join " | "
        end
      end
    end

    def _alias(aliass)
      tr do
        td aliass.name
        td aliass.command
        td do
          [a("Edit", :href => R(EditAlias, aliass)), 
           a("View", :href => R(ViewAlias, aliass))].join " | "
        end
      end
    end

    def _env_var_form(env_var, opts)
      p { "You are logged in as #{@user.username} | #{a 'Logout', :href => R(Logout)}" }
      form({:method => 'post'}.merge(opts)) do
        label 'Name', :for => 'env_var_name'; br
        input :name => 'env_var_name', :type => 'text', 
              :value => env_var.name; br

        label 'Command', :for => 'env_var_command'; br
        textarea env_var.command, :name => 'env_var_command'; br

        input :type => 'hidden', :name => 'env_var_id', :value => env_var.id
        input :type => 'submit'
      end
    end

    def _alias_form(aliass, opts)
      p { "You are logged in as #{@user.username} | #{a 'Logout', :href => R(Logout)}" }
      form({:method => 'post'}.merge(opts)) do
        label 'Name', :for => 'alias_name'; br
        input :name => 'alias_name', :type => 'text', 
              :value => aliass.name; br

        label 'Command', :for => 'alias_command'; br
        textarea aliass.command, :name => 'alias_command'; br

        input :type => 'hidden', :name => 'alias_id', :value => aliass.id
        input :type => 'submit'
      end
    end
end
 
def Treehugger.create
    Camping::Models::Session.create_schema
    Treehugger::Models.create_schema :assume => (Treehugger::Models::EnvVariable.table_exists? ? 1.0 : 0.0)
end

