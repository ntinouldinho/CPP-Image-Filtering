#ifndef _FILTERLAPLACE
#define _FILTERLAPLACE
#include <iostream>
#include "Filter.h"
#include "array2d.hpp"
#include "FilterBlur.h"
#include "imageio.hpp"
#include <string>
using namespace math;
using namespace std;
class FilterLaplace : public Filter,public Array2D<float> {
public:
	//constuctor
	FilterLaplace()  {
		buffer.push_back(0);
		buffer.push_back(1);
		buffer.push_back(0);
		buffer.push_back(1);
		buffer.push_back(-4);
		buffer.push_back(1);
		buffer.push_back(0);
		buffer.push_back(1);
		buffer.push_back(0);
	}
	//operator
	image::Image operator << (const image::Image & image) {
		image::Image fimage(image);
		int N = 3;
		int bound = int(N / 2);
		for (unsigned int x = 0; x < fimage.getWidth(); x++) {
			for (unsigned int y = 0; y < fimage.getHeight(); y++) {
				Color newPixel(0);
				for (int m = -bound; m <= bound ; m++) {
					for (int n = -bound; n <= bound ; n++) {
						if (x + m < image.getWidth() && x + m >= 0 && y + n < image.getHeight() && y + n >= 0) {
							int bufx = m + bound;
							int bufy = n + bound;
							int indexbuffer = int(bufx + bufy * N);
							newPixel += image.getT(int(x + m), int(y + n))*buffer[indexbuffer];
						}
					}
				}
				newPixel = newPixel.clampToUpperBound(1);
				newPixel = newPixel.clampToLowerBound(0);
				fimage.setT(x, y, newPixel);
			}
		}
		return fimage;
	}
};
#endif