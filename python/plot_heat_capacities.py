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

	plt.plot(beta_s, heat_capacities, lw=3, color="red")	

	plt.autoscale()

	plt.xlabel("B")
	plt.ylabel("C", rotation=0)

	plt.title("Heat capacity for a {} x {} lattice".format(width, height))

	# plt.savefig("plots/" + str(serial_number) + ".png")
	plt.savefig("plots/heat_capacity.png")



plot()