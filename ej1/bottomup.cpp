// include utils
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <numeric>
// include data structures
#include <deque>
#include <set>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;
using namespace std::chrono;
typedef vector< vector<int> > MatrizCosto;


MatrizCosto read_data(istream& input, int N) {
	// devuelve una matriz triangular
	MatrizCosto data(N + 1);
	for (int i = 1; i < N + 1; ++i) {
		data[i] = vector<int>(i);
		for (int j = 0; j < i; ++j) {
			int dato;
			input >> dato;
			data[i][j] = dato;
		}
	}

	return data;
}

MatrizCosto init(int N) {
	// devuelve una matriz triangular
	MatrizCosto data(N + 1);
	for (int i = 1; i < N + 1; ++i) {
		data[i] = vector<int>(i);
		for (int j = 0; j < i; ++j) {
			data[i][j] = 0;
		}
	}

	return data;
}

stack<int> solucionOptima(MatrizCosto costos_fijos, MatrizCosto soluciones, int resultado, int N, vector<int> anteriores){
	stack<int> sol;
	sol.push(N);
	// return sol;
	int res = resultado;
	for (int i = N; i > 0; --i){
		for(int j = 0; j < i; ++j){
			if(soluciones.at(i).at(j) == res){
				if(j == i-1 ){
					int anterior = anteriores.at(i);
					res = res - costos_fijos.at(i).at(anterior);
					if(i == sol.top() and anteriores[i] > 0){
						sol.push(anterior);
					}
				}
				else{
					res = res - costos_fijos.at(i).at(i-1);
					if(i == sol.top() and (i-1 > 0) ){
						sol.push(i-1);
					}
				}
			break;
			}
		}
	}
	return sol;
}
int costo_minimo_bottom_up(MatrizCosto costos_fijos, int N, MatrizCosto& soluciones, vector<int>& anteriores) {
	// inicializamos
	soluciones.at(1).at(0) = costos_fijos.at(1).at(0);
	for (int i = 2; i < N + 1; ++i) {
		// TODO
		int minimo = 999999;
		int anterior = 0;
		for (int j = 0; j < i - 1; ++j) {
			soluciones.at(i).at(j) = soluciones.at(i-1).at(j) + costos_fijos.at(i).at(i - 1);
			int nuevo_min = soluciones.at(i-1).at(j) + costos_fijos.at(i).at(j);
			if(minimo > nuevo_min) anterior = j;
			minimo = min(minimo, nuevo_min );
		}

		soluciones.at(i).at(i-1) = minimo;
		anteriores.at(i) = anterior;
	}
	int resultado =*min_element(soluciones.at(N).begin(), soluciones.at(N).end());
	
	return resultado;
}


void main_2(istream& input) {
	int N;
	input >> N;
	while(N > 0){
		MatrizCosto costos_fijos(read_data(input, N));
		MatrizCosto soluciones(init(N));
		vector<int> anteriores(N+1, 0);
		
		high_resolution_clock::time_point beginSolution = high_resolution_clock::now();
        
		int resultado = costo_minimo_bottom_up(costos_fijos, N, soluciones, anteriores);
		stack<int> solucion = solucionOptima(costos_fijos, soluciones, resultado, N, anteriores);

        high_resolution_clock::time_point endSolution = high_resolution_clock::now();
		
	    duration<double> elapsedSecsFindingSol = duration_cast<duration<double>>(endSolution - beginSolution);
	    cerr << N <<"; "<< elapsedSecsFindingSol.count() << endl;
	    cout << resultado << " " << solucion.size();
	    while (!solucion.empty()) {
	        cout << " " << solucion.top();
	        solucion.pop();
	    }
	    cout << endl;
	    input >> N;
	}
}

int main(int argc, char const *argv[]) {
	if (argc > 1) {
		ifstream file(argv[1]);
		main_2(file);
	}
	else
		main_2(cin);

	return 0;
}

