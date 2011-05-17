TARGETS=basic_heap merge_sort2 quick_sort money
all: $(TARGETS)

money: money.cpp
	g++ -Wall -o $@ $<

bfs: bfs.cpp
	g++ -Wall -o $@ $<

basic_heap: basic_heap.c
	gcc -Wall -o $@ $< -lm

merge_sort2: merge_sort2.cpp
	g++ -g -Wall -o $@ $<

quick_sort: quick_sort.cpp
	g++ -g -Wall -o $@ $<

clean:
	rm $(TARGETS)
