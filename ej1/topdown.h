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

using namespace std;

struct CostoAcumulado {
    int valor; //el costo optimo para cierto par de valores
    int def; //dice si el costo esta definido
    int padre; //dice cual es el valor que viene antes de i; se usa para reconstruir la solucion
    CostoAcumulado(int v, int d, int p) : valor(v), def(d), padre(p) {}
    // CostoAcumulado operator=(const CostoAcumulado c) {
    //     valor = c.valor; def = c.def; padre = c.padre;
    // }
};

typedef vector< vector<int> > MatrizCosto;
typedef vector< vector<CostoAcumulado> > MatrizCostoAcumulado;

class TallerDeImpresiones {
public:
    TallerDeImpresiones(int n, MatrizCosto &c);
    int costoOptimo();
    stack<int> dameSolucionOptima();
private:
    int cantTrabajos;
    MatrizCosto costosFijos;
    MatrizCostoAcumulado costosAcumulados;
    stack<int> solucionOptima;
    int costoOptimoAux(int i, int j);
};

