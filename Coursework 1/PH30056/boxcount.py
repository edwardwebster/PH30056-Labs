import matplotlib.pyplot as plt
import numpy as np

def boxcount(datafile, N, visual_output=False):
    # Load CSV Data
    data = np.loadtxt(datafile, delimiter=',', unpack=True, usecols=[0, 1, 3], skiprows=1)

    # Filter only cluster points
    filter = data[2] == 1

    # Get x & y values
    x = data[0][filter]
    y = data[1][filter]

    # Minimum and maximums
    xmax = max(x) + 0.00001
    xmin = min(x) - 0.00001
    ymax = max(y) + 0.00001
    ymin = min(y) - 0.00001

    # Generate range
    xrange = xmax - xmin
    yrange = ymax - ymin

    w = xrange / N  # width of boxes
    m = int(np.ceil(yrange / w))  # number of y boxes
    boxoccupancy = np.zeros([N, m])  # empty array of box occupancies

    # Find the occupied boxes
    for i, _ in enumerate(x):
        ix = int(np.trunc((x[i] - xmin) / w))
        iy = int(np.trunc((y[i] - ymin) / w))
        boxoccupancy[ix, iy] = 1

    # plot if required
    if visual_output:
        plt.figure()
        plt.scatter(x, y)
        plt.imshow(np.flip(boxoccupancy.T, 0), extent=[xmin, xmax, ymin, ymax])
        plt.show()

    # Return number of occupied boxes
    return np.sum(boxoccupancy)


# print(boxcount("output.csv.67", 60, rich_output=True))

def calculate_fractal_dimension(datafile, start, stop, step, visual_output=False):
    data = [[], []]

    for n in range(start, stop, step):
        data[0].append(1 / n)
        data[1].append(boxcount(datafile, n, visual_output))

    [m, c] = np.polyfit(np.log(data[0]), np.log(data[1]), 1)

    if visual_output:
        x = np.array(np.log(data[0]))
        y = m * x + c

        plt.figure()
        plt.scatter(np.log(data[0]), np.log(data[1]))
        plt.plot(x, y, color="red")
        plt.show()

    return -m

#print(calculate_fractal_dimension("output.csv.67", 10, 40, 3))
