#include <iostream>


// #include "../interface/Vertex.h"
// #include "../interface/Lattice.h"
#include "../interface/System.h"


using namespace std;

int main() {

	// Define a new system first. 
	unsigned width = 50;
	unsigned height = 50;
	float beta = 1.;
	ising::System sys = ising::System(width, height, beta);

		
	ising::Lattice lat = sys.get_lattice();
	
	cout << lat << endl;

	cout << endl << endl << "========================" << endl << endl;
	cout << "Energy: " << lat.get_energy() << endl;


	sys.step();
	

	return 1;

}
