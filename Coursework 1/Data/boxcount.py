import matplotlib.pyplot as plt
import numpy as np
import subprocess
import pandas as pd
import time

class DLA():
    def __init__(self, n=3000, steps=25000, p=1.0):
        self.number_of_walkers = n
        self.number_of_steps = steps
        self.sticking_probability = p

        start_time = time.time()
        process = subprocess.Popen(["../DLA-Single/cmake-build-debug/DLA-Single",
                                    "-v",
                                    "-n", str(self.number_of_walkers),
                                    "-s", str(self.number_of_steps),
                                    "-p", str(self.sticking_probability)],
                                   stdout=subprocess.PIPE)
        output = process.stdout.read().split()
        self.time = time.time() - start_time
        data = np.loadtxt(output, delimiter=',', skiprows=1)
        self.data = pd.DataFrame(data, columns=["x", "y", "z", "state", "r", "n"]).sort_values(by="n")
        self.data["r"] = self.data["r"] - min(self.data["r"])
        print(f"Simulation generated in {self.time:.2f} seconds")

    def boxcount(self, N, visual_output=False):
        # filter = self.data["state"] == 1

        x = self.data["x"]
        y = self.data["y"]

        # x = self.data["x"][filter]
        # y = self.data["y"][filter]

        # Minimum and maximums
        xmax = max(x) + 0.00001
        xmin = min(x) - 0.00001
        ymax = max(y) + 0.00001
        ymin = min(y) - 0.00001

        # Generate range
        xrange = xmax - xmin
        yrange = ymax - ymin
        self.xrange = xrange

        w = xrange / N  # width of boxes
        m = int(np.ceil(yrange / w))  # number of y boxes
        boxoccupancy = np.zeros([N, m])  # empty array of box occupancies

        # Find the occupied boxes
        for i, _ in enumerate(x):
            ix = int(np.trunc((x[i] - xmin) / w))
            iy = int(np.trunc((y[i] - ymin) / w))
            boxoccupancy[ix, iy] = 1

        if visual_output:
            plt.figure()
            plt.scatter(x, y, 1)
            plt.imshow(np.flip(boxoccupancy.T, 0), extent=[xmin, xmax, ymin, ymax])
            plt.show()

        # Return number of occupied boxes
        return np.sum(boxoccupancy)

    def boxcount_dimension(self, start=1, stop=30, step=5, visual_output=False):
        fractal_data = [[], []]

        for n in range(start, stop, step):
            fractal_data[1].append(self.boxcount(n))
            fractal_data[0].append(self.xrange / n)


        [m, c], cov = np.polyfit(np.log(fractal_data[0]), np.log(fractal_data[1]), 1, cov=True)

        if visual_output:

            x = np.array(np.log(fractal_data[0]))
            y = m * x + c

            plt.scatter(np.log(fractal_data[0]), np.log(fractal_data[1]))
            plt.plot(x, y, color="red")

        self.fractal_data = fractal_data

        return [-m, np.sqrt(cov[0,0])]

    def radial_dimension(self, start=5,  step=5, plot=False):
        n = []
        r_max = []
        for i in range(start+step, len(self.data.index), step):
            partial_data = self.data["r"].iloc[start:i]
            n.append(i)
            r_max.append(max(partial_data))

        self.radial_data = [n, r_max]

        if plot:
            plt.scatter(n, r_max, label=f"p={self.sticking_probability}")
            plt.xlabel("Number")
            plt.ylabel("Maximum Custer Radius")

        [m, c], cov = np.polyfit(np.log(r_max), np.log(n), 1, cov=True)
        return [m, cov[0,0]]


def box_count(datafile, N, visual_output=False):
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

def fractal_dimension(datafile, start, stop, step, visual_output=False, boxcount_visual=False):
    data = [[], []]

    for n in range(start, stop, step):
        data[0].append(1 / n)
        data[1].append(box_count(datafile, n, boxcount_visual))

    [m, c] = np.polyfit(np.log(data[0]), np.log(data[1]), 1)

    if visual_output:
        # calculate_fractal_dimension(datafile, 1, 100, 10, visual_output=True, boxcount_visual=False)

        x = np.array(np.log(data[0]))
        y = m * x + c

        plt.figure()
        plt.scatter(np.log(data[0]), np.log(data[1]))
        plt.plot(x, y, color="red")
        plt.show()

    return -m
