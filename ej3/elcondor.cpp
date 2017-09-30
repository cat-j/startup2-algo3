#include "elcondor.h"
#include "disjoint_set_union.h"

struct arista {
    int origen;
    int fin;
    int costo;

    arista(int o, int f, int c) : origen(o), final(f), costo(c) {}

    bool operator<(const arista a) const {
        return costo < a.costo;
    }
}

class ElCondor
{
public:
    ElCondor(int c, int f, vector<arista> r);
    ~ElCondor();
    vector<arista> rutasOptimas();

private:
    int clientes, fabricas;
    vector<arista> rutas;
    Disjoint_Union conjuntos;
    vector<bool> tieneFabrica;
};

ElCondor::ElCondor(int c, int f, vector<arista> r)
    : clientes(c)
    , fabricas(f)
    , rutas(r)
    , conjuntos(c + f)
    , tieneFabrica(c, false) {} // Sólo nos importa saber si un conjunto tiene fábricas cuando lo identificamos con un cliente.

vector<arista> ElCondor::rutasOptimas() {
    vector<arista> res;
    sort(rutas.begin(), rutas.end());

    for (const auto &ruta:rutas) {
        if (ruta.inicio < clientes) { // es un cliente
            if (ruta.fin >= clientes) { // es fabrica
                auto rep1 = conjuntos.find(ruta.inicio);
                auto rep2 = conjuntos.find(ruta.fin);
                if (rep1 == rep2) { // ya estan en el mismo conjunto
                }
                else if (tieneFabrica[rep1] && tieneFabrica[rep2]) { // ambos conjuntos tienen fabrica
                }
                else { // ambos conjuntos tienen fabrica
                    if (tieneFabrica[rep1] || tieneFabrica[rep2]) { // al menos uno tiene fabrica
                        tieneFabrica[rep1] = true;
                        tieneFabrica[rep2] = true;
                        tieneFabrica[ruta.inicio] = true;
                        tieneFabrica[ruta.fin] = true;
                    }

                    conjuntos.merge(rep1, rep2);
                }
            }
        }
    }
}