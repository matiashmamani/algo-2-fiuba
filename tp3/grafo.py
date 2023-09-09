class Grafo():

    def __init__(self, es_dirigido = False):
        self.grafo = {}
        self.es_dirigido = es_dirigido
    
    def agregar_vertice(self, vertice):
        if vertice in self.grafo: return
        self.grafo[vertice] = {}

    def borrar_vertice(self, vertice):
        for v in self.grafo:
            if vertice in self.grafo[v].keys():
                self.grafo[v].pop(vertice)
        self.grafo.pop[vertice]

    def existe_vertice(self, vertice):
        return vertice in self.grafo

    def agregar_arista(self, origen, destino, peso = 1):
        if destino in self.grafo[origen]:
            return
        self.grafo[origen][destino] = peso
        if self.es_dirigido == False:
            self.grafo[destino][origen] = peso

    def borrar_arista(self, origen, destino):
        self.grafo[origen].pop(destino)
        if self.es_dirigido == False:
            self.grafo[destino].pop(origen)

    def existe_arista(self, origen, destino):
        if origen not in self.grafo or destino not in self.grafo:
            return False
        return destino in self.grafo[origen]

    def peso_arista(self, origen, destino):
        return self.grafo[origen][destino]
    
    def obtener_vertices(self):
        return list(self.grafo.keys())

    def adyacentes(self, vertice):
        return list(self.grafo[vertice].keys())

    def __str__(self):
        for v in self.grafo:
            print(v + ' :')
            for w in self.grafo[v]:
                print('\t' + w)
        return

    def __len__(self):
        return len(self.grafo.keys())