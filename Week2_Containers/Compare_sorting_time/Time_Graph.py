import matplotlib.pyplot as plt
import numpy as np


plt.figure(figsize=(10,7))
plt.grid(True)

array, size = np.loadtxt('array.txt', unpack = True)
plt.plot(size, array, label = "array", marker = "o")


deque, size = np.loadtxt('deque.txt', unpack = True)
plt.plot(size, deque, label = "deque", marker = "o")


vector, size = np.loadtxt('vector.txt', unpack = True)
plt.plot(size, vector, label = "vector", marker = "o")

list, size = np.loadtxt('list.txt', unpack = True)
plt.plot(size, list, label = "list", marker = "o")

forward_list, size = np.loadtxt('forward_list.txt', unpack = True)
plt.plot(size, forward_list, label = "forward_list", marker = "o")

plt.legend()
plt.title("Comparison of sorting time")
plt.xlabel(r'$size$', fontsize = 16)
plt.ylabel(r'$time, \: microseconds$', fontsize = 16)


plt.savefig("Compare_time_sort.png")
plt.show()
