#ifndef _FILTERLINEAR
#define _FILTERLINEAR
#include <iostream>
#include "Filter.h"
#include "array2d.h"
#include "imageio.hpp"
using namespace math;
using namespace std;
class FilterLinear : public Filter{
	Color a;
	Color c;
	public:
		//constuctors
		FilterLinear() { Color a(-1,-1,-1); Color c( 1, 1, 1);}
		FilterLinear(const FilterLinear &f) : a(f.a), c(f.c) { }
		FilterLinear(Color &a , Color &c) : a(a), c(c){ }
		//operator
		image::Image operator << (const image::Image& image) {
			image::Image fimage(image);
			
			for (unsigned int x = 0; x < image.getWidth(); x++) {
				for (unsigned int y = 0; y < image.getHeight(); y++) {
					Color color = fimage.getT(x, y);
					color *= a;
					color += c;
					color=color.clampToLowerBound(0.0);
					color=color.clampToUpperBound(1.0);
					fimage.setT(x, y, color);
				}
			}
			return fimage;
		}
};
#endif
