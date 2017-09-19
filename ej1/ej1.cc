// include utils
#include <iostream>
#include <fstream>
#include <functional>
// include data structures
#include <deque>
#include <vector>

using namespace std;

typedef vector< vector<int> > MatrizCosto;

MatrizCosto read_data(int N)
{
	// TODO: hacerlo triangular
	MatrizCosto data(N + 1, vector<int>(N + 1, -9));
	for (int i = 1; i < N + 1; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			int dato;
			cin >> dato;
			data[i][j] = dato;
		}
	}

	return data;
}

void costo_minimo(MatrizCosto costos_fijos, int N) {
	vector<int> anterior(N, 0);
	vector<int> actual(N, 0);
	// inicializamos
	anterior[1] = costos_fijos[1][0];
	for (int i = 2; i < N + 1; ++i) {
		// TODO
		int minimo = 999999;
		for (int j = 0; j < i - 1; ++j) {
			actual[j] = anterior[j] + costos_fijos[i][i - 1];
			minimo = min(minimo, anterior[j] + costos_fijos[i][j]);
		}

		actual[i - 1] = minimo;
		swap(anterior, actual);
	}

	for (int j = 0; j < N + 1; ++j) {
		cerr << actual[j] << "  ";			
	}
	cerr << endl;
}

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	MatrizCosto costos_fijos(read_data(N));
	costo_minimo(costos_fijos, N);

//	for (int i = 0; i < N + 1; ++i) {
//		for (int j = 0; j < N + 1; ++j) {
//			cerr << costos_fijos[i][j] << "  ";			
//		}
//		cerr << endl;
//	}

	return 0;
}

