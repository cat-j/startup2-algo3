# -*- coding: utf-8 -*-

import numpy as np

def generarGrafoPesosUniformes(f, c, minimo=0, maximo=10, p_arista=0.5):
    assert(f<=c)

    grafo = []
    verticesUsados = []
    aristasUsadas = []

    # Genera un grafo minimal con respecto a que cualquier cliente
    # sea alcanzable desde al menos una fábrica.

    for cliente in range(f+1, f+c+1):
        # Se asegura de que cada cliente sea adyacente a una fábrica
        # o a otro cliente tal que hay un camino entre él y una fábrica.
        vecino = np.random.choice([i for i in range(1,f+1)] + verticesUsados)
        verticesUsados.append(cliente)
        l, r = min(cliente, vecino), max(cliente, vecino)
        grafo.append([ l, r, np.random.randint(minimo, maximo) ])
        aristasUsadas.append((l,r))

    # Agrega más aristas con probabilidad p_arista.
    # Cada una es independiente.

    for i in range(1, f+c+1):
        for j in range(i+1, f+c+1):
            if not((i,j) in aristasUsadas):
                p = np.random.uniform()
                if p <= p_arista:
                    grafo.append([ i, j, np.random.randint(minimo, maximo) ])

    grafoStr = [ " ".join( str(k) for k in e ) for e in grafo ]

    return grafoStr

def generarGrafoPesosNormales(f, c, mu=5, sigma=1, p_arista=0.5):
    assert(f<=c)

    grafo = []
    verticesUsados = []
    aristasUsadas = []

    # Genera un grafo minimal con respecto a que cualquier cliente
    # sea alcanzable desde al menos una fábrica.

    for cliente in range(f+1, f+c+1):
        # Se asegura de que cada cliente sea adyacente a una fábrica
        # o a otro cliente tal que hay un camino entre él y una fábrica.
        vecino = np.random.choice([i for i in range(1,f+1)] + verticesUsados)
        verticesUsados.append(cliente)
        l, r = min(cliente, vecino), max(cliente, vecino)
        grafo.append([ l, r, int(max(np.random.normal(mu, sigma), 0)) ])
        aristasUsadas.append((l,r))

    # Agrega más aristas con probabilidad p_arista.
    # Cada una es independiente.

    for i in range(1, f+c+1):
        for j in range(i+1, f+c+1):
            if not((i,j) in aristasUsadas):
                p = np.random.uniform()
                if p <= p_arista:
                    grafo.append([ i, j, int(max(np.random.normal(mu, sigma), 0)) ])

    grafoStr = [ " ".join( str(k) for k in e ) for e in grafo ]

    return grafoStr

def generarEntradaPesosUniformes(f, c, minimo=0, maximo=10, p_arista=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos. Los pesos están distribuidos
    # uniformemente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            grafo = generarGrafoPesosUniformes(f, c, minimo, maximo, p_arista)
            entrada.write(str(f) + " " + str(c) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return

def generarEntradaPesosNormales(f, c, mu=5, sigma=1, p_arista=0.5, archivo="output"):
    # Genera un caso de test con 32 grafos de n nodos. Los pesos están distribuidos
    # normalmente según los parámetros especificados.
    with open(archivo, 'w') as entrada:
        for i in range(32):
            grafo = generarGrafoPesosNormales(f, c, mu, sigma, p_arista)
            entrada.write(str(f) + " " + str(c) + " " + str(len(grafo)) + '\n')
            for j in grafo:
                entrada.write(j + '\n')
        entrada.write("0\n")

    return