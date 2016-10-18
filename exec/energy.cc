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

void write_energies(ofstream & output_file, float beta, float energy);
void write_heat_capacities(ofstream & output_file, vector<float> all_heat_capacities, vector<float> all_betas);
void mc_update_system(ising::System & sys, int iteration);
void write_lattice(ofstream & output_file, ising::Lattice lat);

void calculate_heat_capacities(vector<float> & all_heat_capacities, vector<float> & all_betas, vector<float> & all_energies);

int main(int argc, char * argv[]) {

	// Define a new system first. 
	unsigned width = stoi(argv[1]);
	unsigned height = stoi(argv[2]);
	unsigned steps = stoi(argv[3]);

	vector<float> all_betas;
	vector<float> all_energies;

	ofstream output_file("data/energy.dat", ios::out);


	float beta = 1.0;
	float energy;
	for (unsigned i=0; beta < 3.0; i++) {

		cout << "Working with beta = " << beta << endl;

		ising::System sys = ising::System(width, height, beta);
		mc_update_system(sys, steps);
		
		ofstream lattice_output(("data/lattice/5x5_1M/" + to_string(i) + ".dat").c_str());
		write_lattice(lattice_output, sys.get_lattice());


		energy = sys.get_lattice().get_energy();
		
		all_betas.push_back(beta);
		all_energies.push_back(energy);
		
		write_energies(output_file, beta, energy);

		beta += 0.02;


	}

	// vector<float> all_heat_capacities;
	// calculate_heat_capacities(all_heat_capacities, all_betas, all_energies);
	// write_heat_capacities(output_file, all_heat_capacities, all_betas);


	stringstream plotting_command;
	plotting_command << "python python/plot_energies.py " << width << " " << height << " " << steps;

	// cout << plotting_command << endl;
	system( plotting_command.str().c_str() );


	return 1;
}


void write_lattice(ofstream & output_file, ising::Lattice lat) {
	output_file << lat;
}

void calculate_heat_capacities(vector<float> & all_heat_capacities, vector<float> & all_betas, vector<float> & all_energies) {
	// Find the x granulity first.
	float delta_B = all_betas[1] - all_betas[0];
	
	all_heat_capacities.push_back(0);
	for (unsigned i=1; i < all_betas.size(); i++) {
		all_heat_capacities.push_back((all_energies[i + 1] - all_energies[i]) / delta_B);
	}	
}

void mc_update_system(ising::System & sys, int iteration) {
	for (unsigned i=0; i < iteration; i++) {		
		sys.step();
	}
}


void write_heat_capacities(ofstream & output_file, vector<float> all_heat_capacities, vector<float> all_betas) {
	for (unsigned i=0; i < all_betas.size(); i++) {
		output_file << fixed << setprecision(2) << all_betas[i] << "\t" << all_heat_capacities[i] << endl;
	}
}

void write_energies(ofstream & output_file, float beta, float energy) {
	output_file << fixed << setprecision(2) << beta << "\t" << energy << endl;
}

void write_to_file(ising::Lattice lat) {
	ofstream output_file("data/lattice.dat", ios::out);


	std::vector<std::vector<ising::Vertex> > vertices = lat.get_vertices();

	for (unsigned x=0; x < vertices.size(); x++) {
		for (unsigned y=0; y < vertices[x].size(); y++) {
			output_file << showpos << to_string(vertices[x][y].get_spin()) + "\t";
		}
		output_file << "\n";
	}

}