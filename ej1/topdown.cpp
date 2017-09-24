include "topdown.h"

void mostrarMatriz(MatrizCostoAcumulado &m) {
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            cout << "(" << m[i][j].valor << ", " << m[i][j].def << ") ";
        }
        cout << endl;
    }
}

TallerDeImpresiones::TallerDeImpresiones(int n, MatrizCosto &c) : cantTrabajos(n), costosFijos(c) {
    costosAcumulados = MatrizCostoAcumulado(n+1);
    for (int i = 0; i < n+1; ++i) {
        // Inicializa las filas de la matriz. Para cada 0 <= i <= n, crea un vector de i posiciones
        // que almacenará los costos óptimos cuando t_i es el último trabajo en una máquina y t_j es el
        // último en la otra, con 0 <= j < i.
        for (int j = 0; j < i; ++j) {
            CostoAcumulado costo(0,0);
            costosAcumulados[i].push_back(costo);
        }
    }

#ifdef DEBUG

    cout << "Costos fijos: ";

    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < i; ++j) {
            cout << costosFijos[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

#endif
}

int TallerDeImpresiones::costoOptimo() {

    /* Metodo principal de la solución top-down.
       Calcula C(cantTrabajos) mediante llamadas a C moño (cantTrabajos, j)
       para cada j entre 0 y cantTrabajos-1.
IMPORTANTE: modifica la variable global que guarda la solución optima. */


    solucionOptima.push(cantTrabajos);
    int minimo = costoOptimoAux(cantTrabajos, 0);
    for (int j = 0; j < cantTrabajos; ++j) {
        int actual = costoOptimoAux(cantTrabajos, j);
        if (actual < minimo) { minimo = actual; }
    }
    return minimo;
}

stack<int> TallerDeImpresiones::dameSolucionOptima(){
    return solucionOptima;
}

int TallerDeImpresiones::costoOptimoAux(int i, int j) {
    assert(j >= 0 && i > j);

#ifdef DEBUG

    cout << endl << "i = " << i << ", j = " << j << endl;

#endif

    if ( costosAcumulados[i][j].def ) {
        // El valor ya estaba guardado en la matriz, lo devolvemos en O(1)
        return costosAcumulados[i][j].valor;
    } else {

        if (i == 1) {

            //Caso base

#ifdef DEBUG
            cout << endl << "i == 1" << endl;
#endif

            costosAcumulados[1][0] = CostoAcumulado( costosFijos[1][0], 1 );

#ifdef DEBUG
            mostrarMatriz(costosAcumulados);
#endif

            return costosAcumulados[1][0].valor;

        } else {

            if (j < i-1) {

                // Segundo caso, calculamos la sumatoria

#ifdef DEBUG
                cout << endl << "j < i-1" << endl;
#endif
                int suma = 0;
                for (int l = j+2; l < i+1; ++l) {
                    suma += costosFijos[l][l-1];
                }

                int costoParcial = costoOptimoAux(j+1, j); //subproblema
                costosAcumulados[i][j] = CostoAcumulado( costoParcial + suma, 1 );

#ifdef DEBUG
                mostrarMatriz(costosAcumulados);
#endif

                return costosAcumulados[i][j].valor;

            } else { // j == i-1

#ifdef DEBUG
                cout << endl << "j == i-1" << endl;
#endif

                /* Elegimos entre las soluciones de i-1 subproblemas. */

                int minimo = costoOptimoAux(j, 0) + costosFijos[i][0], aPushear = 0;
                for (int k = 1; k < j; ++k ) {
                    int actual = costoOptimoAux(j, k) + costosFijos[i][k];
#ifdef DEBUG
                    cout << "costosAcumulados[" << j << "][" << k << "] = " << costosAcumulados[j][k].valor << endl;
                    cout << "costosFijos[" << i << "][" << k << "] = " << costosFijos[i][k] << endl;
#endif
                    if (actual < minimo) {
                        minimo = actual;
                        aPushear = i;
                    }
                    solucionOptima.push(aPushear);
                }
                costosAcumulados[i][j] = CostoAcumulado(minimo,1);
#ifdef DEBUG
                mostrarMatriz(costosAcumulados);
                cout << endl;
#endif
                return minimo;

            }
        }
    }
}
