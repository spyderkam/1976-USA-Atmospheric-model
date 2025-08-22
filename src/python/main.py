#!/usr/bin/env python3

import scipy.integrate as integrate
import numpy as np

g = -9.81     # This varies for altitude but will be assumed constant here.

class Atmosphere:
    """1976 standard atmosphere model"""

    def __init__(self, h0=-1524, P0=101325, R=287.052874):
        self.R = R       # specific gas constant for dry air (default units: [J/(kg*K)])
        self.h0 = h0     # geopotential altitude at sea level (boudary condition)
        self.P0 = P0     # pressure at sea level (boudary condition)

    def T(self, h):      # See "find_T_vs_h_curve.py" for how this expresssion was obtained.
        return 0.000000000000000027*h**4 - 0.000000000006074933*h**3 + 0.000000422889669793*h**2 - 0.009918936624872612*h + 289.661267963331567898

    def P(self, h):      # h is geopotential altitude
        return self.P0*np.exp( (g/self.R)*integrate.quad(lambda h: 1/T(h), self.h0, h)[0] )

    def ρ(self, h):      # density
        return P(h)/(self.R*T(h))
   
    def drag_force(self, Cd, A, vh, vx, vy, h, x=0, y=0):     # Cd is drag coefficient and A is cross-sectional area
        return 0.5*ρ(h)*np.square([vx, vy, vh])*Cd*A

if __name__ == '__main__':
    atm_model = Atmosphere()
    T = atm_model.T
    P = atm_model.P
    ρ = atm_model.ρ

    hmax = 76200
    h = 10000

    print(f"For h = {h}, T = {T(h)}, P = {P(h)}, and ρ = {ρ(h)}.\n")
    
    z = h; m = 100
    Fd = atm_model.drag_force(Cd=1, A=100, vh=20, vx=100, vy=3000, h=z)
    print(f"The drag force at altitude {z} is {Fd} and so with a mass of {m} its acceleration is {np.linalg.norm(Fd)/m}.")
