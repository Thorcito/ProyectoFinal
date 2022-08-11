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

#Funcion auxiliar para detectar el color de la casilla
def detectar_color(valor_casilla_excel_read):
        if type(valor_casilla_excel_read) == int:
                color = 0;
                if ((valor_casilla_excel_read//10)==1):
                        color = "verde";
                        return color
                elif ((valor_casilla_excel_read//10)==2):
                        color = "rojo";
                        return color
                elif ((valor_casilla_excel_read//10)==3):
                        color = "gris";
                        return color
                elif ((valor_casilla_excel_read//10)==4):
                        color = "morado";
                        return color
                elif ((valor_casilla_excel_read//10)==9):
                        color = "azul";
                        return color
                else:
                        return "color no detectado"
        else:
                return "valor casilla no es int"

#Funcion auxiliar para detectar la direccion de los pasos segun el valor de la casilla
def direccion_pasos(valor_casilla_excel_read):
        if type(valor_casilla_excel_read) == int:
                direccion = 0;
                if ((valor_casilla_excel_read%10)==0):
                        direccion = "arriba";
                        return direccion
                elif ((valor_casilla_excel_read%10)==1):
                        direccion = "derecha";
                        return direccion
                elif ((valor_casilla_excel_read%10)==2):
                        direccion = "izquierda";
                        return direccion
                elif ((valor_casilla_excel_read%10)==3):
                        direccion = "abajo";
                        return direccion
                else:
                        return "dirección no detectada"
        else:
                return "valor casilla no es un int"

def encontrarInicio():
	for fila in range (0, len(Matriz)):
			if (Matriz[fila][columna]) >= int('90'):
				print ('El incio del recorrido es en la:', 'fila', fila, 'columna', columna)

raiz.mainloop()
