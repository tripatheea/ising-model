#include "System.h"

ising::System::System(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta) {
	_current_lattice = ising::Lattice(width, height);
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
	// new_lattice.get_vertex_at(x, y).flip_spin();

	// First, get all vertices.
	std::vector<std::vector<ising::Vertex>> all_vertices = current_lattice.get_vertices();

	// Take this coordinate (x, y) and flip the spin for just that vertex.


	// cout << all_vertices[x][y] << " vs. ";

	// Select the vertex to flip.
	all_vertices[x][y].flip_spin();

	// cout << all_vertices[x][y] << " and ";


	ising::Lattice new_lattice = ising::Lattice(all_vertices);

	// cout << new_lattice.get_vertices()[x][y] << endl;

	new_lattice.calculate_energy();


	return new_lattice;
}

void ising::System::step() {

	float new_energy = 0;
	ising::Lattice current_lattice = ising::Lattice(_current_lattice);
	ising::Lattice new_lattice = new_random_lattice(current_lattice);

	// cout << "Lattice is: " << endl;
	// cout << new_lattice << endl;

	// Sweep width * height times.
	for (unsigned i=0; i < _width * _height; i++) {
	// for (unsigned i=0; i < 0; i++) {

		// First, pick a random element by altering just one vertex of the lattice.
		new_lattice = new_random_lattice(new_lattice);
	}

	// cout << "Final lattice is: " << endl;
	// cout << new_lattice << endl;

	/*
	ising::Vertex a = ising::Vertex(0);
	ising::Vertex b = ising::Vertex(1);
	ising::Vertex c = ising::Vertex(0);
	ising::Vertex d = ising::Vertex(0);

	std::vector<std::vector<ising::Vertex>> all_vertices{{ising::Vertex(a), ising::Vertex(b)}, {ising::Vertex(c), ising::Vertex(d)}};

	cout << endl << all_vertices[0][0] << all_vertices[0][1] << endl << all_vertices[1][0] << all_vertices[1][1] << endl;

	ising::Lattice hey_lattice = ising::Lattice(all_vertices);

	cout << endl << hey_lattice << endl;
	*/
	
	_current_lattice = new_lattice;

	// cout << endl << new_lattice << endl;
	// cout << "New Energy: " << new_energy << endl;

	// cout << "Current lattice is:" << endl;
	// cout << _current_lattice << endl;
}
