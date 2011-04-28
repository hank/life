# Set of overlapping jobs with different periods
# They all pay the same
# Algorithm finds optimal set of jobs (maximum number taken)
# where none overlap.
# Inspired by Skiena 2nd ed., sec. 1.2
jobs = {"Casablanca"    => [0, 6],
        "Teen Wolf"     => [2, 5],
        "The Matrix"    => [1, 4],
        "Patton"        => [3, 9],
        "Platoon"       => [5, 6],
        "Gandhi"        => [4, 8],
        "The Room"      => [5, 6],
        "Power Rangers" => [7, 9],
}.to_a

# First, sort the jobs by when they end
jobs.sort!{|x,y| x[1][1] <=> y[1][1]}

while !jobs.empty?
    # We know the first job ends the soonest
    puts jobs[0].to_s
    # Now simply delete it, and anything intersecting it
    etime = jobs[0][1][1]
    jobs.delete_at(0) while !jobs[0].nil? and jobs[0][1][0] < etime
    # Repeat!
end
