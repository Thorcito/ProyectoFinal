import csv

with open ('personas.csv') as f: 
	reader = csv.reader(f, delimiter=";")
	print (f)
	for row in reader: 
		#for columns in row
			#if 
		print ("Ap paterno: {0}, Ap materno: {1}, Nombre: {2}, Ciudad: {3}".format(row[0], row[1], row[2], row[3]))