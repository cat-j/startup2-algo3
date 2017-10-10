#include "topdown.h"

void mostrarMatriz(MatrizCostoAcumulado &m) {
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            cerr << "(" << m[i][j].valor << ", " << m[i][j].def << ", " << m[i][j].padre << ") ";
        }
        cerr << endl;
    }
}

TallerDeImpresiones::TallerDeImpresiones(int n, MatrizCosto &c) : cantTrabajos(n), costosFijos(c) {
    costosAcumulados = MatrizCostoAcumulado(n+1);
    for (int i = 0; i < n+1; ++i) {
        // Inicializa las filas de la matriz. Para cada 0 <= i <= n, crea un vector de i posiciones
        // que almacenara los costos optimos cuando t_i es el ultimo trabajo en una maquina y t_j es el
        // ultimo en la otra, con 0 <= j < i.
        for (int j = 0; j < i; ++j) {
            CostoAcumulado costo(0,0,0);
            costosAcumulados[i].push_back(costo);
        }
    }

#ifdef DEBUG

    cerr << "Costos fijos: ";

    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < i; ++j) {
            cerr << costosFijos[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << endl;

#endif
}

int TallerDeImpresiones::costoOptimo() {

    /* Metodo principal de la solucion top-down.
       Calcula C(cantTrabajos) mediante llamadas a C mono (cantTrabajos, j)
       para cada j entre 0 y cantTrabajos-1.
IMPORTANTE: modifica la matriz de costos acumulados. */

    int minimo = costoOptimoAux(cantTrabajos, 0);
    for (int j = 0; j < cantTrabajos; ++j) {
        int actual = costoOptimoAux(cantTrabajos, j);
        if (actual < minimo) { minimo = actual; }
    }
    return minimo;
}

stack<int> TallerDeImpresiones::dameSolucionOptima() {
    stack<int> res;
    int optimo = costoOptimo(), actual = cantTrabajos, otro = 0, minimo = costosAcumulados[cantTrabajos][0].valor;
    // mostrarMatriz(costosAcumulados);
    res.push(cantTrabajos);

    for(int j = 1; j < cantTrabajos; ++j) {
        if (costosAcumulados[cantTrabajos][j].valor < minimo) {
	    minimo = costosAcumulados[cantTrabajos][j].valor;
	    otro = j;
	}
    }

    int padre = costosAcumulados[cantTrabajos][otro].padre;

    while(padre != 0) {
<<<<<<< HEAD
	// cout << "INICIO DEL CICLO" << endl;
        // cout << "Padre: " << padre << ", otro: " << otro << endl;
	res.push(padre);
=======
	    cerr << "INICIO DEL CICLO" << endl;
        cerr << "Padre: " << padre << ", otro: " << otro << endl;
        res.push(padre);
>>>>>>> 7ee6900498742a5952144fcdc530b217018accf5

        padre = costosAcumulados[max(padre, otro)][min(padre, otro)].padre;
        if ( max(padre, otro) > 0 ) { otro = costosAcumulados[max(padre, otro)][min(padre, otro)].padre; }

<<<<<<< HEAD
	// cout << "FIN DEL CICLO" << endl;
        // cout << "Padre: " << padre << ", otro: " << otro << endl;
=======
        cerr << "FIN DEL CICLO" << endl;
        cerr << "Padre: " << padre << ", otro: " << otro << endl;
>>>>>>> 7ee6900498742a5952144fcdc530b217018accf5

    }
    
    return res;
}

int TallerDeImpresiones::costoOptimoAux(int i, int j) {
    assert(j >= 0 && i > j);

    if ( costosAcumulados[i][j].def ) {

        // El valor ya estaba guardado en la matriz, lo devolvemos en O(1)
        return costosAcumulados[i][j].valor;

    } else {

        if (i == 1) {

            //Caso base

            costosAcumulados[1][0] = CostoAcumulado( costosFijos[1][0], 1, 0 );
            return costosAcumulados[1][0].valor;

        } else {

            if (j < i-1) {

                // Segundo caso, calculamos la sumatoria

                int costoParcial = costoOptimoAux(i-1, j); //subproblema
                costosAcumulados[i][j] = CostoAcumulado( costoParcial + costosFijos[i][i-1], 1, i-1 );

                return costosAcumulados[i][j].valor;

            } else {

                /* Tercer caso, j = i-1. Elegimos entre las soluciones de i-1 subproblemas. */

                int minimo = costoOptimoAux(j, 0) + costosFijos[i][0], padre = 0;
                for (int k = 1; k < j; ++k ) {
                    int actual = costoOptimoAux(j, k) + costosFijos[i][k];

                    if (actual < minimo) {
                        minimo = actual;
                        padre = k;
                    }
                }
                costosAcumulados[i][j] = CostoAcumulado( minimo, 1, padre );

                return minimo;

            }
        }
    }
}
