CXXFLAGS=-g -std=c++11 -pedantic -Wall

tests := $(basename $(wildcard tests/*.test-in))
all-tests := $(addsuffix .test, $(tests))
all-expe := $(addsuffix .expe, $(tests))

.PHONY: all test %.test expe %.expe

all: test 
	@echo "$(all-tests)"
	@echo "Pasaron todos los tests!"

test: elcondor $(all-tests)

expe: elcondor experimentacion $(all-expe)

experimentacion:
	@mkdir -p experimentacion

%.test: %.test-in %.test-cmp
	@./elcondor < $< 2> /dev/null | diff -q $(word 2, $?) - >/dev/null || \
	(echo "Falló el test $@" && exit 1)

%.expe: %.test-in
	@./elcondor < $< > experimentacion/$(basename $(notdir $@)).stdout 2> experimentacion/$(basename $(notdir $@)).stderr

elcondor: elcondor.o disjoint_set_union.o
	$(CXX) $(CXXFLAGS) -o $@ $^