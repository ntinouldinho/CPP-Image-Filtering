#ifndef _FILTER
#define _FILTER
#include <iostream>
#include "array2d.hpp"
#include "imageio.hpp"
using namespace math;
using namespace std;
using namespace image;
class Filter {
	public:
		//constuctors
		Filter() {}
		Filter(const Filter &f) { }
		//operator
		virtual image::Image operator << (const image::Image& image) = 0;
};
#endif