from tkinter import * 
from tkinter import filedialog
raiz=Tk()

def AbrirArchivo():
	archivo = filedialog.askopenfilename(title= "Seleccione el mapa", initialdir = "C:/Users/usuario/Desktop", filetypes = ((" Archivos de Texto","*.txt"),(" Archivos de Archivo de valores separados por comas de Microsoft Excel","*.csv"),(" Todos los Archivos","*.*")))
	print(archivo)

Button (raiz, text= "Abrir archivo", command = AbrirArchivo).pack()

raiz.mainloop()