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
            grafoCompleto.append( (i, j, pesos[pesoActual]) )
            pesoActual += 1
            
    return grafoCompleto 


# pesosUniformes = generarPesosUniformes(10)
# pesosNormales = generarPesosNormales(10)

# print generarGrafo(10, pesosUniformes)
# print generarGrafo(10, pesosNormales)