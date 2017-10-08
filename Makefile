.PHONY: test all

all: ej3.test

%.test: %
	make -C $<
