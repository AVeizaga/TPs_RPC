#Script sencillo para graficar el resultado de las splines.

import numpy as np
import matplotlib.pyplot as plt

#Ejes para el grafico
x = []
y = []

#Archivo
f = open('salida.txt', 'r')

#Recorrido del archivo
count = 0
for line in f:
    if(count%2 == 0):
        x.append(float(line))
    else:
        y.append(float(line))
    count = count + 1

#print(x)
#print(y)


#Grafico
plt.figure()
plt.plot(x, y)
plt.show()