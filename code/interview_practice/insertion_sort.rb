# Simple insertion sort review
def is!(ar)
  ar.each_index do |i|
    next if i == 0
    j = i
    while j > 0 && ar[j] < ar[j-1]
        t = ar[j]
        ar[j] = ar[j-1]
        ar[j-1] = t
        j -= 1
    end
  end
end

a = [4,2,3,5,6,3,2,5,2,5,2,6,34,54,65,7,3,23,34,2,3,-2,4,5,-324,34,2,4,6]
is!(a)
puts a
