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


void calculate_heat_capacities(vector<float> & all_heat_capacities, vector<float> & all_temps, vector<float> & all_energies);

void write_energies(ofstream & output_file, float temp, float energy);
void write_heat_capacities(ofstream & output_file, vector<float> all_heat_capacities, vector<float> all_temps);
void write_lattice(ofstream & output_file, ising::Lattice lat);

int main(int argc, char * argv[]) {

	// Define a new system first. 
	unsigned width = stoi(argv[1]);
	unsigned height = stoi(argv[2]);
	unsigned steps = stoi(argv[3]);

	vector<float> all_temps;
	vector<float> all_energies;

	ofstream energies_output_file("data/energy.dat", ios::out);
	ofstream heat_capacities_output_file("data/heat_capacities.dat", ios::out);
	ofstream file("temp.dat", ios::out);
	
	float temp = 1.0;
	float energy;
	// for (unsigned i=0; temp <= 1.0; i++) {
	for (unsigned i=0; temp <= 4.0; i++) {

		// if ((int(temp * 100) % 5) == 0) 
			// cout << endl << "========================================" << endl << endl << "Working with temp = " << temp << endl;

		float beta = 1 / temp;
		ising::System sys = ising::System(width, height, beta);
		sys.stabilize(1000);
		sys.mc_update(steps);
		

		// cout << "For the following lattice, I got E = " << sys.get_lattice().get_energy() << endl;
		// cout << sys.get_lattice() << endl;
		energy = sys.get_lattice().get_energy();

		// cout << "Energy according to energy is: " << energy << endl;
		
		all_temps.push_back(temp);
		all_energies.push_back(energy);
		
		write_energies(energies_output_file, temp, energy);

		temp += 0.5;
	}

	vector<float> all_heat_capacities;
	calculate_heat_capacities(all_heat_capacities, all_temps, all_energies);
	write_heat_capacities(heat_capacities_output_file, all_heat_capacities, all_temps);


	stringstream plotting_command;
	plotting_command << "python python/plot_energies.py " << width << " " << height << " " << steps;
	system( plotting_command.str().c_str() );
	
	plotting_command.str("");
	plotting_command << "python python/plot_heat_capacities.py " << width << " " << height << " " << steps;
	system( plotting_command.str().c_str() );


	return 1;
}




void write_lattice(ofstream & output_file, ising::Lattice lat) {
	output_file << lat;
}

void calculate_heat_capacities(vector<float> & all_heat_capacities, vector<float> & all_temps, vector<float> & all_energies) {
	// Find the x granulity first.
	float delta_T = all_temps[1] - all_temps[0];
	
	all_heat_capacities.push_back(0);
	for (unsigned i=1; i < all_temps.size(); i++) {
		all_heat_capacities.push_back((all_energies[i + 1] - all_energies[i]) / delta_T);
	}	
}



void write_heat_capacities(ofstream & output_file, vector<float> all_heat_capacities, vector<float> all_temps) {
	for (unsigned i=0; i < all_temps.size(); i++) {
		output_file << all_temps[i] << "\t" << all_heat_capacities[i] << endl;
	}
}

void write_energies(ofstream & output_file, float temp, float energy) {
	output_file << temp << "\t" << energy << endl;
}
