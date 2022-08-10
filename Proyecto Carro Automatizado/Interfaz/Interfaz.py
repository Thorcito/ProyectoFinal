import csv
import pandas as panda
from tkinter import *
from tkinter import filedialog

raiz = Tk()
Matriz = [[]]
fila = 0 
columna = 0

def AbrirArchivo():
    archivo = filedialog.askopenfilename(title="Seleccione el mapa", initialdir="C:/Users/usuario/Desktop", filetypes=(
        (" Archivos de Archivo de valores separados por comas de Microsoft Excel", "*.csv"), (" Archivos de Texto", "*.txt"), (" Todos los Archivos", "*.*")))
    #print("El mapa que se esta utilizando es: ", archivo)
    AbrirCSV(archivo)

Button(raiz, text="Abrir archivo", command=AbrirArchivo).pack()

def AbrirCSV(mapa):
	with open(mapa) as f:
		reader = csv.reader(f, delimiter=";")
		for row in reader:
			Matriz.append(row)
			print (row)
			#print("{0}, {1}, {2}, {3}, {4}".format(row[0], row[1], row[2], row[3], row[4]))
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
