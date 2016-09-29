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
			Lattice(Lattice & source);
			

			unsigned get_width() ;
			unsigned get_height() ;

			ising::Vertex & get_vertex_at(int x, int y) ;
			std::vector< std::vector<ising::Vertex> > get_vertices();
			string make_string() ;

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
