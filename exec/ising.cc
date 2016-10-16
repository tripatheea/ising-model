#include <iostream>


// #include "../interface/Vertex.h"
// #include "../interface/Lattice.h"
#include "../interface/System.h"


using namespace std;

int main(int argc, char * argv[]) {

	// Define a new system first. 
	unsigned width = stoi(argv[1]);
	unsigned height = stoi(argv[2]);
	float beta = 1.;
	ising::System sys = ising::System(width, height, beta);

		
	ising::Lattice lat = sys.get_lattice();
		
	cout << endl << "Old lattice with energy = " << lat.get_energy() << " is: " << endl << lat;
	
	sys.step();

	cout << "========================" << endl;

	ising::Lattice new_lattice = sys.get_lattice();

	cout << "New lattice with energy = " << new_lattice.get_energy() << " is: " << endl << new_lattice << endl;


	
	

	return 1;

}
