#Script sencillo para graficar el resultado de las splines.

import numpy as np
import matplotlib.pyplot as plt

import sys

if(len(sys.argv) > 1):
    file_name = sys.argv[1]
else:
    file_name = "salida.txt"

#Ejes para el grafico
x = []
y = []


#Recorrido del archivo
with open(file_name, 'r') as file:
    for line in file:
        val = line.strip().split(',')
        x.append(float(val[0]))
        y.append(float(val[1]))


#Grafico
plt.plot(x, y)
plt.savefig('grafico.png')