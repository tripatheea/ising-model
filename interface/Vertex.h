#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>


namespace ising {
	class Vertex {

		public:
			Vertex(int spin);
			
			const int get_spin() const;
			void flip_spin();
			
			std::string make_string();

			friend std::ostream& operator<< (std::ostream&, const Vertex&);
		private:
			int _spin;
	};
}


#endif /* VERTEX_H */
