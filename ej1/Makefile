CXXFLAGS=-g -std=c++11 -pedantic -Wall

tests := $(basename $(wildcard tests/*.test-cmp))
all-tests := $(addsuffix .test, $(basename $(wildcard tests/*.test-cmp)))
all-expe := $(addsuffix .expe, $(basename $(wildcard tests/*.test-in)))

.PHONY: all test %.test expe %.expe

all: test
	@echo "$(all-tests)"
	@echo "Pasaron todos los tests!"

test: $(all-tests)

expe: experimentacion $(all-expe)

experimentacion:
	@mkdir -p experimentacion

%.test: %.test-in %.test-cmp topdown
	@./topdown < $< 2> /dev/null | diff -q $(word 2, $?) - >/dev/null || \
	(echo "Falló el test $@ en topdown" && exit 1)

%.expe: %.test-in topdown bottomup
	@./topdown < $< > experimentacion/topdown_$(basename $(notdir $@)).stdout 2> experimentacion/topdown_$(basename $(notdir $@)).stderr
	@./bottomup < $< > experimentacion/bottomup_$(basename $(notdir $@)).stdout 2> experimentacion/bottomup_$(basename $(notdir $@)).stderr

topdown: topdown.cpp main_topdown.cpp
	$(CXX) $(CXXFLAGS) -o $@ topdown.cpp main_topdown.cpp
