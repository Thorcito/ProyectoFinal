from tkinter import *
# Raiz
root = Tk()
# Titulo
root.title("Interfaz Torreta")
# Icono
root.iconbitmap("turret_icon.ico")
# Redimensionable?
root.resizable(0, 0)
# Ancho y alto
root.geometry("325x300")
# Color
root.config(bg="black",
            relief="groove",
            bd="20")
# Marco
frame = Frame(root)
frame.pack()
frame.config(width=660,
             height=410,
             bg="white",
             relief="groove",
             bd="30")

# Label
Label(frame, text="------MODOS DE LA TORRETA------").grid(row=1, columnspan=20)
Label(frame).grid(row=4, columnspan=20)
Label(frame).grid(row=8, columnspan=20)
Label(frame).grid(row=12, columnspan=20)
Label(frame).grid(row=16, columnspan=20)

# Botones
Button(frame, text="MODO MANUAL").grid(row=6, column=10)
Button(frame, text="MODO PROGRAMABLE").grid(row=10, column=10)
Button(frame, text="MODO WATCHDOG").grid(row=14, column=10)
Button(frame, text="SALIR", command="destroy .").grid(row=18, column=10)

# Loop infinito
root.mainloop()




