CXXFLAGS=-g -std=c++11 -pedantic -Wall

tests := $(basename $(wildcard tests/*.test-in))
all-tests := $(addsuffix .test, $(tests))
all-expe := $(addsuffix .expe, $(tests))

.PHONY: all test %.test expe %.expe

all: test 
	@echo "$(all-tests)"
	@echo "Pasaron todos los tests!"

test: main $(all-tests)

expe: main experimentacion $(all-expe)

experimentacion:
	@mkdir -p experimentacion

%.test: %.test-in %.test-cmp
	@./main < $< 2> /dev/null | diff -q $(word 2, $?) - >/dev/null || \
	(echo "Falló el test $@" && exit 1)

%.expe: %.test-in
	@./main < $< > experimentacion/$(basename $(notdir $@)).stdout 2> experimentacion/$(basename $(notdir $@)).stderr

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^
