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
serial_number = int(sys.argv[3])
energy = float(sys.argv[4])



def parse_file():
	lattice = []
	with open("data/lattice.dat") as f:
		lines = f.readlines()
		
		for line in lines:
			row = []
			for vertex in line.strip().split("\t"):
				row.append(int(vertex))
			lattice.append(row)

	return lattice

def plot():
	lattice = parse_file()

	

	# plt.imshow(lattice, origin='upper', extent=[0, width - 1, 0, height - 1])
	im = plt.imshow(lattice, origin='upper', extent=[0, width - 1, 0, height - 1], cmap='Blues')

	cb = plt.colorbar(im)

	plt.xlim(0, width - 1)
	plt.ylim(0, height - 1)

	plt.xlabel("x")
	plt.ylabel("y", rotation=0)

	label = []
	extra = Rectangle((0, 0), 1, 1, fc="w", fill=False, edgecolor='none', linewidth=0)
	label.extend( ["{} x {}".format(width, height)] ) 
	additional_legend = plt.gca().legend( [extra] * len(label), label, frameon=0, borderpad=0, fontsize=20, bbox_transform = plt.gcf().transFigure, bbox_to_anchor=[0.1, 0.98], loc="upper left")	
	plt.gca().add_artist(additional_legend)



	label = []
	label.extend( ["N = {}; E = {}".format(serial_number, energy)] ) 
	additional_legend = plt.gca().legend( [extra] * len(label), label, frameon=0, borderpad=0, fontsize=20, bbox_transform = plt.gcf().transFigure, bbox_to_anchor=[0.83, 0.98], loc="upper right")	
	plt.gca().add_artist(additional_legend)


	plt.savefig("plots/lattice/" + str(serial_number) + ".png")



plot()