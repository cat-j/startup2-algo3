# -*- coding: utf-8 -*-

import numpy as np

def generarCasoUniforme(n, minimo=0, maximo=10):
    caso = []
    caso.append(str(n))
    for i in range(1,n+1):
        costos_i = []
        for j in range(i):
            c_j_i = np.random.randint(minimo, maximo+1)
            costos_i.append(c_j_i)
            costos_i_str = " ".join(str(k) for k in costos_i)
        caso.append(costos_i_str)

    return caso

def generarCasoNormal(n, mu=5, sigma=1):
    caso = []
    caso.append(str(n))
    for i in range(1,n+1):
        costos_i = []
        for j in range(i):
            c_j_i = int(np.random.normal(mu, sigma))
            c_j_i = max(c_j_i, 0)
            costos_i.append(c_j_i)
            costos_i_str = " ".join(str(k) for k in costos_i)
        caso.append(costos_i_str)

    return caso

def generarEntradaUniforme(n, minimo=0, maximo=10, archivo="output"):
    with open(archivo, 'w') as entrada:
        for i in range(50):
            caso = generarCasoUniforme(n, minimo, maximo)
            for j in caso:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaNormal(n, mu=5, sigma=1, archivo="output"):
    with open(archivo, 'w') as entrada:
        for i in range(30):
            caso = generarCasoNormal(n, mu, sigma)
            for j in caso:
                entrada.write(j + '\n')
        entrada.write("0 \n")

    return


def generarEntradasHasta(n):
    trabajos = 50
    while(trabajos <= n):        
        generarEntradaUniforme(trabajos, 1, 100, "tests/uniforme_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 10, 5, "tests/normal_10_5_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 40, 5, "tests/normal_40_5_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 80, 5, "tests/normal_80_5_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 160, 5, "tests/normal_160_5_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 320, 5, "tests/normal_320_5_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 40, 0, "tests/normal_40_0_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 40, 0, "tests/normal_40_10_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 40, 0, "tests/normal_40_20_%i.in" % (trabajos))
        generarEntradaNormal(trabajos, 40, 0, "tests/normal_40_40_%i.in" % (trabajos))
        trabajos = trabajos + 20


generarEntradasHasta(350)