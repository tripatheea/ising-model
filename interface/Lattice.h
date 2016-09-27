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
			Lattice(unsigned width, unsigned height);

			Lattice(const Lattice & source_lattice);	// Copy constructor.

			
			 unsigned get_width() ;
			 unsigned get_height() ;

			 ising::Vertex & get_vertex_at(int x, int y) ;
			 std::string make_string() ;

			 float get_energy() ;
						
			friend std::ostream& operator<< (std::ostream&,  Lattice&);

		private:
			 std::vector< std::vector<ising::Vertex> > _vertices;
			 unsigned _width;
			 unsigned _height;
			float _energy;

			void calculate_energy();
			void initialize_vertices();
	};
}


#endif /* LATTICE_H */
