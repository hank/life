CFLAGS=-Lgmp/lib -Igmp/include
TARGETS=basic_heap merge_sort2 quick_sort bfs abstract_factory_pattern \
        builder_pattern adapter_pattern fizzbuzz fibo_mat money fibo_gmp_native
all: $(TARGETS)

fibo_gmp_native: fibo_gmp_native.c
	gcc -Wall $(CFLAGS) -o $@ $< -lgmp

fibo_mat: fibo_mat.c
	gcc -Wall $(CFLAGS) -o $@ $< -lgmp

fizzbuzz: fizzbuzz.c
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
