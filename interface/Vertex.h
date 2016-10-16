#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>


namespace ising {
	class Vertex {

		public:
			Vertex(int spin);

			Vertex(const Vertex & source_vertex);	// Copy constructor.
			
			

			const int get_spin() const;
			void flip_spin();
			
			std::string make_string() const;

			friend std::ostream& operator<< (std::ostream&, Vertex&);
		private:
			int _spin;
	};
}


#endif /* VERTEX_H */
