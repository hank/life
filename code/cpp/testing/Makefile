INCLUDE=googletest-read-only/include
LIBS=googletest-read-only/mybuild
UNIT_TESTS=factorial_unittest
TARGETS=

all: ${TARGETS}

factorial: factorial.cc

test: ${UNIT_TESTS}

factorial_unittest: factorial_unittest.cc
	g++ -o $@ $< -L${LIBS} -I${INCLUDE} -lgtest -lgtest_main -lpthread

clean: ${UNIT_TESTS} ${TARGETS}
	rm $<
