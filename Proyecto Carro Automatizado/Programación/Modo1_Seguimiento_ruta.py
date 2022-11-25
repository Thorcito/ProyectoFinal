from Setup_Interfaz_Mode1 import *
import time 
import os
import sys 
import serial 

Matriz_trabajo = [[]]
color = 0
direccion = 0
#se establece la comunicacion serial
#ser = serial.Serial('/dev/ttyUSB0',9600, timeout=1)
#ser.flush()

#se definen las variables con las que se va a trabajar
def paso_siguiente(fila, columna):
    #mover el motor en la direccion correcta
    celda_actual = int(Matriz_trabajo[fila][columna])
    color = detectar_color(celda_actual)
    direccion = direccion_pasos(celda_actual)
    if color == 'azul':
        #ser.write(b"direccion\n")
        verificación_celda(direccion, fila, columna)
        time.sleep(1)
        #ser.write(b"forward\n")
        if direccion == 'arriba':
            fila = fila-1

        if direccion == 'abajo':
            fila = fila+1

        if direccion == 'izquierda':
            columna = columna-1

        if direccion == 'derecha':
            columna = columna+1

    if color == 'verde':
        #ser.write(b"direccion\n")
        verificación_celda(direccion, fila, columna)
        time.sleep(1)
        #ser.write(b"forward\n")
        if direccion == 'arriba':
            fila = fila-1

        if direccion == 'abajo':
            fila = fila+1

        if direccion == 'izquierda':
            columna = columna-1

        if direccion == 'derecha':
            columna = columna+1

    if color == 'rojo':
        # Tiempo reglamentario
        time.sleep(5)
        #ser.write(b"direccion\n")
        verificación_celda(direccion, fila, columna)
        time.sleep(1)
        #ser.write(b"forward\n")
        if direccion == 'arriba':
            fila = fila-1

        if direccion == 'abajo':
            fila = fila+1

        if direccion == 'izquierda':
            columna = columna-1

        if direccion == 'derecha':
            columna = columna+1

    if color == 'gris':
        #ser.write(b"direccion\n")
        verificación_celda(direccion, fila, columna)
        time.sleep(1)
        #ser.write(b"forward\n")
        if direccion == 'arriba':
            fila = fila-1

        if direccion == 'abajo':
            fila = fila+1

        if direccion == 'izquierda':
            columna = columna-1

        if direccion == 'derecha':
            columna = columna+1

    if color == 'morado':
        MORADO(fila,columna)

    paso_siguiente(fila, columna)




#Funcion auxiliar para detectar la direccion de los pasos segun el valor de la casilla
def verificacion_celda(direccion, fila, columna):

    if direccion == 'arriba':
        if detectar_color(Matriz_trabajo[fila-1][columna]) == 'gris':
        # golpe a la pared reglamentario
        #ser.write(b"chop\n")

    if direccion == 'abajo':
        if detectar_color(Matriz_trabajo[fila+1][columna]) == 'gris':
        # golpe a la pared reglamentario
        #ser.write(b"chop\n")

    if direccion == 'izquierda':
        if detectar_color(Matriz_trabajo[fila][columna-1]) == 'gris':
        # golpe a la pared reglamentario
        #ser.write(b"chop\n")

    if direccion == 'derecha':
        if detectar_color(Matriz_trabajo[fila][columna+1]) == 'gris':
        # golpe a la pared reglamentario
        #ser.write(b"chop\n")

    if detectar_color(Matriz_trabajo[fila-1][columna]) == 'gris':
##

def MORADO(direccion,fila,columna):
    #avanzar hasta que se encuentre un cero, un borde, en la direccion respectiva
        if direccion == 'arriba':
            while fila>0:
                # ser.write(b"direccion\n")
                fila=fila-1

            paso_siguiente(fila, columna)

        if direccion == 'abajo':
            while fila < 4:
                # ser.write(b"direccion\n")
                fila = fila + 1
            paso_siguiente(fila, columna)

        if direccion == 'izquierda':
            while columna > 0:
                # ser.write(b"direccion\n")
                columna = columna - 1
            paso_siguiente(fila, columna)

        if direccion == 'derecha':
            while columna < 4:
                # ser.write(b"direccion\n")
                columna = columna + 1
            paso_siguiente(fila, columna)
#Funcion auxiliar de AbrirCSV que permite traer la matriz de Interfaz.py

def extraerMatriz():
    for fila in range (1, 6): #este rango definido permite validar que el mapa no se extienda de los parametros establecidos
        nuevo_valor = sacarElementos(fila)  #se obtienen la filas de la matriz extraida
        Matriz_trabajo.append(nuevo_valor)
    print ('traslado de matriz completado')
    for fila in range (0, len(Matriz_trabajo)):  #permite la comprobacion del mapa
        print ('fila: ', fila, 'valor:', Matriz_trabajo[fila])
#Funcion se encarga de decodificar str a un int, para poder procesar la informacion

def deteccionSTRtoINT():
    #se realiza un barrido de la matriz buscando los elementos que deben ser convertidos
    for fila in range (0, len(Matriz_trabajo)):
        for columna in range (0, len(Matriz_trabajo[fila])):
            if (Matriz_trabajo[fila][columna]) == '':
                pass;
            else:
                #se encuentra un celda que no esta vacia y convierte el valor de lo que haya en esta
                valorAconvetir=int(Matriz_trabajo[fila][columna])
                #print(type(valorAconvetir))
                #print(valorAconvetir)
                #se envia el valor convertido para ser procesado e identificar el color y la direccion
                #print(detectar_color(valorAconvetir))
                #print(direccion_pasos(valorAconvetir))
#Funcion se encarga de obtener la ubicacion del inicio del mapa y la retorna

def encontrarInicio():
    for fila in range (0, len(Matriz_trabajo)):
        for columna in range(0, len(Matriz_trabajo[fila])):
            if (Matriz_trabajo[fila][columna]) >= '90':
                print ('El inicio del recorrido es en la:', 'fila', fila, 'columna', columna)
                filaIni=fila
                columnaIni=columna
                return(filaIni, columnaIni)
#Funcion auxiliar para detectar el color de la casilla

def detectar_color(valor_casilla_excel_read):
    if type(valor_casilla_excel_read) == int:
        color = 8;
        if ((valor_casilla_excel_read//10)==1):
            color = "verde";
            return color
        elif ((valor_casilla_excel_read//10)==2):
            color = "rojo";
            return color
        elif ((valor_casilla_excel_read//10)==3):
            color = "gris";
            return color
        elif ((valor_casilla_excel_read//10)==4):
            color = "morado";
            return color
        elif ((valor_casilla_excel_read//10)==9):
            color = "azul";
            return color
        else:
            return "color no detectado"
    else:
        return "valor casilla no es int"
#Funcion auxiliar para detectar la direccion de los pasos segun el valor de la casilla





def direccion_pasos(valor_casilla_excel_read):
        if type(valor_casilla_excel_read) == int:
                direccion = 0;
                if ((valor_casilla_excel_read%10)==0):
                        direccion = "arriba";
                        return direccion
                elif ((valor_casilla_excel_read%10)==1):
                        direccion = "derecha";
                        return direccion
                elif ((valor_casilla_excel_read%10)==2):
                        direccion = "izquierda";
                        return direccion
                elif ((valor_casilla_excel_read%10)==3):
                        direccion = "abajo";
                        return direccion
                else:
                        return "direccion no detectada"
        else:
                return "valor casilla no es un int"
# golpe a la pared reglamentario
        #ser.write(b"chop\n")


#Inicio del codigo se pide un mapa atraves de un CSV y la funcion main
def __main__():
    extraerMatriz() #esta funcion se encarga de obtener la matriz leida en la interfaz *siempre debe llamarse para que funcione el codigo*
    deteccionSTRtoINT() #esta funcion se encarga de decodificar los valores que se encuentran en las celdas
    filaIni, columnaIni = encontrarInicio()  #esta funcion se encarga de obtener la ubicacion del inicio del mapa, este siempre inicia con 9
    paso_siguiente(filaIni, columnaIni)
__main__()
#Funcion auxiliar para detectar la siguiente instruccion a ejecutar
