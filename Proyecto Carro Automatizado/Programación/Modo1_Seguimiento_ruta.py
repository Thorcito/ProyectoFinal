from Setup_Interfaz_Mode1 import *
import time 
import os
import sys 
import serial 

#se definen las variables con las que se va a trabajar
Matriz_trabajo = [[]]

color = 0 
direccion = 0

#se establece la comunicación serial
#ser = serial.Serial('/dev/ttyUSB0',9600, timeout=1)
#ser.flush()

##
def MORADO(fila,columna):
    #avanzar hasta que se encuentre un cero, un borde, en la dirección respectiva
    for i in range(columna, len(Matriz_trabajo[0])-1):
        if direccion == 'arriba':
            fila = fila-1
            if detectar_color(Matriz_trabajo[fila][columna]) == 'gris':
                #ser.write(b"stop\n") 
            paso_siguiente(fila, columna) 

        if direccion == 'abajo':
            fila = fila+1

        if direccion == 'izquierda':
            columna = columna-1

        if direccion == 'derecha':   
            columna = columna+1
            if detectar_color(Matriz_trabajo[fila][columna])
                #ser.write(b"direccion\n")
                time.sleep(1)
#Función auxiliar de AbrirCSV que permite traer la matriz de Interfaz.py
def extraerMatriz():
    for fila in range (1, 6): #este rango definido permite validar que el mapa no se extienda de los parámetros establecidos 
        nuevo_valor = sacarElementos(fila)  #se obtienen la filas de la matriz extraída
        Matriz_trabajo.append(nuevo_valor)
    print ('traslado de matriz completado')
    for fila in range (0, len(Matriz_trabajo)):  #permite la comprobación del mapa 
        print ('fila: ', fila, 'valor:', Matriz_trabajo[fila])

#Función se encarga de decodificar str a un int, para poder procesar la información
def deteccionSTRtoINT():
    #se realiza un barrido de la matriz buscando los elementos que deben ser convertidos 
    for fila in range (0, len(Matriz_trabajo)):
        for columna in range (0, len(Matriz_trabajo[fila])):
            if (Matriz_trabajo[fila][columna]) == '':
                pass;
            else:
                #se encuentra un celda que no está vacía y convierte el valor de lo que haya en esta
                valorAconvetir=int(Matriz_trabajo[fila][columna])
                #print(type(valorAconvetir))
                #print(valorAconvetir)
                #se envía el valor convertido para ser procesado e identificar el color y la dirección 
                #print(detectar_color(valorAconvetir))
                #print(direccion_pasos(valorAconvetir))

#Función se encarga de obtener la ubicación del inicio del mapa y la retorna
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

#Funcion auxiliar para detectar la siguiente instrucción a ejecutar
def paso_siguiente(fila, columna):
    #mover el motor en la dirección correcta 
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
def verificación_celda(direccion, fila, columna):

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
        # golpe a la pared reglamentario
        #ser.write(b"chop\n")   
    

#Inicio del código se pide un mapa através de un CSV y la función main
def __main__():
    extraerMatriz() #esta función se encarga de obtener la matriz leída en la interfaz *siempre debe llamarse para que funcione el código*
    deteccionSTRtoINT() #esta función se encarga de decodificar los valores que se encuentran en las celdas
    filaIni, columnaIni = encontrarInicio()  #esta función se encarga de obtener la ubicación del inicio del mapa, este siempre inicia con 9
    paso_siguiente(filaIni, columnaIni)

__main__()