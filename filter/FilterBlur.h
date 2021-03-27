#ifndef _FILTERBLUR
#define _FILTERBLUR
#include <iostream>
#include "Filter.h"
#include "array2d.hpp"
#include "imageio.hpp"
using namespace math;
using namespace std;
using namespace image;

class FilterBlur : public Filter, public Array2D<float> {
	unsigned N;
public:
	//constuctors
	FilterBlur() {  }
	FilterBlur(const FilterBlur &f) :N(f.N){
		vector<float> tempVector;
		buffer.swap(tempVector);
		for (unsigned i = 0; i < N*N; i++) {
			buffer.push_back(1.0 / (N*N));
		}
	}
	FilterBlur(unsigned int N) : N(N) { 
		for (unsigned i = 0; i < N*N; i++) {
			buffer.push_back(1.0 / (N*N));
		}
	}
	//operator
	  virtual image::Image operator << (const image::Image & image) {
		image::Image fimage(image);
		int add = 0;
		if (N % 2 == 0) {
			add = -1;
		}
		int bound = int(N / 2);
		for (unsigned int x = 0; x < fimage.getWidth(); x++) {
			for (unsigned int y = 0; y < fimage.getHeight(); y++) {
				Color newPixel(0);
				for (int m = -bound; m <= bound+add; m++) {
					for (int n = -bound; n <= bound+add; n++) {
						if (x + m < image.getWidth() && x + m >= 0 && y + n < image.getHeight() && y + n >= 0) {
								int bufx = m + bound;
								int bufy = n + bound;
								int indexbuffer= int(bufx+bufy*N);
								newPixel += image.getT(int(x + m), int(y + n))*buffer.at(indexbuffer);
						}
					}
				}
				newPixel = newPixel.clampToLowerBound(0);
				newPixel = newPixel.clampToUpperBound(1);
				fimage.setT(x, y, newPixel);
			}
		}
		return fimage;
	}
};
#endif