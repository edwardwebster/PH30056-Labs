#!/usr/bin/env python
# coding: utf-8

# # Data Analysis for DLA

# ## Section 1
# This method to evaluate the fractal dimension uses the fact that
# 
# $N = \frac{R}{a}^d$
# 
# so $\ln(N)=d\ln(R/a)+c$ hence the gradient of $\ln(N)$ against $\ln(R)$ is the fractal dimension $d$.

# In[1]:


import numpy as np

file = "dla.csv"

number_of_particles, radius = np.loadtxt(file, unpack=True, delimiter=",")


# In[2]:


import matplotlib.pyplot as plt

plt.scatter(np.log(radius), np.log(number_of_particles))
plt.xlabel("radius")
plt.ylabel("number of particles")
[m, c], cov = np.polyfit(np.log(radius), np.log(number_of_particles), 1, cov=True)

x = np.linspace(min(np.log(radius)), max(np.log(radius)), 10)
y = m*x + c
plt.plot(x, y, color="red")

print(f"fractal dimension: {m:.4f} ± {cov[1,1]:.4f}")


# ## Section 2
# The fractal dimension here is calculated using box counting

# In[3]:


from boxcount import *

