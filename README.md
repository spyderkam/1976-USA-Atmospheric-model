# 1976 U.S. Standard Atmosphere Model Implementation

A Python implementation of the 1976 U.S. Standard Atmosphere model for calculating atmospheric properties (temperature, pressure, density) and drag forces at different altitudes.

## Overview

This implementation:
- Calculates temperature as a function of geopotential altitude using a fitted 4th-degree polynomial
- Computes atmospheric pressure via numerical integration
- Determines air density using the ideal gas law
- Calculates drag forces on objects at various altitudes
- Valid for altitudes between -1,524 m and 76,200 m

## Features

- Temperature calculation using fitted polynomial model
- Pressure calculation using numerical integration
- Density computation from ideal gas law
- Drag force calculations
- Supports Earth-Centered Earth-Fixed (ECEF) coordinates

## Installation

1. Clone this repository:
```bash
git clone [repository-url]
```

2. Required dependencies:
```bash
pip install numpy scipy matplotlib
```

## Usage

### Basic Usage
```python
from main import Atmosphere

# Create atmosphere model instance
atm_model = Atmosphere()

# Calculate properties at a given altitude (in meters)
h = 10000
temperature = atm_model.T(h)
pressure = atm_model.P(h)
density = atm_model.ρ(h)

# Calculate drag force
drag_force = atm_model.drag_force(
    Cd=1,           # drag coefficient
    A=100,          # cross-sectional area (m²)
    vh=20,          # vertical velocity (m/s)
    vx=100,         # x velocity (m/s)
    vy=3000,        # y velocity (m/s)
    h=10000         # altitude (m)
)
```

## Model Details

### Atmosphere Class
The main class implementing the atmospheric model.

#### Parameters
- `h0` (float): Geopotential altitude at sea level (-1,524 m default)
- `P0` (float): Pressure at sea level (101,325 Pa default)
- `R` (float): Specific gas constant for dry air (287.052874 J/(kg⋅K) default)

#### Methods
- `T(h)`: Calculate temperature at given altitude
- `P(h)`: Calculate pressure at given altitude
- `ρ(h)`: Calculate density at given altitude
- `drag_force(Cd, A, vh, vx, vy, h)`: Calculate drag force

## Physical Model

The implementation is based on three key equations:

1. Vertical pressure variation:
```
dP/dh = -ρg
```

2. Ideal gas law:
```
P = ρRT
```

3. Drag force:
```
Fd = (1/2)ρv²CdA
```

Where:
- P is pressure
- ρ is density
- g is gravitational acceleration (-9.81 m/s²)
- R is the specific gas constant for dry air
- T is temperature
- v is velocity
- Cd is drag coefficient
- A is cross-sectional area

## Limitations

- Valid only for altitudes between -1,524 m and 76,200 m
- Uses constant gravitational acceleration (g = -9.81 m/s²)
- Temperature model uses polynomial fit which may not have physical meaning
- Only considers dry air

## Contributing

Feel free to open issues or submit pull requests for:
- Bug fixes
- Documentation improvements
- Model enhancements
- Additional features

## License

[MIT License](https://github.com/spyderkam/1976-USA-Atmosphere/blob/main/LICENSE)

Copyright (c) 2024 Kamyar Modjtahedzadeh

This code was developed to implement the 1976 U.S. Standard Atmosphere model.

## References

1. U.S. Standard Atmosphere, 1976 (NOAA/NASA/USAF)
2. The Engineering ToolBox - Standard Atmosphere properties
3. Public Domain Aeronautical Software - Geopotential & Geometric Altitude
