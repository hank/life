TARGETS=basic_heap merge_sort2
all: $(TARGETS)

basic_heap: basic_heap.c
	gcc -Wall -o $@ $< -lm

merge_sort2: merge_sort2.cpp
	g++ -g -Wall -o $@ $<

clean:
	rm $(TARGETS)
