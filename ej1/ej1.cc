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

int costo_minimoBT(MatrizCosto costos_fijos, int N, int A, int B, int trabajo) {
	if(trabajo == 1){
		return costo_minimoBT(costos_fijos, N, trabajo, B, trabajo +1) + costos_fijos[trabajo][A];
	}
	int maquinaA, maquinaB;

	if(trabajo > N){
		return 0;
	}

	else{
		
		maquinaA = costo_minimoBT(costos_fijos, N, trabajo, B, trabajo +1) + costos_fijos[trabajo][A];

		maquinaB = costo_minimoBT(costos_fijos, N, A, trabajo, trabajo +1) + costos_fijos[trabajo][B];
	}

	return min(maquinaA, maquinaB);
}

void costo_minimo(MatrizCosto costos_fijos, int N) {
	vector<int> anterior(N, 0);
	vector<int> actual(N, 0);
	// inicializamos
	anterior[0] = costos_fijos[1][0];
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
		cerr << anterior[j] << "  ";			
	}
	cerr << endl;
}

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	MatrizCosto costos_fijos(read_data(N));
	/*if(N < 10)*/cerr << costo_minimoBT(costos_fijos, N, 0, 0, 1) << endl;
	costo_minimo(costos_fijos, N);

//	for (int i = 0; i < N + 1; ++i) {
//		for (int j = 0; j < N + 1; ++j) {
//			cerr << costos_fijos[i][j] << "  ";			
//		}
//		cerr << endl;
//	}

	return 0;
}

