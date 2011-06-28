INCLUDE=../../cpp/testing/googletest-read-only/include
LIBS=../../cpp/testing/googletest-read-only/build

TARGETS=heaps prim htable2 itoa fun_with_strings bintree \
        queue quicksort_test radix_sort subsets

all: $(TARGETS)

clean:
	rm $(TARGETS)

quicksort_test: quicksort_test.cpp qsort.h
	g++ -O0 -g -o $@ $< -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

bintree: bintree.c
	gcc -Wall -o $@ $<

subsets: subsets.c
	gcc -Wall -o $@ $< -lm

heaps: heaps.c
	gcc -Wall -o $@ $<

fun_with_strings: fun_with_strings.c
	gcc -Wall -g -o $@ $<

itoa: itoa.c
	gcc -Wall -o $@ $<

radix_sort: radix_sort.cpp
	g++ -g -Wall -o $@ $<

htable2: htable2.cpp
	g++ -g -Wall -o $@ $<

prim: prim.c
	gcc -Wall -o $@ $<

queue: queue.cpp
	g++ -Wall -o $@ $<
