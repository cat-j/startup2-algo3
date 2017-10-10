.PHONY: test all

all: ej1.test ej3.test

%.test: %
	make -C $<
