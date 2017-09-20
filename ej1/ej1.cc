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

using namespace std;

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

// esto debería ser un map o un vector de pares o algo así para no usar el workaround de +500
vector<int> costo_minimo_td_data(1000, -1);
// t_i: último trabajo en MA
int costo_minimo_td(MatrizCosto costos_fijos, int t_i, int conozco_ultimo_b) {
	if (conozco_ultimo_b) {
		if (costo_minimo_td_data[t_i+500] != -1) {
			return costo_minimo_td_data[t_i+500];
		}
	}
	else {
		if (costo_minimo_td_data[t_i] != -1) {
			return costo_minimo_td_data[t_i];
		}
	}

	assert(t_i >= 1);
	if (t_i == 1) {
		return costos_fijos[1][0];
	}

	// MA <-------------t_i-1---t_i-|
	// MB <-------------------------|
	int minimo = 999999; // TODO
	if (!conozco_ultimo_b) {
		// cuando conozco el último trabajo de MB no puedo considerar este caso
		minimo = costo_minimo_td(costos_fijos, t_i-1, false) + costos_fijos[t_i][t_i-1];
	}

	// todas las posibilidades alternando, e.g.:
	// MA <-----t_i-2-----------t_i-|   MA <--t_i-3-------------------t_i-|
	// MB <-------------t_i-1-------|   MB <----------t_i-2---t_i-1-------|
	for (int t_j = t_i-2; t_j >= 0; --t_j) {
		// t_j+1 es el nodo que en la siguiente iteración quiero 
		int costo_siguientes = 0;
		for (int t_k = t_i-1; t_k >= t_j+2; --t_k) {
			// suma todos los consecutivos en MB
			costo_siguientes += costos_fijos.at(t_k).at(t_k-1);
		}
		minimo = min(minimo, costo_minimo_td(costos_fijos, t_j+1, true) + costo_siguientes + costos_fijos[t_i][t_j]);
	}

	assert(minimo != 999999);

	// workaround para guardar distinto si conozco o no último MB
	if (conozco_ultimo_b)
		costo_minimo_td_data[t_i+500] = minimo;
	else
		costo_minimo_td_data[t_i] = minimo;
	return minimo;
}

int costo_minimo_backtracking(MatrizCosto costos_fijos, int N, int A, int B, int trabajo) {
	if (trabajo == 1) {
		return costo_minimo_backtracking(costos_fijos, N, trabajo, B, trabajo + 1) + costos_fijos.at(trabajo).at(A);
	}

	if (trabajo > N) {
		return 0;
	}

	int maquina_a = costo_minimo_backtracking(costos_fijos, N, trabajo, B, trabajo + 1) + costos_fijos.at(trabajo).at(A);
	int maquina_b = costo_minimo_backtracking(costos_fijos, N, A, trabajo, trabajo + 1) + costos_fijos.at(trabajo).at(B);

	return min(maquina_a, maquina_b);
}


int costo_minimo_bottom_up(MatrizCosto costos_fijos, int N) {
	vector<int> anterior(N, 0);
	vector<int> actual(N, 0);
	// inicializamos
	anterior[0] = costos_fijos.at(1).at(0);
	for (int i = 2; i < N + 1; ++i) {
		// TODO
		int minimo = 999999;
		for (int j = 0; j < i - 1; ++j) {
			actual[j] = anterior[j] + costos_fijos.at(i).at(i - 1);
			minimo = min(minimo, anterior[j] + costos_fijos.at(i).at(j));
		}

		actual[i - 1] = minimo;
		swap(anterior, actual);
	}

	return *min_element(anterior.begin(), anterior.end());
}

void main_2(istream& input) {
	int N;
	input >> N;
	MatrizCosto costos_fijos(read_data(input, N));
	cerr << "costo_minimo_backtracking: " << costo_minimo_backtracking(costos_fijos, N, 0, 0, 1) << endl;
	cerr << "costo_minimo_td: " << costo_minimo_td(costos_fijos, N, false) << endl;
	cerr << "costo_minimo_bottom_up: " << costo_minimo_bottom_up(costos_fijos, N) << endl;
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

