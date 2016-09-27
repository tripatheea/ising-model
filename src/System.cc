#include "System.h"

ising::System::System(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta), _current_lattice(Lattice(width, height)) {
	
}

ising::Lattice ising::System::get_lattice() {
	return _current_lattice;
}

ising::Lattice ising::System::new_random_lattice(ising::Lattice current_lattice) {
	// TODO: Maybe accept a parameter about how to select a new lattice.

	unsigned lattice_width = current_lattice.get_width();
	unsigned lattice_height = current_lattice.get_height();

	// Select a random x and y.
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> x_dist(0, (lattice_width - 1)); // distribution in range [0, width - 1]

	int x = x_dist(rng);

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> y_dist(0, (lattice_height - 1)); // distribution in range [0, height - 1]

	int y = y_dist(rng);

	// Take this coordinate (x, y) and flip the spin for just that vertex.
	current_lattice.get_vertex_at(x, y).flip_spin();

	return  current_lattice;

}

void ising::System::step() {
	// First, pick a random element by altering just one vertex of the lattice.
	ising::Lattice new_lattice = new_random_lattice(_current_lattice);
}