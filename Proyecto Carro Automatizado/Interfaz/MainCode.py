from Interfaz import *

Matriz_trabajo = [[]]
fila = 0 
columna = 0

#Inicio del código se pide un mapa através de un CSV y la función main
def __main__():
    extraerMatriz()
    #deteccionSTRtoINT() 
    encontrarInicio()

#Función auxiliar de AbrirCSV
def extraerMatriz():
    for fila in range (1, 6):
        nuevo_valor = sacarElementos(fila)
        Matriz_trabajo.append(nuevo_valor)
    print ('traslado de matriz completado')
    for fila in range (0, len(Matriz_trabajo)):
        print ('fila: ', fila, 'valor:', Matriz_trabajo[fila])


def deteccionSTRtoINT():
    for fila in range (0, len(Matriz_trabajo)):
        for columna in range (0, len(Matriz_trabajo[fila])):
            if (Matriz_trabajo[fila][columna]) == '':
                pass;
            else:
                valorAconvetir=int(Matriz_trabajo[fila][columna])
                print(type(valorAconvetir))
                print(valorAconvetir)
                
                print(detectar_color(valorAconvetir))
                print(direccion_pasos(valorAconvetir))

def encontrarInicio():
    for fila in range (0, len(Matriz_trabajo)):
        for columna in range(0, len(Matriz_trabajo[fila])):
            if (Matriz_trabajo[fila][columna]) >= '90':
                print ('El inicio del recorrido es en la:', 'fila', fila, 'columna', columna)

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

__main__()