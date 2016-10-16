#ifndef LATTICE_H
#define LATTICE_H


#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <string>


#include "Vertex.h"

using namespace std;

namespace ising {
	class Lattice {

		public:
			Lattice();
			Lattice(unsigned width, unsigned height);
			Lattice(const Lattice & source);
			Lattice(vector<vector<Vertex>> & source_vertices);
			

			unsigned get_width() const;
			unsigned get_height() const;

			const ising::Vertex & get_vertex_at(int x, int y) const;
			std::vector< std::vector<ising::Vertex> > get_vertices() const;
			string make_string() const;

			void calculate_energy();
			float get_energy() const;
						
			friend std::ostream& operator<< (std::ostream&,  Lattice&);

		private:
			std::vector< std::vector<ising::Vertex> > _vertices;
			unsigned _width;
			unsigned _height;
			float _energy;

			void initialize_vertices();
	};
}


#endif /* LATTICE_H */
