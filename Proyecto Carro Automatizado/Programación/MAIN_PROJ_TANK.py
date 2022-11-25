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
     # Se envía al ESP32 el modo que se va a utilizar para el Modo1 
     #ser.write(b"Auto\n")
     # Se abre el archivo de Python correpondiente al modo 1
     os.system("python Modo1_Seguimiento_ruta.py")
     # Se actualiza en la interfaz el estatus del código 
     labelStatus.config(text='Check status: Modo 1 En Ejecución')

# Función que se encarga de abrir el modo 2
def mode2():
     print('modo 2')
     #ser.write(b"Auto\n")
     os.system("python Modo2_Busqueda_ruta.py") 
     labelStatus.config(text='Check status: Modo 2 En Ejecución')
     
# Función que se encarga de abrir el modo 3
def mode3():
     print('modo 3')
     # Se envía al ESP32 el modo que se va a utilizar para el Modo3 
     #ser.write(b"Manual\n")
     # Se deja la opción de ingresar un archivo py para el modo 3, en este caso no se va a utilizar 
     os.system("python Modo3_Manual.py") 
     labelStatus.config(text='Check status: Modo 3 En Ejecución')

# Función que se encarga de salirse del auto o del manual
def mode4():
     #ser.write(b"Atras\n")
     labelStatus.config(text='Check status: Cambio de Modo Ejecutado')
    
# Set de las dimensiones de la ventana de interfaz
Window.geometry("400x310")
Window.title("Interfaz de Usuario")
label = Label(Window, text ="Bienvenido al centro de comandos del K-M7G Behemoth")
# Se limita la dimensión en el eje y de la etiqueta
label.pack(pady = 10)
 
# Se agregan los botones
# Primero se agrega el boton que le corresponde al modo 1
btnM1 = Button(Window, text ="Modo 1: Reconocimiento de la Zona!", command = mode1)
btnM1.pack(pady = 10)

# Primero se agrega el boton que le corresponde al modo 2
btnM2 = Button(Window, text ="Modo 2: Ataque coordinado!", command = mode2)
btnM2.pack(pady = 10)

# Primero se agrega el boton que le corresponde al modo 3
btnM3 = Button(Window, text ="Modo 3: Control Manual de EMERGENCIA!", command = mode3)
btnM3.pack(pady = 10)

# Botón que se encarga de salirse de modo, ya sea manual o auto
btnQ = Button(Window, text ="Cambio de Control", command = mode4)
btnQ.pack(pady = 10)

#Tag que me indica el status de la acción
labelStatus = Label(Window, text ="Check status: Libre (Sin modo de control)")
labelStatus.pack(pady = 10)

# Botón que se encarga de salirse de la ventana
btnExit = Button(Window, text = "Cerrar Comando", command = Window.destroy)
btnExit.pack(pady = 10)

mainloop()
