#Seguimiento de ruta
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

#Funcion que ejecuta el seguimiento de ruta
#def seguimiento_ruta(excel.csv)
        
