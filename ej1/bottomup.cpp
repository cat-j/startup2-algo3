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
	//pila donde guardo las soluciones
	stack<int> sol;

	// apilo el ultimo elemento
	sol.push(N);

	//este es el costo optimo de poner todos los trabajos
	int res = resultado;

	//itero sobre la matriz, desde la ultima fila
	for (int i = N; i > 0; --i){
		//itero sobre las columnas de la fila
		for(int j = 0; j < i; ++j){

			//si el costo que estoy viendo es el resultado que tengo
			if(soluciones.at(i).at(j) == res){

				//si era el costo de tener t_i sobre algun t_k que no era i-1
				if(j == i-1 ){

					//agarro el k del vector en el que los guardaba
					int anterior = anteriores.at(i);

					//actualizo el costo que tengo que buscar, restandole lo que me costo agregar t_i sobre t_k
					res = res - costos_fijos.at(i).at(anterior);

					//si estaba en la misma maquina que el ultimo trabajo que apile, tambien lo apilo
					if(i == sol.top() and anteriores[i] > 0){
						sol.push(anterior);
					}
				}
				else{
					//si lo apile sobre el anterior, solo actualizo el costo igual que antes
					res = res - costos_fijos.at(i).at(i-1);
					//si es la misma maquina que el ultimo que apile, lo apilo
					if(i == sol.top() and (i-1 > 0) ){
						sol.push(i-1);
					}
				}
			//ya encontre como seguir asi que en vez de seguir iterando en esta fila paso a la siguiente
			break;
			}
		}
	}
	//devuelvo la pila
	return sol;
}


int costo_minimo_bottom_up(MatrizCosto costos_fijos, int N, MatrizCosto& soluciones, vector<int>& anteriores) {
	//el primer paso es trivial
	//el costo de poner el primer trabajo en una maquina no depende de nada salvo de su costo fijo
	//entonces guardo en mi matriz de costos optimos ese resultado
	soluciones.at(1).at(0) = costos_fijos.at(1).at(0);

	for (int i = 2; i < N + 1; ++i) { //como ya vi t_1, ahora veo desde t_2 en adelante
		// TODO
		int minimo = 999999; //minimo grande arbitrario, se puede reemplazar con un valor negativo y luego chequear cada vez
		int anterior = 0; //inicializo esta variable aunque no es realmente necesario

		for (int j = 0; j < i - 1; ++j) {
			//en el caso de agregar t_i sobre t_(i-1):
			//el costo optimo de hacer eso es el costo optimo de tener t_(i-1) y t_j en cada maquina (ya calculado en la iteracion anterior)
			//y sumarle el costo de poner t_i luego de t_(i-1)
			//luego, guardo ese valor en la matriz de costos optimos
			soluciones.at(i).at(j) = soluciones.at(i-1).at(j) + costos_fijos.at(i).at(i - 1);

			//en el caso de NO agregar t_i sobre t_(i-1):
			//t_i va a ir sobre algun t_k, 0 <= k < i-1;
			//entonces el costo optimo de agregar t_i sobre t_k 
			//va a ser el el costo de tener t_(i-1) y t_k (ya calculado) más el costo de poner t_i luego de t_k
			//el k que genere el minimo de eso va a ser el que me interese

			int nuevo_min = soluciones.at(i-1).at(j) + costos_fijos.at(i).at(j);

			//voy calculando el posible costo mientras itero
			if(minimo > nuevo_min) anterior = j;
			minimo = min(minimo, nuevo_min );
		}
		//una vez que mire todos los posibles costos de agregar t_i sobre t_k != t_(i-1)
		//guardo ese valor en la matriz de soluciones
		soluciones.at(i).at(i-1) = minimo;

		anteriores.at(i) = anterior;//este vector guarda cual era t_k antes de agregar t_i arriba
									//en la maquina que NO contenia a t_(i-1) para que el costo en esa situacion sea optimo
									//esto me permite reconstruir eficientemente la solucion
	}

	//el resultado va a ser el minimo costo de haber apilado todos, que va a ser el minimo costo posible de
	//añadir el ultimo trabajo (pues se agregan en orden)
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

