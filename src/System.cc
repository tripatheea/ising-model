#include "System.h"

ising::System::System(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta), _current_lattice(ising::Lattice(width, height)) {
}

ising::Lattice ising::System::get_lattice() {
	return _current_lattice;
}

ising::Lattice ising::System::new_random_lattice(ising::Lattice current_lattice) {
	// TODO: Maybe accept a parameter about how to select a new lattice.

	int lattice_width = current_lattice.get_width();
	int lattice_height = current_lattice.get_height();

	// Select a random x and y.
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> x_dist(0, (lattice_width - 1)); // distribution in range [0, width - 1]

	int x = x_dist(rng);

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> y_dist(0, (lattice_height - 1)); // distribution in range [0, height - 1]

	int y = y_dist(rng);

	// Take this coordinate (x, y) and flip the spin for just that vertex.
	//cout << "Flipping x = " << x << " y = " << y << endl;
	current_lattice.get_vertex_at(x, y).flip_spin();

	return  current_lattice;

}

void ising::System::step() {

	float new_energy = 0;
	ising::Lattice new_lattice = new_random_lattice(_current_lattice);

	// Sweep width * height times.
	for (unsigned i=0; i < _width * _height; i++) {

		// First, pick a random element by altering just one vertex of the lattice.
		new_lattice = new_random_lattice(new_lattice);
	
		// Next, calculate the energy for this new lattice.
		new_energy = new_lattice.get_energy();

		//cout << new_lattice << endl;
		cout << new_energy << ", ";
	}

	cout << endl << new_lattice << endl;
	cout << "New Energy: " << new_energy << endl;
}
