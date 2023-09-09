#!/usr/bin/python3
import sys
from grafo import Grafo
from biblioteca import *

# *****************************************************************
#                    CONSTANTES
# *****************************************************************
ARGS_CANT = 2
ARGS_ARCHIVO = 1

ERROR_CANT_PARAMETROS = "ERROR: Cantidad de parámetros incorrecta"
ERROR_CMD = "ERROR: Comando inválido"
ERROR_CMD_PARAM = "ERROR: Parámetros de comando inválidos"
ERROR_CANCION_INVALIDA = "Tanto el origen como el destino deben ser canciones"
ERROR_NO_RECORRIDO = "No se encontro recorrido"

CMD_CAMINO = "camino"
CMD_MAS_IMPORTANTES = "mas_importantes"
CMD_RECOMENDACION = "recomendacion"
CMD_CICLO = "ciclo"
CMD_RANGO = "rango"

# *****************************************************************
#                    FUNCIONES AUXILIARES
# *****************************************************************
def reconstruir_camino(grafo, padres, destino):
    if destino not in padres:
        return None
    recorrido = []
    es_cancion = True      # Es True si estoy iterando una cancion, sino False si itero usuario
    while True:
        recorrido.append(destino)
        origen = padres[destino]
        if origen is not None:
            playlist_name = grafo.peso_arista(origen, destino)
        else:
            break
        if es_cancion:
            recorrido.append("donde aparece")
            recorrido.append(playlist_name)
            recorrido.append("tiene una playlist")
            es_cancion = False
        else:
            recorrido.append("de")
            recorrido.append(playlist_name)
            recorrido.append("aparece en playlist")
            es_cancion = True
        destino = origen
    return " --> ".join(recorrido[::-1])

def cmd_camino(param, grafo, canciones):
    try:
        pos = param.index(">>>>")   # Encuentro pos del caracter separador de origen y destino
        origen = ' '.join(param[:(pos)])
        destino = ' '.join(param[(pos+1):])
        if origen not in canciones or destino not in canciones:
            print(ERROR_CANCION_INVALIDA)
            return
        padres, distancia = camino_minimo_bfs(grafo, origen, destino)
        mensaje = reconstruir_camino(grafo, padres, destino)
        if mensaje is not None:
            print(mensaje)  
        else:
            print(ERROR_NO_RECORRIDO)
    except ValueError:
        print(ERROR_CMD_PARAM)

def cmd_mas_importantes(param, grafo, pr, canciones):
    if len(param) != 1 or not param[0].isnumeric():
        print(ERROR_CMD_PARAM)
        return
    if len(pr) == 0:
        page_rank(grafo, pr)
    pr = dict(sorted(pr.items(), key=lambda item: item[1], reverse=True))
    i = 1
    resultado = []
    for clave in pr:
        if i > int(param[0]):
            break
        if clave in canciones:
            resultado.append(clave)
            i += 1
    print('; '.join(resultado))

def cmd_recomendacion(param, grafo, usuarios, canciones):
    if param[0] != "canciones" and param[0] != "usuarios":
        print(ERROR_CMD_PARAM)
        return
    if not param[1].isnumeric():
        print(ERROR_CMD_PARAM)
        return
    listado = ' '.join(param[2:]).split(" >>>> ")
    prp = {}
    for cancion in listado:
        page_rank_personalizado(prp, grafo, cancion)
    prp = dict(sorted(prp.items(), key=lambda item: item[1], reverse=True))
    i = 1
    resultado = []
    for clave in prp:
        if i > int(param[1]):
            break
        if clave in listado:
            continue
        if param[0] == "canciones":
            if clave in canciones:
                resultado.append(clave)
                i += 1
        else:   # param[0] = "usuarios"
            if clave in usuarios:
                resultado.append(clave)
                i += 1
    print('; '.join(resultado))
                
def cmd_ciclo(param, grafo_canc, canciones):
    if not param[0].isnumeric():
        print(ERROR_CMD_PARAM)
        return
    cancion = ' '.join(param[1:])
    if cancion not in canciones:
        print(ERROR_CMD_PARAM)
        return
    camino = ciclo(grafo_canc, cancion, int(param[0]))
    if camino is not None:
        print(' --> '.join(camino))
    else:
        print(ERROR_NO_RECORRIDO)

def cmd_rango(param, grafo_canc, canciones):
    if not param[0].isnumeric():
        print(ERROR_CMD_PARAM)
        return
    cancion = ' '.join(param[1:])
    if cancion not in canciones:
        print(ERROR_CMD_PARAM)
        return
    print(rango(grafo_canc, cancion, int(param[0])))

def procesar_comando(linea):
    linea = linea.rstrip('\n')
    registro = linea.split(' ')
    comando = registro[0]
    param = registro[1:]
    return comando, param

def cargar_grafo_canciones(grafo_canc, usuarios):
    if len(grafo_canc) > 0:
        return
    for u in usuarios:
        for v in usuarios[u]:
            grafo_canc.agregar_vertice(v)
            for w in usuarios[u]:
                grafo_canc.agregar_vertice(w)
                if w != v:
                    grafo_canc.agregar_arista(w, v)

# *****************************************************************
#                    FUNCIONES PRINCIPALES
# *****************************************************************
def recomendify(grafo, usuarios, canciones):
    pr = {} # Dicc de PageRank para guardar iteraciones
    grafo_canc = Grafo()
    for linea in sys.stdin:
        comando, param = procesar_comando(linea)
        if comando == CMD_CAMINO:
            cmd_camino(param, grafo, canciones)
            continue
        if comando == CMD_MAS_IMPORTANTES:
            cmd_mas_importantes(param, grafo, pr, canciones)
            continue
        if comando == CMD_RECOMENDACION:
            cmd_recomendacion(param, grafo, usuarios, canciones)
            continue
        if comando == CMD_CICLO:
            cargar_grafo_canciones(grafo_canc, usuarios)
            cmd_ciclo(param, grafo_canc, canciones)
            continue
        if comando == CMD_RANGO:
            cargar_grafo_canciones(grafo_canc, usuarios)
            cmd_rango(param, grafo_canc, canciones)
            continue
        # Default (comando erroneo):
        print(ERROR_CMD)

def cargar_archivo(archivo, usuarios, canciones):
    grafo = Grafo()
    with open(archivo, 'r') as f:
        for linea in f:
            registro = linea.split('\t')
            usuario_id = registro[1]
            cancion = registro[2]
            artista = registro[3]
            playlist = registro[5]
            cancion_artista = cancion + ' - ' + artista
            grafo.agregar_vertice(usuario_id)
            grafo.agregar_vertice(cancion_artista)
            grafo.agregar_arista(usuario_id, cancion_artista, playlist)
            canciones.add(cancion_artista)
            if usuario_id not in usuarios:
                usuarios[usuario_id] = set()
            if cancion_artista not in usuarios[usuario_id]:
                usuarios[usuario_id].add(cancion_artista)    
    return grafo

# *****************************************************************
#                    PROGRAMA PRINCIPAL
# *****************************************************************
def main():
    if len(sys.argv) != ARGS_CANT:
        print(ERROR_CANT_PARAMETROS)
        return
    usuarios = {}
    canciones = set()
    grafo = cargar_archivo(sys.argv[ARGS_ARCHIVO], usuarios, canciones)
    recomendify(grafo, usuarios, canciones)

if __name__ == "__main__":
    main()