#include <iostream>


// #include "../interface/Vertex.h"
// #include "../interface/Lattice.h"
#include "../interface/System.h"


using namespace std;
using namespace ising;

int main() {

	// Define a new system first. 
	System sys = System(10, 10, 1.);
	Lattice lat = sys.get_lattice();

	cout << lat << endl;

	cout << endl << endl << "========================" << endl << endl;
	cout << "Energy: " << lat.get_energy() << endl;


	sys.step();
	
	return 1;

}
