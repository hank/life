INCLUDE=../googletest-read-only/include
LIBS=../googletest-read-only/scons/build/dbg/scons
UNIT_TESTS=factorial_unittest
TARGETS=factorial

all: ${TARGETS}

factorial: factorial.cpp

test: ${UNIT_TESTS}

factorial_unittest: factorial_unittest.cc
	g++ -o $@ $< -L${LIBS} -I${INCLUDE} -lgtest -lgtest_main -lpthread

clean: ${UNIT_TESTS} ${TARGETS}
	rm $<

