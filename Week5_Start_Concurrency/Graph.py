import matplotlib.pyplot as plt
import numpy as np


plt.figure(figsize=(10,7))
plt.grid(True)

amount_workers, time = np.loadtxt('Time.txt', unpack = True)
plt.plot(amount_workers, time, color = "pink")


plt.legend()
plt.title("Compare times")
plt.xlabel('amount tread', fontsize = 16)
plt.ylabel(r'$time, \: microseconds$', fontsize = 16)


plt.savefig("Compare_time.png")
plt.show()
