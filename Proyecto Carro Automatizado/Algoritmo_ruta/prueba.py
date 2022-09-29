from tkinter import * 

import turtle
import tkinter as tk

#bloque de entrada del usuario
def validacion(usuarioFin, ejex, ejey, info):
    try: 
        x = int(ejex.get())
        y = int(ejey.get())

        info.config(text='La coordenada es valida')

        #aqui va la funcion que ingresa el punto de inicio despues de validar
        #que el espacio no se encuentre ocupado por una barrera\
        
        usuarioFin.destroy()
    except ValueError: 
       info.config(text='La coordenada no es valida')


def puntoFin():
    usuarioFin = Tk()
    usuarioFin.title('Ventana de usuario')
    usuarioFin.geometry('300x300')

    CoorEjeX = Label(usuarioFin, text="Coordenada eje X:")
    CoorEjeX.pack(pady=10)

    ejex = Entry(usuarioFin)
    ejex.pack(pady=10)

    CoorEjeY = Label(usuarioFin, text="Coordenada eje Y:")
    CoorEjeY.pack(pady=10)

    ejey = Entry(usuarioFin)
    ejey.pack(pady=10)

    info = Label(usuarioFin, text='')
    info.pack(pady=20)

    btn = Button(usuarioFin, text='Nice day BITCH', command=lambda: validacion(usuarioFin ,ejex, ejey, info))
    btn.pack(pady=5)

 


    usuarioFin.mainloop()


puntoFin()

PARTE_DEL_CAMINO = 'O'
INTENTADO = '.'
OBSTACULO = '1'
CAJELLON_SIN_SALIDA = '-'
EXIT = '2'

class Laberinto:
    def __init__(self,nombreArchivoLaberinto):
        filasEnLaberinto = 0
        columnasEnLaberinto = 0
        self.listaLaberinto = []
        archivoLaberinto = open(nombreArchivoLaberinto,'r')
        filasEnLaberinto = 0
        for linea in archivoLaberinto:
            listaFila = []
            columna = 0
            for caracter in linea[:-1]:
                listaFila.append(caracter)
                if caracter == '9':
                    self.filaInicio = filasEnLaberinto
                    self.columnaInicio = columna
                columna = columna + 1
            filasEnLaberinto = filasEnLaberinto + 1
            self.listaLaberinto.append(listaFila)
            columnasEnLaberinto = len(listaFila)

        self.filasEnLaberinto = filasEnLaberinto
        self.columnasEnLaberinto = columnasEnLaberinto
        self.xTranslate = -columnasEnLaberinto/2
        self.yTranslate = filasEnLaberinto/2
        self.t = turtle.Turtle()
        self.t.shape('turtle')
        self.wn = turtle.Screen()
        self.wn.setworldcoordinates(-(columnasEnLaberinto-1)/2-.5,-(filasEnLaberinto-1)/2-.5,(columnasEnLaberinto-1)/2+.5,(filasEnLaberinto-1)/2+.5)

    def dibujarLaberinto(self):
        self.t.speed(10)
        self.wn.tracer(0)
        for y in range(self.filasEnLaberinto):
            for x in range(self.columnasEnLaberinto):
                if self.listaLaberinto[y][x] == OBSTACULO:
                    self.dibujarCajaCentrada(x+self.xTranslate,-y+self.yTranslate,'orange')
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
            color = 'red'
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

    def __getitem__(self,indice):
        return self.listaLaberinto[indice]


def buscarDesde(laberinto, filaInicio, columnaInicio):
    laberinto.actualizarPosicion(filaInicio, columnaInicio)
   #  Verificar casos base:
   #  1. Hemos tropezado con un obstáculo, devolver False
    if laberinto[filaInicio][columnaInicio] == OBSTACULO :
        return False
    #  2. Hemos encontrado un cuadrado que ya ha sido explorado
    if laberinto[filaInicio][columnaInicio] == INTENTADO:
        return False
    # 3. Éxito, un borde exterior no ocupado por un obstáculo
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

miLaberinto = Laberinto('laberinto2.txt')
miLaberinto.dibujarLaberinto()
miLaberinto.actualizarPosicion(miLaberinto.filaInicio,miLaberinto.columnaInicio)

solucion = buscarDesde(miLaberinto, miLaberinto.filaInicio, miLaberinto.columnaInicio)
if solucion == False:
    print('No se encuentra una ruta para la coordenada deseada')
else: 
    for i in range(len(miLaberinto.listaLaberinto)):
        print(miLaberinto.listaLaberinto[i] )

        #hacer el input del usuario para la posicion final, una vez se tenga la posIni y la posFin, 
        #se envia al carro para que lea el patron con la ruta correcta