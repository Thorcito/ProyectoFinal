import csv
from tkinter import *
from tkinter import filedialog

raiz = Tk()
Matriz = [[]]
 

#Función que permite la búsqueda del archivo csv que contiene el mapa a ejecutar
def AbrirArchivo():
    archivo = filedialog.askopenfilename(title="Seleccione el mapa", initialdir="C:/Users/usuario/Desktop", filetypes=(
        (" Archivos de Archivo de valores separados por comas de Microsoft Excel", "*.csv"), (" Archivos de Texto", "*.txt"), (" Todos los Archivos", "*.*")))
    raiz.destroy()
    AbrirCSV(archivo)
Button(raiz, text="Abrir archivo", command=AbrirArchivo).pack()

#Función que convierte los valores del cvs en una matriz
def AbrirCSV(mapa):
	with open(mapa) as f:
		reader = csv.reader(f, delimiter=";")
		for row in reader:
			Matriz.append(row)
		print ("Se cerro la interfaz") 
	mostrarMatriz()
		

#Función auxiliar de AbrirCSV
def mostrarMatriz():
	#for fila in range (0, len(Matriz)):
	#	for columna in range (0, len(Matriz[fila])):
	#		sacarElementos(fila, columna)
			
	for i in range (0, len(Matriz)):
		print ('fila:', i, Matriz[i])

def sacarElementos(fila):
	#print (Matriz[fila][columna])
	return (Matriz[fila])
	

raiz.mainloop()
