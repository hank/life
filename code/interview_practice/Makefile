CFLAGS=-Lgmp/lib -Igmp/include
TARGETS=basic_heap merge_sort2 quick_sort bfs abstract_factory_pattern \
        builder_pattern adapter_pattern fizzbuzz money weird_sort_string \
        reverse_linked_list biggest_subarray
all: $(TARGETS)

fibo_gmp_native: fibo_gmp_native.c
	gcc -Wall $(CFLAGS) -o $@ $< -lgmp

fibo_mat: fibo_mat.c
	gcc -Wall $(CFLAGS) -o $@ $< -lgmp

biggest_subarray: biggest_subarray.c
	gcc -Wall -o $@ $<

sel_sort: sel_sort.c
	gcc -Wall -o $@ $<

reverse_linked_list: reverse_linked_list.c
	gcc -Wall -o $@ $<

fizzbuzz: fizzbuzz.c
	gcc -Wall -o $@ $<

weird_sort_string: weird_sort_string.c
	gcc -Wall -o $@ $<

adapter_pattern: adapter_pattern.cpp
	g++ -Wall -o $@ $<

builder_pattern: builder_pattern.cpp
	g++ -Wall -o $@ $<

abstract_factory_pattern: abstract_factory_pattern.cpp
	g++ -Wall -o $@ $<

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
