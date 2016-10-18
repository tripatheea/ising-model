#include <iostream>


// #include "../interface/Vertex.h"
// #include "../interface/Lattice.h"
#include "../interface/System.h"
// #include "python2.7/Python.h"


#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iterator>
#include <iomanip>
#include <limits>
#include <chrono>


using namespace std;

void write_to_file(ising::Lattice lat);

int main(int argc, char * argv[]) {

	// Define a new system first. 
	unsigned width = stoi(argv[1]);
	unsigned height = stoi(argv[2]);
	float beta = 1.;
	ising::System sys = ising::System(width, height, beta);

		
	ising::Lattice lat = sys.get_lattice();

	unsigned max_i = 100;
	for (unsigned i=0; i < max_i; i++) {

		if ((i % (max_i / 10)) == 0)
			cout << "Step #" << (i + 1) << endl;
		
		sys.step();

		write_to_file(sys.get_lattice());

		stringstream plotting_command;
		plotting_command << "python plots/plot.py " << width << " " << height << " " << i << " " << fixed << setprecision(2) << sys.get_lattice().get_energy();

		// cout << plotting_command << endl;
		system( plotting_command.str().c_str() );
	}

	// system("convert -delay 40 -loop 0 plots/*.png plots/animation.gif");
	system("ffmpeg -start_number 0 -framerate 25  -r 4 -y -i plots/lattice/%d.png -vcodec mpeg4 plots/lattice/animation.avi");
	// The -r 3 option sets the framerate of the resulting video to 3 frames per second so that I can see each still for a short period of time.

	
	

	return 1;

}


void write_to_file(ising::Lattice lat) {
	ofstream output_file("lattice.dat", ios::out);


	std::vector<std::vector<ising::Vertex> > vertices = lat.get_vertices();

	for (unsigned x=0; x < vertices.size(); x++) {
		for (unsigned y=0; y < vertices[x].size(); y++) {
			output_file << showpos << to_string(vertices[x][y].get_spin()) + "\t";
		}
		output_file << "\n";
	}

}