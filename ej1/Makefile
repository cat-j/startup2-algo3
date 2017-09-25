CXXFLAGS=-g -std=c++14 -pedantic -Wall

test: ej1 prueba1.in uniforme_1_30.in prueba.in
	./ej1 < prueba1.in
	./ej1 < uniforme_1_30.in
	./ej1 < prueba.in

topdown:
	-g++ -std=c++11 topdown.cpp main_topdown.cpp -o topdown

.PHONY: topdown
