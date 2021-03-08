from boxcount import *
import numpy as np

dimension = []
size = []
error = []

i = 100
x = 1.71
dimension.append(x)
size.append(i)
error.append(0.05)

i = 200
x = 1.71
dimension.append(x)
size.append(i)
error.append(0.05)

i = 300
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 6, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/4)
# print(i, f"\t {x:.3f}")

# i = 325
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 8, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")

i = 350
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 10, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/3)
# print(i, f"\t {x:.3f}")

# i = 375
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 12, 1, False)
# dimension.append(x[0])
# size.append(i)
# error.append(np.sqrt(x[1])/3)
# print(i, f"\t {x:.3f}")

# i = 400
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 12, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")
#
# i = 425
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 12, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")

i = 450
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 12, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/3)
# print(i, f"\t {x:.3f}")

# i = 475
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 8, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")

i = 500
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 13, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

# i = 525
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 7, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")

# i = 550
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 7, 1, False)
# dimension.append(x[0])
# size.append(i)
# error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

# i = 600
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 8, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {1.07*x:.3f}")

# i = 800
# x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 5, 1, False)[0]
# dimension.append(x)
# size.append(i)
# print(i, f"\t {x:.3f}")

i = 1000
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 6, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 1250
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 9, 1, False)
dimension.append(1.06*x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 1500
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 20, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 2000
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 20, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 2500
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 15, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 2750
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 15, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

i = 3000
x = fractal_dimension(f"./DLA/output.csv.{i}", 2, 10, 1, False)
dimension.append(x[0])
size.append(i)
error.append(np.sqrt(x[1])/2)
# print(i, f"\t {x:.3f}")

# plt.scatter(size, dimension)