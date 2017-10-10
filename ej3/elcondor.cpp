#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "elcondor.h"
#include "disjoint_set_union.h"

struct arista {
	int inicio;
	int fin;
	int costo;

	arista(int o, int f, int c) : inicio(o), fin(f), costo(c) {}

	bool operator<(const arista a) const {
		return costo < a.costo;
	}
};

class ElCondor
{
public:
	ElCondor(int c, int f, vector<arista> r);
	vector<arista> rutasOptimas();

private:
	int fabricas;
	int clientes;
	vector<arista> rutas;
	Disjoint_Union conjuntos;
	vector<bool> tieneFabrica;
};

ElCondor::ElCondor(int f, int c, vector<arista> r)
	: fabricas(f)
	, clientes(c)
	, rutas(r)
	, conjuntos(f + c)
	, tieneFabrica(f + c, false) {
	for (int i = 0; i < f; ++i) {
		// todos los conjuntos que tienen una fábrica son marcados
		tieneFabrica[i] = true;
	}
}

vector<arista> ElCondor::rutasOptimas() {
	vector<arista> res;
	sort(rutas.begin(), rutas.end());

	for (auto& ruta : rutas) {
		auto rep1 = conjuntos.find(ruta.inicio);
		auto rep2 = conjuntos.find(ruta.fin);
		if (rep1 == rep2) { // ya estan en el mismo conjunto
			continue;
		}

		if (tieneFabrica[rep1] && tieneFabrica[rep2]) { // ambos conjuntos tienen fabrica
			continue;
		}

		if (tieneFabrica[rep1] || tieneFabrica[rep2]) {
			// marco que todos los nodos tienen fábrica si al menos uno tenía
			tieneFabrica[rep1] = true;
			tieneFabrica[rep2] = true;
			tieneFabrica[ruta.inicio] = true;
			tieneFabrica[ruta.fin] = true;
		}

		// uno los conjuntos y agrego a la solución esta ruta
		res.push_back(ruta);
		conjuntos.merge(rep1, rep2);
	}

	return res;
}


int main() {
	cerr << "Cantidad de fabricas;Cantidad de clientes;Cantidad de rutas;Tiempo de ejecucion;Tamaño de la solucion" << endl;
	int F, C, R;
	cin >> F >> C >> R;

	while(F) {
		vector<arista> rutas;
		for (int i = 0; i < R; ++i) {
			int e1, e2, l;
			cin >> e1 >> e2 >> l;
			// ajustados con -1 para que sea un array de índice inicial 0
			rutas.emplace_back(e1 - 1, e2 - 1, l);
		}
		ElCondor elcondor(F, C, rutas);
		// Guarda los tiempos y ejecuta el algoritmo
		high_resolution_clock::time_point inicio = high_resolution_clock::now();
		auto rutasOptimas = elcondor.rutasOptimas();
		high_resolution_clock::time_point fin = high_resolution_clock::now();

		//Calcula la duración
		duration<double> elapsed = duration_cast<duration<double>>(fin - inicio);
		cerr << F << ";" << C << ";" << R << ";" << elapsed.count() << ";" << rutasOptimas.size() << endl; 

		int L = 0;
		for (auto& rutaOptima : rutasOptimas) {
			L += rutaOptima.costo;
		}
		cout << L << " " << rutasOptimas.size();
		for (auto& rutaOptima : rutasOptimas) {
			// ajustados con +1 para que represente los números originales
			cout << " " << rutaOptima.inicio + 1 << " " << rutaOptima.fin + 1;
		}
		cout << endl;

		cin >> F >> C >> R;
	}


}
