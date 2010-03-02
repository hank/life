require 'rubygems'
require 'ramaze'
require 'gpgme'

class GPGME::Signature
  # Add an id method
  def id
    self.to_s
  end
end

class CSSController < Ramaze::Controller
  map '/css'
  engine :Sass
  def main
    # Purposely empty
  end
end

class MainController < Ramaze::Controller
  layout :default
  engine :Haml

  def index
    # Purposely empty
  end

  # Accepts 'signed' data, which will be tested by GPGME
  def verify
    @sigs = []
    @orig_data = request.params['data']
    begin
      GPGME::verify(request.params['data'], nil, @plain) do |signature|
        @sigs << signature
      end
    rescue GPGME::Error => e
      @error = "GPGME Error: #{e.to_s}"
    #rescue
    #  @error = "Unspecified Error."
    end
  end
end
Ramaze.start
