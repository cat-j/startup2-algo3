CXXFLAGS=-g -std=c++11 -pedantic -Wall

all-tests := $(addsuffix .test, $(basename $(wildcard tests/*.test-in)))

.PHONY: test all %.test

all: test 
	@echo "$(all-tests)"
	@echo "Pasaron todos los tests!"

test: elcondor $(all-tests)

%.test: %.test-in %.test-cmp
	@./elcondor <$< 2>&1 | diff -q $(word 2, $?) - >/dev/null || \
	(echo "Falló el test $@" && exit 1)

elcondor: elcondor.o disjoint_set_union.o
	$(CXX) $(CXXFLAGS) -o $@ $^
