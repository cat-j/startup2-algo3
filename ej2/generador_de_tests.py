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

def sacarBackedges(n, grafo, p_backedge=0.5):
    # Elimina cada backedge de un grafo con una probabilidad 1.0 - p_backedge.
    print grafo
    vecinos = [ [] for i in range(n) ]

    for e in grafo:
        vecinos[e[0] - 1].append(e[1])

    print vecinos

    return

def generarGrafoSpiderman(n, l, pesos, p_backedge=0.5):
    # n = número de rayos
    # l = número de capas
    assert(len(pesos) == 2*n*l)

    grafoSpiderman = []
    pesoActual = 0

    # inicializa la primera capa
    for j in range(2, n+2):
        grafoSpiderman.append( [1, j, pesos[pesoActual]] )

        if j < n+1:
            grafoSpiderman.append( [j, j+1, pesos[pesoActual + 1]] )
        else:
            grafoSpiderman.append( [2, j, pesos[pesoActual + 1]] )

        pesoActual += 2

    # genera las capas 2 a l
    for i in range(1, l):
        for j in range(2, n+2):
            grafoSpiderman.append( [j + (i-1)*n, j + i*n, pesos[pesoActual]] )

            if j < n+1:
                grafoSpiderman.append( [j + i*n, j + i*n + 1, pesos[pesoActual + 1]] )
            else:
                grafoSpiderman.append( [2 + i*n, j + i*n, pesos[pesoActual + 1]] )

            pesoActual += 2

    grafoStr = [ " ".join( str(k) for k in e ) for e in grafoSpiderman ]

    return grafoStr

def generarGrafoAleatorio(n, pesos, p_backedge=0.5):
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

    sacarBackedges(n, grafoCompleto)

    return grafoStr

def generarEntradaCompletoPesosUniformes(n, minimo=0, maximo=10, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos.
    # Los pesos están distribuidos uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = generarPesosUniformes(n, minimo, maximo)
            grafo = generarGrafoAleatorio(n, pesos)
            entrada.write(str(n) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaCompletoPesosNormales(n, mu=5, sigma=1, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos.
    # Los pesos están distribuidos uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = generarPesosNormales(n, mu, sigma)
            grafo = generarGrafoAleatorio(n, pesos)
            entrada.write(str(n) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaSpidermanPesosUniformes(n, l, minimo=0, maximo=0, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos telaraña de n vértices y l capas.
    # Los pesos están distribuidos uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = [ np.random.randint(0,10) for i in range(2*n*l) ]
            grafo = generarGrafoSpiderman(n, l, pesos, p_backedge)
            entrada.write(str(n*l+1) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaSpidermanPesosNormales(n, l, mu=5, sigma=1, p_backedge=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos telaraña de n vértices y l capas.
    # Los pesos están distribuidos uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            pesos = [ int(max(np.random.normal(mu, sigma), 0)) for i in range(2*n*l) ]
            grafo = generarGrafoSpiderman(n, l, pesos, p_backedge)
            entrada.write(str(n*l+1) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

pesosUniformes = generarPesosUniformes(4)
pesosNormales = [ np.random.randint(0,10) for i in range(24) ]

generarEntradaSpidermanPesosNormales(6, 1, 10, 2, archivo="spiderman.in")

# generarEntradaPesosUniformes(10, 1, 30, 0.5, "uniforme_10nodos_1a30.in")
# generarEntradaPesosNormales(10, 30, 5, 0.5, "normal_10nodos_mu30_sigma5.in")