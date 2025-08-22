import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

file = np.genfromtxt("U.S. Standard Atmosphere Air Properties - Imperial (BG) Units.txt", skip_header=2)

h = file[:, 0]*0.3048             # converting ft to m
T = (file[:, 1] + 459.67)*(5/9)   # converting F to K


def temp_curve(x, a, b, c, d, e): return a*x**4 + b*x**3 + c*x**2 + d*x + e
# Obviously such a polynomial is not good math but get the ball rolling.


plt.scatter(h, T, label='data', color='blue')
popt, pcov = curve_fit(temp_curve, h, T)
plt.plot(h, temp_curve(h, *popt), 'r--', label=r'fit: $ah^4 + bh^3 + ch^2 + dh + e$')


## Generating a nicer curve.
#TT = np.linspace(h[0], h[-1], 500)
#τ = lambda h : 0.000000000000000027*h**4 - 0.000000000006074933*h**3 + 0.000000422889669793*h**2 - 0.009918936624872612*h + 289.661267963331567898
#plt.plot(TT, τ(TT), 'r--', label=r'fit: $ah^4 + bh^3 + ch^2 + dh + e$')


plt.legend()
plt.ylabel(r"$T(h)$", fontsize=25)
plt.xlabel(r"$h$", fontsize=25)

plt.tight_layout()
plt.show()


print('   a =', '%0.18f' % popt[0])
print('   b =', "%0.18f" % popt[1])
print('   c =', "%0.18f" % popt[2])
print('   d =', '%0.18f' % popt[3])
print('   e =', "%0.18f" % popt[4])


"""
CONCLUSTION: 
  if -1524 meter ≤ 𝘩 ≤ 76200 ⇒ 𝘛(𝘩) = 0.000000000000000027𝘩^4 - 0.000000000006074933𝘩^3 + 0.000000422889669793𝘩^2 - 0.009918936624872612𝘩 + 289.661267963331567898
"""

