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
	temp_s = []
	energies = []
	with open("data/energy.dat") as f:
		lines = f.readlines()
		
		for line in lines:
			row = []
			blocks = line.strip().split("\t")
			
			temp_s.append(float(blocks[0]))
			energies.append(float(blocks[1]))

	return (temp_s, energies)


def plot():
	temp_s, energies = parse_file()

	plt.plot(temp_s, energies, lw=0, color="red", marker='+', markersize=40, pickradius=30, alpha=1.0)	

	plt.autoscale()

	plt.gca().set_ylim( plt.gca().get_ylim()[0] * 1.25, plt.gca().get_ylim()[1] )

	plt.xlabel("Temperature (T)", fontsize=55, labelpad=25)
	plt.ylabel("Internal Energy $(U)$", fontsize=55)

	plt.tick_params(which='major', width=5, length=25, labelsize=50)
	plt.tick_params(which='minor', width=3, length=15)

	plt.title("Internal Energy of a {} x {} lattice with {} steps".format(width, height, N))


	plt.gcf().set_size_inches(30, 24, forward=1)

	# plt.savefig("plots/" + str(serial_number) + ".png")
	plt.savefig("plots/energy.pdf")
	# plt.show()


plot()