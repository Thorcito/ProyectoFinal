import csv
from tkinter import *
from tkinter import filedialog

raiz = Tk()


def AbrirArchivo():
    archivo = filedialog.askopenfilename(title="Seleccione el mapa", initialdir="C:/Users/usuario/Desktop", filetypes=(
        (" Archivos de Archivo de valores separados por comas de Microsoft Excel", "*.csv"), (" Archivos de Texto", "*.txt"), (" Todos los Archivos", "*.*")))
    print(archivo)
    AbrirCSV(archivo)


Button(raiz, text="Abrir archivo", command=AbrirArchivo).pack()


def AbrirCSV(mapa):
    with open(mapa) as f:
        reader = csv.reader(f, delimiter=";")
        print(f)
        for row in reader:
            # for columns in row
            # if
            print("{0}, {1}, {2}, {3}, {4}".format(
                row[0], row[1], row[2], row[3], row[4]))


raiz.mainloop()
