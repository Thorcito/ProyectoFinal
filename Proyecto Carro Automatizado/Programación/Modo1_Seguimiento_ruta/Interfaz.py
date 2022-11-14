import csv
from tkinter import *
from tkinter import filedialog

#se definen las variables con las que se va a trabajar
raiz = Tk()
Matriz = [[]]
fila = 0 
columna = 0
casilla = 0


#Función que permite la búsqueda del archivo csv que contiene el mapa a ejecutar
def AbrirArchivo():
    archivo = filedialog.askopenfilename(title="Seleccione el mapa", initialdir="C:/Users/usuario/Desktop", filetypes=(
        (" Archivos de Archivo de valores separados por comas de Microsoft Excel", "*.csv"), (" Archivos de Texto", "*.txt"), (" Todos los Archivos", "*.*")))
    raiz.destroy()
    AbrirCSV(archivo)
Button(raiz, text="Abrir archivo", command=AbrirArchivo).pack()

#Función que el cvs y lo traslada a una matriz
def AbrirCSV(mapa):
    with open(mapa) as f:
        reader = csv.reader(f, delimiter=";")
        for row in reader:
            Matriz.append(row)
            print (row)
        encontrarInicio()

    with open(mapa) as f:
        reader = csv.reader(f, delimiter=";")
        for row in reader:
            Matriz.append(row)
            print ("Se cerro la interfaz") 
    mostrarMatriz()
		

#Función que permite desplegar los valores que se leyeron
def mostrarMatriz():
    for fila in range (0, len(Matriz)):
        for columna in range (0, len(Matriz[fila])):
            if (Matriz[fila][columna]) == '':
                pass;
            else:
                print ('fila:', fila, 'columna:', columna ,'valor interno:', Matriz[fila][columna])
                casilla = Matriz[fila][columna]
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
            for columna in range(0, len(Matriz[fila])):
                if (Matriz[fila][columna]) >= '90':
                        print ('El incio del recorrido es en la:', 'fila', fila, 'columna', columna)
	#for fila in range (0, len(Matriz)):
	#	for columna in range (0, len(Matriz[fila])):
	#		sacarElementos(fila, columna)
			
    for i in range (0, len(Matriz)):
        print ('fila:', i, Matriz[i])

#Función que permite extraer los valores de la matriz
def sacarElementos(fila):
	#print (Matriz[fila][columna])
	return (Matriz[fila])
	

raiz.mainloop()
