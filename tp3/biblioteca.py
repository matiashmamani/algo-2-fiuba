from collections import deque
from random import choice

def camino_minimo_bfs(grafo, origen, destino):
    visitados = set()
    padres = {}
    distancia = {}
    padres[origen] = None
    distancia[origen] = 0
    visitados.add(origen)
    q = deque()
    q.append(origen)
    while len(q) > 0:                   # While not q.esta_vacia()
        v = q.popleft()
        if v == destino:
            return padres, distancia
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                distancia[w] = distancia[v] + 1
                visitados.add(w)
                q.append(w)
    return padres, distancia

def page_rank(grafo, pr, d=0.85, n_iter=10):
    N_total = len(grafo)
    if len(pr) == 0:
        for v in grafo.obtener_vertices():
            pr[v] = 1 / N_total
    for i in range(n_iter):
        pr_anterior = pr
        for v in grafo.obtener_vertices():
            suma = 0
            for w in grafo.adyacentes(v):
                suma += pr_anterior[w]/len(grafo.adyacentes(w))
            pr[v] += ((1-d)/N_total + d*suma)
    return

def _random_walk(grafo, v, prp, pagerank, largo):
    if largo == 0:
        return
    if pagerank != 1:
        if v in prp:
            prp[v] += pagerank
        else:
            prp[v] = pagerank
    pagerank /= len(grafo.adyacentes(v))
    w = choice(grafo.adyacentes(v))
    return _random_walk(grafo, w, prp, pagerank, largo-1)

def page_rank_personalizado(prp, grafo, origen, cant_walk=1, largo=30):
    for i in range(cant_walk):
        _random_walk(grafo, origen, prp, 1, largo)
    return

def _ciclo_dfs(grafo, v, visitados, camino, largo):
    visitados.add(v)
    camino.append(v)
    if v == camino[0] and len(camino) == largo + 1:
        return True
    if len(camino) > largo:
        visitados.remove(v)
        camino.pop()
        return False
    for w in grafo.adyacentes(v):
        if w not in visitados or (w == camino[0] and len(camino) == largo):
            if _ciclo_dfs(grafo, w, visitados, camino, largo):
                return True
    visitados.remove(v)
    camino.pop()
    return False

def ciclo(grafo, origen, largo):
    camino = []
    visitados = set()
    if _ciclo_dfs(grafo, origen, visitados, camino, largo):
        return camino
    return None

def rango(grafo, origen, rango):
    visitados = set()
    suma = 0
    distancia = {}
    distancia[origen] = 0
    visitados.add(origen)
    q = deque()
    q.append(origen)
    while len(q) > 0:                   # While not q.esta_vacia()
        v = q.popleft()
        if distancia[v] == rango:
            return suma
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                if distancia[w] == rango:
                    suma += 1
                visitados.add(w)
                q.append(w)
    return suma