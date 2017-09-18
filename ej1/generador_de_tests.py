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
        for i in range(32):
            caso = generarCasoUniforme(n, minimo, maximo)
            for j in caso:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaNormal(n, mu=5, sigma=1, archivo="output"):
    with open(archivo, 'w') as entrada:
        for i in range(32):
            caso = generarCasoNormal(n, mu, sigma)
            for j in caso:
                entrada.write(j + '\n')
        entrada.write("0 \n")

    return

# generarEntradaUniforme(20, 1, 30, "uniforme_1_30.in")
# generarEntradaNormal(20, 30, 5, "normal_mu30_sigma5.in")