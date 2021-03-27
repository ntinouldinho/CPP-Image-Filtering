#include <iostream>
#include <string>
#include "array2d.hpp"
#include "Filter.h"
#include "FilterGamma.h"
#include "FilterLinear.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
#include "imageio.h"
#include "vec3.h"

using namespace math;
using namespace std;
using namespace image;

int main(int argc, char *argv[]) {
	if (argc<2) {
		cout << "No arguments" << endl;
		system("pause");
		return -1;
	}
	std::string arg1 = argv[1];
	if (arg1.compare("filter")==0) {
		//create image
		string filename = "";
		filename = argv[argc-1];
		if (filename.find(".")<0) { 
			cout << "No filter name" << endl;
			system("PAUSE");
			return -1;
		}
		image::Image image;//initialize image
		string format = filename.substr(filename.find(".") + 1);//find format
		if (!image.load(filename, format)) {//load image
			cout << "Something went wrong while loading the image" << endl;
			system("PAUSE");
			return -1;
		}
		//print image dimensions
		cout << "Image dimensions are: " << image.getWidth() << " X " << image.getHeight() << endl;
		int i = 2;
		while (i < argc) { 
			std::string f = argv[i++];
			if (f.compare( "-f")==0) { //start new filter
				std::string filname = argv[i++];
				if (filname.compare("gamma")==0) {
					if (i + 2 <= argc) { //enough arguments to create and apply this filter
						std::string num = argv[i++];
						FilterGamma gamma(stof(num.c_str())); //create filter gamma
						cout << "Loading. . ." << endl;
						image = gamma << image; //apply filter gamma
					}
				}
				else if (filname.compare("linear")==0) {
					if (i + 7 <= argc) { //enough arguments to create and apply this filter
						std::string num1 = argv[i++];
						std::string num2 = argv[i++];
						std::string num3 = argv[i++];
						Vec3<float>* a = new Vec3<float>(stof(num1.c_str()), stof(num2.c_str()), stof(num3.c_str()));
						num1 = argv[i++];
						num2 = argv[i++];	
						num3 = argv[i++];
						Vec3<float>* c = new Vec3<float>(stof(num1.c_str()), stof(num2.c_str()), stof(num3.c_str()));
						FilterLinear linear(*a, *c); //create filter linear
						cout << "Loading. . ." << endl;
						image = linear << image;//apply filter linear
					}
				}
				else if (filname.compare("blur")==0) {
					if (i + 2 <= argc) { //enough arguments to create and apply this filter
						std::string num = argv[i++];
						FilterBlur blur(stof(num.c_str()));//create filter blur
						cout << "Loading. . ." << endl;
						image = blur << image; //apply filter blur
					}
				}
				else if (filname.compare("laplace")==0) {
					FilterLaplace laplace; //create filter laplace
					cout << "Loading. . ." << endl;
					image = laplace << image;//apply filter laplace
				}
				else {
					cout << "Wrong filter name!" << endl;
				}
			}
		}
		if (image.save("filtered_" + filename, format)) {
			cout << "The new image was saved successfully with file name:" << "filtered_" + filename << endl;
		}
		else {
			cout << "Something went wrong in creating or saving the new image" << endl;
		}
	}
	system("pause");

	return 0;
}