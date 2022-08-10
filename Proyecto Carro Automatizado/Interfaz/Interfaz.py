import csv
from tkinter import * 
from tkinter import filedialog

raiz=Tk()

def AbrirArchivo():
	archivo = filedialog.askopenfilename(title= "Seleccione el mapa", initialdir = "C:/Users/usuario/Desktop", filetypes = ((" Archivos de Texto","*.txt"),(" Archivos de Archivo de valores separados por comas de Microsoft Excel","*.csv"),(" Todos los Archivos","*.*")))
	print(archivo)
	AbrirCSV(archivo)

Button (raiz, text= "Abrir archivo", command = AbrirArchivo).pack()

def AbrirCSV(mapa):
	with open (mapa) as f: 
		reader = csv.reader(f, delimiter=";")
		print (f)
		for row in reader: 
			#for columns in row
				#if 
			print ("Ap paterno: {0}, Ap materno: {1}, Nombre: {2}, Ciudad: {3}".format(row[0], row[1], row[2], row[3]))

raiz.mainloop()