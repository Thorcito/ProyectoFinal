from tkinter import *
from tkinter.ttk import *
 
# Crea el la ventana Tk
Window = Tk()
 
# Función que se encarga de abrir el modo 1
def mode1():
     print('modo 1')

# Función que se encarga de abrir el modo 2
def mode2():
     print('modo 2')

# Función que se encarga de abrir el modo 3
def mode3():
     print('modo 3')
    
 # set de las dimensiones
Window.geometry("400x250")
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

 # Primero se agrega el boton que le corresponde al modo 1
btnQ = Button(Window,
             text ="Liberar Control",
             command = Window.destroy)
btnQ.pack(pady = 10)


mainloop()
