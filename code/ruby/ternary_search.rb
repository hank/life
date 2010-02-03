# A little toy ternary search
class Array
  def tern_search(i)
    found = nil
    piv1 = self.length/3
    piv2 = piv1*2
    c = 0
    while found.nil?
      c += 1
      #puts "piv1 = #{piv1}, piv2 = #{piv2}"
      case i <=> self[piv1-1]
        when -1 # Less Than
          #puts "#{i} is less than #{self[piv1-1]}."
          piv1 = (piv1 / 3)
        when 0 # Equal!
          #puts "#{i} is equal to #{self[piv1-1]}."
          found = piv1-1
          next
        when 1 # Greater Than
          # Check piv2
          #puts "#{i} is greater than #{self[piv1-1]}."
          piv1 += (piv2 - piv1) / 3
      end

      case i <=> self[piv2-1]
        when -1 # Less Than
          #puts "#{i} is less than #{self[piv2-1]}."
          piv2 -= (piv2 - piv1 )/3
        when 0 # Equal!
          #puts "#{i} is equal to #{self[piv2-1]}."
          found = piv2-1
          next
        when 1 # Greater Than
          #puts "#{i} is greater than #{self[piv2-1]}."
          piv2 += (piv2 - piv1) / 3 * 2
      end
    end
    puts "#{c} iterations required."
    return found
  end
end
a = (1..1024).to_a
b = 437
idx = a.tern_search(b)
puts "Found #{b} at index #{idx}"
