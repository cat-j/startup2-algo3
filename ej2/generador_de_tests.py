            # -*- coding: utf-8 -*-

import numpy as np

'''
Idea: generar un grafo completo. Recorrerlo usando DFS desde un nodo elegido al azar.
Para cada arista que no sea puente, tomar una muestra de una variable aleatoria y eliminar
la arista si la variable supera cierto umbral. A grandes rasgos, el procedimiento consiste
en eliminar cierto porcentaje esperado de backedges.
'''

def generarPesosUniformes(n, minimo=0, maximo=10):
    return [ np.random.randint(minimo, maximo) for i in range(n*(n-1) / 2) ]

def generarPesosNormales(n, mu=5, sigma=1):
    return [ int(max(np.random.normal(mu, sigma), 0)) for i in range(n*(n-1) / 2) ]

def generarGrafo(n, pesos, p_backedge=0.5):
    # Es necesario que los pesos se correspondan con la cantidad de aristas
    # de un grafo completo de n nodos
    assert(len(pesos) == n*(n-1) / 2)

    # Genera un grafo completo representado por una lista de aristas.
    # El nodo de menor índice aparece antes, pero los pares no son ordenados
    # (es decir, el grafo no es dirigido).
    grafoCompleto = []
    pesoActual = 0
    for i in range(1, n):
        for j in range(i+1, n+1):
            grafoCompleto.append( [i, j, pesos[pesoActual]] )
            pesoActual += 1

    grafoStr = [ " ".join( str(k) for k in e ) for e in grafoCompleto ]

    return grafoStr

def generarEntradaPesosUniformes(n, minimo=0, maximo=10, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos. Los pesos están distribuidos
    # uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = generarPesosUniformes(n, minimo, maximo)
            grafo = generarGrafo(n, pesos)
            entrada.write(str(n) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaPesosNormales(n, mu=5, sigma=1, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos. Los pesos están distribuidos
    # uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = generarPesosNormales(n, mu, sigma)
            grafo = generarGrafo(n, pesos)
            entrada.write(str(n) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return


# pesosUniformes = generarPesosUniformes(10)
# pesosNormales = generarPesosNormales(10)

# print generarGrafo(10, pesosUniformes)
# print generarGrafo(10, pesosNormales)

generarEntradaPesosUniformes(10, 1, 30, 0.5, "uniforme_10nodos_1a30.in")
generarEntradaPesosNormales(10, 30, 5, 0.5, "normal_10nodos_mu30_sigma5.in")