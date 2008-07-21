# A nice little function to generate 
def find_happy_numbers(arr)
  return arr.class if arr.class != Array and arr.class != Range
  happs = {}
  begin
    arr.each do |x|
      z = x.to_i
      while(z != 1)
        prevz = z
        z = z.to_s.split(//).inject(0) {|v,c| v.to_i + c.to_i**2}
        if(z<prevz && happs[z].nil?)
          #puts "#{x} is not happy."
          break
        end
      end
      if(z==1)
        #puts "#{x} is a happy number"
        happs[x] = 1
      end
    end
  #rescue
    
  end
  happs.keys.sort
end

if __FILE__ == $0
  happies = find_happy_numbers(1..100_000)
  puts happies.join(", ")
end
