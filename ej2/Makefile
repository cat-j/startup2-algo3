main: main.cpp
	g++ -std=c++11 main.cpp -o getNetWork

test: experimentacion/normal_10nodos_mu30_sigma5.in experimentacion/uniforme_10nodos_1a30.in
	./getNetWork < experimentacion/normal_10nodos_mu30_sigma5.in > experimentacion/normalOutput.out 2> experimentacion/logNormal.out
	./getNetWork < experimentacion/uniforme_10nodos_1a30.in > experimentacion/uniformeOutput.out 2> experimentacion/logUniforme.out