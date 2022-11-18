import csv
from tkinter import *

import turtle
import tkinter as tk

PARTE_DEL_CAMINO = '5'
INTENTADO = '.'
OBSTACULO = '1'
BARRERA = '0'
CAJELLON_SIN_SALIDA = '-'
EXIT = '2'
solucion = False


class Laberinto:
    def __init__(self,nombreArchivoLaberinto):
        filasEnLaberinto = 0
        columnasEnLaberinto = 0
        self.listaLaberinto = []
        with open(nombreArchivoLaberinto) as f:
            reader = csv.reader(f, delimiter=";")
            for linea in reader:
                listaFila = []
                columna = 0
                i = 4
                for caracter in linea:
                    listaFila.append(caracter)
                    i = i -1
                    if caracter == '9':
                        self.filaInicio = filasEnLaberinto
                        self.columnaInicio = columna
                    columna = columna + 1
                filasEnLaberinto = filasEnLaberinto + 1
                listaFila.append ('0')
                self.listaLaberinto.append(listaFila)
                columnasEnLaberinto = len(listaFila)
            self.listaLaberinto.append (['0','0','0','0','0','0'])

        self.filasEnLaberinto = filasEnLaberinto
        self.columnasEnLaberinto = columnasEnLaberinto
        self.xTranslate = -columnasEnLaberinto/2
        self.yTranslate = filasEnLaberinto/2
        self.t = turtle.Turtle()
        self.t.shape('turtle')
        self.wn = turtle.Screen()  #desde acá se cree que se puede cerrar la ventana
        self.wn.setworldcoordinates(-(columnasEnLaberinto-1)/2-0.85,-(filasEnLaberinto-1)/2,(columnasEnLaberinto-1)/2-1.15,(filasEnLaberinto-1)/2+0.85)

    def dibujarLaberinto(self):
        self.t.speed(10)
        self.wn.tracer(0)
        for y in range(self.filasEnLaberinto):
            for x in range(self.columnasEnLaberinto):
                if self.listaLaberinto[y][x] == BARRERA:
                    self.dibujarCajaCentrada(x+self.xTranslate,-y+self.yTranslate,'purple')
                elif self.listaLaberinto[y][x] == OBSTACULO:
                    self.dibujarCajaCentrada(x+self.xTranslate,-y+self.yTranslate,'yellow')
        self.t.color('black')
        self.t.fillcolor('blue')
        self.wn.update()
        self.wn.tracer(1)

    def dibujarCajaCentrada(self,x,y,color):
        self.t.up()
        self.t.goto(x-.5,y-.5)
        self.t.color(color)
        self.t.fillcolor(color)
        self.t.setheading(90)
        self.t.down()
        self.t.begin_fill()
        for i in range(4):
            self.t.forward(1)
            self.t.right(90)
        self.t.end_fill()

    def moverTortuga(self,x,y):
        self.t.up()
        self.t.setheading(self.t.towards(x+self.xTranslate,-y+self.yTranslate))
        self.t.goto(x+self.xTranslate,-y+self.yTranslate)

    def tirarMigaDePan(self,color):
        self.t.dot(10,color)

    def actualizarPosicion(self,fila,columna,val=None):
        if val:
            self.listaLaberinto[fila][columna] = val
        self.moverTortuga(columna,fila)

        if val == PARTE_DEL_CAMINO:
            color = 'green'
        elif val == OBSTACULO:
            color = 'blue'
        elif val == INTENTADO:
            color = 'black'
        elif val == CAJELLON_SIN_SALIDA:
            color = 'red'
        else:
            color = None

        if color:
            self.tirarMigaDePan(color)

    def esSalida(self,fila,columna):
        if self.listaLaberinto[fila][columna] == EXIT:
            return True

    def esObstaculo(self,fila,columna):
        if self.listaLaberinto[fila][columna] == OBSTACULO:
            return True

    def __getitem__(self,indice):
        return self.listaLaberinto[indice]

##################################################################################################################################################

# Bloque de entrada del usuario
def devolucionMR():  # Devuelve el mapa resuelto
    try:
        solucion==True
        mapSolved = miLaberinto.listaLaberinto
        print(mapSolved)
        return mapSolved
    except:
        pass

def validacion(usuarioFin, ejex, ejey, info):  # Valida que las entradas sean las correctas
    try:
        x = int(ejex.get())
        y = int(ejey.get())

        # Aqui va la funcion que ingresa el punto de inicio despues de validar
        # Que el espacio no se encuentre ocupado por una barrera
        if x<len(miLaberinto.listaLaberinto) and x!=5:
            if y<len(miLaberinto.listaLaberinto[1]) and y!=5:
                if miLaberinto.listaLaberinto[x][y] == '':
                    info.config(text='La coordenada es valida')
                    miLaberinto.listaLaberinto[x][y] = EXIT
                    usuarioFin.destroy()
                    solucion = buscarDesde(miLaberinto, miLaberinto.filaInicio, miLaberinto.columnaInicio)
                    devolucionMR()

                else:
                    info.config(text='La coordenada no se encuentra libre')
        else:
            info.config(text='La coordenada no se encuentra dentro del mapa')
    except ValueError:
       info.config(text='La coordenada no es válida')


def puntoFin():  #le permite al usuario escoger la posición final o de salida
    usuarioFin = Tk()
    usuarioFin.title('Ventana de usuario')
    usuarioFin.geometry('300x250')

    CoorEjeX = Label(usuarioFin, text="Coordenada eje y:")
    CoorEjeX.pack(pady=10)

    ejex = Entry(usuarioFin)
    ejex.pack(pady=10)

    CoorEjeY = Label(usuarioFin, text="Coordenada eje x:")
    CoorEjeY.pack(pady=10)

    ejey = Entry(usuarioFin)
    ejey.pack(pady=10)

    info = Label(usuarioFin, text='')
    info.pack(pady=10)

    btn = Button(usuarioFin, text='Validar la coordenada', command=lambda: validacion(usuarioFin ,ejex, ejey, info))
    btn.pack(pady=10)

    usuarioFin.mainloop()

def buscarDesde(laberinto, filaInicio, columnaInicio):
    laberinto.actualizarPosicion(filaInicio, columnaInicio)
    #  Verificar casos base:
    # 1. Hemos tropezado con un barrera, devolver False
    if laberinto[filaInicio][columnaInicio] == BARRERA:
        return False
    # 2. Hemos encontrado un cuadrado que ya ha sido explorado
    if laberinto[filaInicio][columnaInicio] == INTENTADO:
        return False
    # 3. Hemos encontrado un obstáculo removible
    if laberinto.esObstaculo(filaInicio,columnaInicio):
        laberinto.actualizarPosicion(filaInicio, columnaInicio, OBSTACULO)
        return True
    # 4. Éxito, un borde exterior no ocupado por un obstáculo
    if laberinto.esSalida(filaInicio,columnaInicio):
        laberinto.actualizarPosicion(filaInicio, columnaInicio, PARTE_DEL_CAMINO)
        return True

    laberinto.actualizarPosicion(filaInicio, columnaInicio, INTENTADO)

    # De lo contrario, use cortocircuitos lógicos para probar cada
    # dirección a su vez (si fuera necesario)
    encontrado = buscarDesde(laberinto, filaInicio-1, columnaInicio) or \
            buscarDesde(laberinto, filaInicio+1, columnaInicio) or \
            buscarDesde(laberinto, filaInicio, columnaInicio-1) or \
            buscarDesde(laberinto, filaInicio, columnaInicio+1)
    if encontrado:
        laberinto.actualizarPosicion(filaInicio, columnaInicio, PARTE_DEL_CAMINO)
    else:
        laberinto.actualizarPosicion(filaInicio, columnaInicio, CAJELLON_SIN_SALIDA)
    return encontrado

miLaberinto = Laberinto('Maps_Mode2(b).csv')
miLaberinto.dibujarLaberinto()
miLaberinto.actualizarPosicion(miLaberinto.filaInicio,miLaberinto.columnaInicio)
puntoFin()