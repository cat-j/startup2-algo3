.PHONY: test all

all: ej1.test ej2.test ej3.test

expe: ej1.expe ej2.expe ej3.expe

%.test: %
	@make -C $<

%.expe: %
	@make -C $< expe
