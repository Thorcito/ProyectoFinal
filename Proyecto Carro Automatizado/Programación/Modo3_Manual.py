import serial 
from tkinter import *
import tkinter as tk

#se establece la comunicación serial
#ser = serial.Serial('/dev/ttyUSB0',9600, timeout=1)
#ser.flush()

def validacion(usuarioIni, ejex, ejey, info): 
    try:
        x = int(ejex.get())
        y = int(ejey.get())

        # Aqui va la función que ingresa el punto de inicio despues de validar
        # Que el espacio no se encuentre ocupado por una barrera
        if x<=5 and x>=1:
            if y<=5 and y>=1:
              info.config(text='La coordenada es valida')
              ini=x*10+y
              #ser.write(b"ini\n")
            else:
              info.config(text='La coordenada en y no valida')
        else:
            info.config(text='La coordenada no valida')
    except ValueError:
       info.config(text='Las coordenadas no son numeros')

def puntoIni():
  usuarioIni = Tk()
  usuarioIni.title('Ventana de usuario')
  usuarioIni.geometry('300x250')

  CoorEjeX = Label(usuarioIni, text="Coordenada eje x:")
  CoorEjeX.pack(pady=10)
    
  # Entradas del usuario para ambos ejes 
  ejex = Entry(usuarioIni)
  ejex.pack(pady=10)

  CoorEjeY = Label(usuarioIni, text="Coordenada eje y:")
  CoorEjeY.pack(pady=10)

  ejey = Entry(usuarioIni)
  ejey.pack(pady=10)

  info = Label(usuarioIni, text='')
  info.pack(pady=10)
    
  # Botón que se encarga de ir a la función para validar las entradas del usuario
  btn = Button(usuarioIni, text='Validar la coordenada', command=lambda: validacion(usuarioFin ,ejex, ejey, info))
  btn.pack(pady=10)

  usuarioFin.mainloop()

#ser.write(b"Manual\n")
