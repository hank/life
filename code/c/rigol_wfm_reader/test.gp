set title "Filename"
set xlabel "Time"
set ylabel "Signal"
set key right nobox
set term gif
set output "test.gif"
plot [0:8192] 'tmp.1.data' with lines, 'tmp.2.data' with lines
