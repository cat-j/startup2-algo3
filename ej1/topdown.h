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
    int valor;
    int def;
    CostoAcumulado(int v, int d) : valor(v), def(d) {}
    CostoAcumulado operator=(const CostoAcumulado c) {
        valor = c.valor; def = c.def;
    }
};

typedef vector< vector<int> > MatrizCosto;
typedef vector< vector<CostoAcumulado> > MatrizCostoAcumulado;

class TallerDeImpresiones {
public:
    int costoOptimo();
    TallerDeImpresiones(int n, MatrizCosto &c);
    stack<int> dameSolucionOptima();

private:
    MatrizCosto costosFijos;
    MatrizCostoAcumulado costosAcumulados;
    int cantTrabajos;
    stack<int> solucionOptima;
    int costoOptimoAux(int i, int j);
};

