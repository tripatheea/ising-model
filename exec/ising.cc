#include <iostream>
#include "../interface/Vertex.h"
#include "../interface/Lattice.h"

using namespace std;
using namespace ising;

int main() {
	Lattice lat = Lattice(10, 10, 1.);
	
	cout << lat << endl;

	return 1;
}
