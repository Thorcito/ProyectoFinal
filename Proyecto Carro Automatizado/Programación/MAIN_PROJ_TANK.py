from tkinter import *
from tkinter.ttk import *
import os
import sys 
import serial 

# Crea el la ventana Tk
Window = Tk()

#se establece la comunicación serial
#ser = serial.Serial('/dev/ttyUSB0',9600, timeout=1)
#ser.flush()

# Función que se encarga de abrir el modo 1
def mode1():
     print('modo 1')
     #ser.write(b"Auto\n")
     os.system("python Modo1_Seguimiento_ruta.py") 
     #ser.write(b"Atras\n")
     labelStatus.config(text='Check status: Modo 1 Completado')

# Función que se encarga de abrir el modo 2
def mode2():
     print('modo 2')
     #ser.write(b"Auto\n")
     os.system("python Modo2_Busqueda_ruta.py") 
     #ser.write(b"Atras\n")
     labelStatus.config(text='Check status: Modo 2 Completado')
     
# Función que se encarga de abrir el modo 3
def mode3():
     print('modo 3')
     ser.write(b"Manual\n")
     #os.system("python Modo3_Manual.py") 
     #Se imprime el comando en el monitor serial con el fin de salirse del modo actual
     #ser.write(b"Atras\n")
     labelStatus.config(text='Check status: Modo 3 Completado')
    
 # set de las dimensiones
Window.geometry("400x270")
Window.title("Interfaz de Usuario")
label = Label(Window,
              text ="Bienvenido al centro de comandos del K-M7G Behemoth")
 
label.pack(pady = 10)
 
# Se agregan los botones
# Primero se agrega el boton que le corresponde al modo 1
btnM1 = Button(Window,
             text ="Modo 1: Reconocimiento de la Zona!",
             command = mode1)
btnM1.pack(pady = 10)

# Primero se agrega el boton que le corresponde al modo 2
btnM2 = Button(Window,
             text ="Modo 2: Ataque coordinado!",
             command = mode2)
btnM2.pack(pady = 10)

# Primero se agrega el boton que le corresponde al modo 3
btnM3 = Button(Window,
             text ="Modo 3: Control Manual de EMERGENCIA!",
             command = mode3)
btnM3.pack(pady = 10)

# Botón que se encarga de salirse de modo, ya sea manual o auto
btnQ = Button(Window,
             text ="Liberar Control",
             command = ser.write(b"Atras\n"))
btnQ.pack(pady = 10)

#Tag que me indica el status de la acción
labelStatus = Label(Window,
              text ="Check status: Libre (Sin modo de control)")
 
labelStatus.pack(pady = 10)

# Botón que se encarga de salirse de la ventana
btnExit = Button(Window,
             text ="Liberar Control",
             command = Window.destroy)
btnExit.pack(pady = 10)
mainloop()
