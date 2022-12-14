import time
# Import necesario para la lectura de archivos CSV
import csv
# Import necesario para la creacion de ventanas de interfaz
from tkinter import * 
# Import necesario para la visualizacion de la posicion actual
import turtle
import tkinter as tk


# Variables globales para la identificacion y clasificacion de los objetos dentro del mapa 
PARTE_DEL_CAMINO = '5'
INTENTADO = '.'
OBSTACULO = '1'
BARRERA = '0'
CAJELLON_SIN_SALIDA = '-'
EXIT = '2'
# Variables encargadas de confirmar que se encontro una solucion, de guardar el mapa sin resolver y guardar los paso realizados 
solucion = False
MapClean = []
direccionmapa = []

# Clase que se encarga de crear un objeto (laberinto) la cual tiene la cualidad de: 
# 1. dibujar el laberinto 
# 2. dibujar las cajas (objetos dentro del mapa: barreras, removibles, etc)
# 3. Mover la tortuga, dejar un rastro en la celda visitada y actualizar o cambiar de posicion 
# 4. Determinar si se encontro la salida o un removible
class Laberinto:
    # Se habilitan las variables necesarias para la lectura del archivo CSV (Mapa) 
    def __init__(self,nombreArchivoLaberinto):
        filasEnLaberinto = 0
        columnasEnLaberinto = 0
        self.listaLaberinto = []
        # Se abre el archivo del mapa para leerlo y transcribirlo para trabajar con el
        with open(nombreArchivoLaberinto) as f:
            reader = csv.reader(f, delimiter=";")
            for linea in reader:
                listaFila = []
                columna = 0
                i = 4
                for caracter in linea:
                    listaFila.append(caracter)
                    i = i -1
                    # Se configura el punto inicial del mapa
                    if caracter == '9':
                        self.filaInicio = filasEnLaberinto
                        self.columnaInicio = columna
                    columna = columna + 1
                filasEnLaberinto = filasEnLaberinto + 1
                #
                listaFila.append ('0')
                self.listaLaberinto.append(listaFila)
                columnasEnLaberinto = len(listaFila)
            #    
            self.listaLaberinto.append (['0','0','0','0','0','0'])
            
        # Se actualizan las varibales internas de la clase
        self.filasEnLaberinto = filasEnLaberinto
        self.columnasEnLaberinto = columnasEnLaberinto
        
        # Se setean las dimensiones internas del mapa 
        self.xTranslate = -columnasEnLaberinto/2
        self.yTranslate = filasEnLaberinto/2
        self.t = turtle.Turtle()
        self.t.shape('turtle')
        self.wn = turtle.Screen() 
        self.wn.setworldcoordinates(-(columnasEnLaberinto-1)/2-0.85,-(filasEnLaberinto-1)/2,(columnasEnLaberinto-1)/2-1.15,(filasEnLaberinto-1)/2+0.85)
    
    # Funcion que se encarga de dibujar el laberinto segun la categor??a de cada objeto y le coloca un color respectivo
    def dibujarLaberinto(self):
        self.t.speed(10)
        self.wn.tracer(0)
        for y in range(self.filasEnLaberinto):
            for x in range(self.columnasEnLaberinto):
                if self.listaLaberinto[y][x] == BARRERA:
                    self.dibujarCajaCentrada(x+self.xTranslate,-y+self.yTranslate,'purple')
                elif self.listaLaberinto[y][x] == OBSTACULO:
                    self.dibujarCajaCentrada(x+self.xTranslate,-y+self.yTranslate,'yellow')
                # Tratar de colocar una condicion para la celda de fin
        self.t.color('black')
        self.t.fillcolor('blue')
        self.wn.update()
        self.wn.tracer(1)
    
    # Funcion que se encarga de dibujar la caja/objeto de manera centrada 
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
    
    # Funcion encargada de mover la tortuga de manera visual en el laberinto
    def moverTortuga(self,x,y):
        self.t.up()
        self.t.setheading(self.t.towards(x+self.xTranslate,-y+self.yTranslate))
        self.t.goto(x+self.xTranslate,-y+self.yTranslate)

    # Funcion encargada de dejar un rastro para saber si la casilla ya se visito
    def tirarMigaDePan(self,color):
        self.t.dot(10,color)
        
    # Funcion encargada de mover la tortuga a la posicion "actual" y de definir el color otorgado para el rastro que debe dejar 
    def actualizarPosicion(self,fila,columna,val=None):
        if val:
            self.listaLaberinto[fila][columna] = val
        self.moverTortuga(columna,fila)
        # Se define el color segun la caracteristica de la casilla 
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

    # Se  identifica si es la salida y si es, retorna True
    def esSalida(self,fila,columna):
        if self.listaLaberinto[fila][columna] == EXIT:
            return True

    # Se  identifica si es un Removible y si es, retorna True
    def esObstaculo(self,fila,columna):
        if self.listaLaberinto[fila][columna] == OBSTACULO:
            return True

    def __getitem__(self,indice):
        return self.listaLaberinto[indice]

##################################################################################################################################################

##################################################################################################################################################

# Funcion que se encarga de enviar al ESP32 los pasos que debe realizar para resolver el laberinto
def sendCommand(step):
    total = len(step)
    for i in range (total):
        stepin = step.pop()
        print(stepin)
        # Se envian por medio de la comunicacion serial
        #ser.write(b"stepin\n")
        # El tiempo de espera para enviar las se??ales, en segundos
        # time.sleep(5) 

# Bloque de entrada del usuario
def mapClean():
    # Se lee el mapa del laberinto justo despues de colocar el EXIT, este mapa se usa para saber cuando debe hacer "Chop"
    with open('Maps_Mode2(b).csv') as f:
        reader = csv.reader(f, delimiter=";")
        for row in reader:
            MapClean.append(row)

# Devuelve el mapa resuelto, con el camino utilizado 
def devolucionMR(solucion): 
    if solucion:
        mapSolved = miLaberinto.listaLaberinto
        #print(mapSolved)
        return mapSolved
    else:
        emergente = Tk()
        emergente.geometry('150x100')
        emergente.title('Info usuario')
        info = Label(emergente, text="No se encontro salida")
        info.pack(pady=10)

        btn = Button(emergente, text='Cerrar', command=emergente.destroy)
        btn.pack(pady=10)
        return solucion

# Funcion que se encarga de validar que las entradas sean las correctas y se encuentren dentro del mapa 
def validacion(usuarioFin, ejex, ejey, info): 
    try:
        x = int(ejex.get())
        y = int(ejey.get())

        # Aqui va la funcion que ingresa el punto de inicio despues de validar
        # Que el espacio no se encuentre ocupado por una barrera
        if x<len(miLaberinto.listaLaberinto) and x!=5:
            if y<len(miLaberinto.listaLaberinto[1]) and y!=5:
                if miLaberinto.listaLaberinto[x][y] == '':
                    info.config(text='La coordenada es valida')
                    mapClean()
                    miLaberinto.listaLaberinto[x][y] = EXIT
                    MapClean[x][y] = EXIT
                    time.sleep(1)
                    usuarioFin.destroy()
                    solucion = buscarDesde(miLaberinto, miLaberinto.filaInicio, miLaberinto.columnaInicio, 'inicio')
                    devolucionMR(solucion)
                else:
                    info.config(text='La coordenada no se encuentra libre')
        else:
            info.config(text='La coordenada no se encuentra dentro del mapa')
    except ValueError:
       info.config(text='La coordenada no es v??lida')

# Funcion que le permite al usuario escoger la posici??n final o de salida, creando una ventana de interfaz
def puntoFin(): 
    usuarioFin = Tk()
    usuarioFin.title('Ventana de usuario')
    usuarioFin.geometry('300x250')

    CoorEjeX = Label(usuarioFin, text="Coordenada eje y:")
    CoorEjeX.pack(pady=10)
    
    # Entradas del usuario para ambos ejes 
    ejex = Entry(usuarioFin)
    ejex.pack(pady=10)

    CoorEjeY = Label(usuarioFin, text="Coordenada eje x:")
    CoorEjeY.pack(pady=10)

    ejey = Entry(usuarioFin)
    ejey.pack(pady=10)

    info = Label(usuarioFin, text='')
    info.pack(pady=10)
    
    # Boton que se encarga de ir a la funci??n para validar las entradas del usuario
    btn = Button(usuarioFin, text='Validar la coordenada', command=lambda: validacion(usuarioFin ,ejex, ejey, info))
    btn.pack(pady=10)

    usuarioFin.mainloop()

# Funcion principal que se encarga de buscar las casillas libres y los pasos que se tuvieron que realizar 
def buscarDesde(laberinto, filaInicio, columnaInicio, paso):
    laberinto.actualizarPosicion(filaInicio, columnaInicio)
    #  Verificar casos base:
    # 1. Hemos tropezado con un barrera, devolver False
    if laberinto[filaInicio][columnaInicio] == BARRERA:
        return False
    # 2. Hemos encontrado un cuadrado que ya ha sido explorado
    if laberinto[filaInicio][columnaInicio] == INTENTADO:
        return False

    if laberinto[filaInicio][columnaInicio] == CAJELLON_SIN_SALIDA:
        return False
    # 3. Hemos encontrado un obst??culo removible
    if laberinto.esObstaculo(filaInicio,columnaInicio):
        laberinto.actualizarPosicion(filaInicio, columnaInicio, OBSTACULO)
    # 4. exito, una celda no ocupada por un obstaculo, se agrega como parte del camino de resolucion
    if laberinto.esSalida(filaInicio,columnaInicio):
        laberinto.actualizarPosicion(filaInicio, columnaInicio, PARTE_DEL_CAMINO)
        # Se agrega el paso realizado a una lista de steps para resolver indicando que no lleva "Chop"
        direccionmapa.append('n '+paso)
        return True

    laberinto.actualizarPosicion(filaInicio, columnaInicio, INTENTADO)

    # Para probar la direccion que se debe tomar para la solucion se agrega como parametro de la funcion recursiva 
    encontrado = buscarDesde(laberinto, filaInicio-1, columnaInicio, 'arriba') or \
            buscarDesde(laberinto, filaInicio+1, columnaInicio, 'abajo') or \
            buscarDesde(laberinto, filaInicio, columnaInicio-1, 'izquierda') or \
            buscarDesde(laberinto, filaInicio, columnaInicio+1, 'derecha')
    
    if encontrado:
        # Compara la posicion que se va a agregar como parte del camino con el mapa sin resolver, para verificar si se debe hacer chop o no a la celda 
        if MapClean[filaInicio][columnaInicio] == '1':
            laberinto.actualizarPosicion(filaInicio, columnaInicio, PARTE_DEL_CAMINO)
            # s = Si Chop
            direccionmapa.append('s '+paso)
        else: 
            laberinto.actualizarPosicion(filaInicio, columnaInicio, PARTE_DEL_CAMINO)
            # n = No Chop
            direccionmapa.append('n '+paso)
    else:
        laberinto.actualizarPosicion(filaInicio, columnaInicio, CAJELLON_SIN_SALIDA)
    return encontrado

# Se inicializa el objeto del Laberinto con el Archivo CSV 
# Se dibuja el laberinto de manera inicial para que el usuario pueda ver lasz casillas disponibles para colocar el punto de fin
miLaberinto = Laberinto('Maps_Mode2(b).csv')
miLaberinto.dibujarLaberinto()
miLaberinto.actualizarPosicion(miLaberinto.filaInicio,miLaberinto.columnaInicio)
puntoFin()
# Una vez resuelto el laberinto se envian los steps al ESP32
sendCommand(direccionmapa)
