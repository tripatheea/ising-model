from __future__ import division




import sys


# matplotlib
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import matplotlib.patches as mpatches
from matplotlib.legend_handler import HandlerLine2D
from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm


width = int(sys.argv[1])
height = int(sys.argv[2])
N = int(sys.argv[3])


mpl.rcParams['axes.linewidth'] = 5.0 #set the value globally
mpl.rcParams['text.usetex'] = True
mpl.rcParams['text.latex.preamble']=[r"\usepackage{amsmath}"]
mpl.rcParams['text.latex.preamble'] = [r'\boldmath']

plt.rc('font', family='serif', size=43)

def parse_file():
	beta_s = []
	heat_capacities = []
	with open("data/heat_capacities.dat") as f:
		lines = f.readlines()
		
		for line in lines:
			row = []
			blocks = line.strip().split("\t")
			
			beta_s.append(float(blocks[0]))
			heat_capacities.append(float(blocks[1]))

	return (beta_s, heat_capacities)


def plot():
	beta_s, heat_capacities = parse_file()

	plt.plot(beta_s, heat_capacities, lw=0, color="red", marker='+', markersize=25, pickradius=15, alpha=1.0)

	plt.xlabel("Temperature", fontsize=55, labelpad=25)
	plt.ylabel("Heat Capacity $(C)$", fontsize=55)

	plt.tick_params(which='major', width=5, length=25, labelsize=50)
	plt.tick_params(which='minor', width=3, length=15)

	plt.title("Heat Capacity for a {} x {} lattice with {} steps.".format(width, height, N))

	plt.gcf().set_size_inches(30, 24, forward=1)

	plt.savefig("plots/heat_capacity.pdf")


plot()