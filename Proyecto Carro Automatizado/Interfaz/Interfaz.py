import csv
from tkinter import *
from tkinter import filedialog

raiz = Tk()
Matriz = [[]]
fila = 0 
columna = 0

def AbrirArchivo():
    archivo = filedialog.askopenfilename(title="Seleccione el mapa", initialdir="C:/Users/usuario/Desktop", filetypes=(
        (" Archivos de Archivo de valores separados por comas de Microsoft Excel", "*.csv"), (" Archivos de Texto", "*.txt"), (" Todos los Archivos", "*.*")))
    AbrirCSV(archivo)

Button(raiz, text="Abrir archivo", command=AbrirArchivo).pack()

def AbrirCSV(mapa):
	with open(mapa) as f:
		reader = csv.reader(f, delimiter=";")
		for row in reader:
			Matriz.append(row)
			print (row)
		mostrarMatriz()

def mostrarMatriz():
	for fila in range (0, len(Matriz)):
		for columna in range (0, len(Matriz[fila])):
			if (Matriz[fila][columna]) == '':
				pass;
			else:
				print ('fila:', fila, 'columna:', columna ,'valor interno:', Matriz[fila][columna])
	for i in range (0, len(Matriz)):
		print ('fila:', i, Matriz[i])


raiz.mainloop()
