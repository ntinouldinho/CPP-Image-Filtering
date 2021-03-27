//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2019 -2020
//
#ifndef _IMAGEI
#define _IMAGEI

#include <iostream>
#include "vec3.h"
#include "imageio.h"
#include <string>
#include "array2d.hpp"
#include "ppmLib/ppm.h"
using namespace std;
using namespace math;


namespace image
{
	
	typedef Vec3<float> Color;
	class Image : public Array2D<Color>, public ImageIO
	{
	public:
		
		
		/*!
		 * Loads the image data from the specified file, if the extension of the filename matches the format string.
		 *
		 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. 
		 *
		 * \param filename is the string of the file to read the array data from.
		 * \param format specifies the file format according to which the array data should be decoded from the file.
		 * Only the "ppm" format is a valid format string for now.
		 *
		 * \return true if the loading completes successfully, false otherwise.
		 */
		virtual bool load(const string & filename, const string & format){
			if (format.compare("ppm") != 0) {
				cout << "Wrong format" << endl;
				return false;
			}
			int w = 0;
			int h = 0;
			float* colors = ReadPPM(filename.c_str(), &w, &h);
			if (colors == nullptr) {
				return false;
			}
			width = w;
			height = h;

			for (unsigned int i = 0; i <= 3 * getWidth()*getHeight() - 3; i += 3) {
				Vec3<float> ok;
				ok.r = colors[i];
				ok.g = colors[i+1];
				ok.b = colors[i + 2];
				buffer.push_back(ok);
			}
			delete[]colors;
			return true;
		};
		
		
		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. 
		*
		* \param filename is the string of the file to write the array data to.
		* \param format specifies the file format according to which the array data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		virtual bool save(const std::string & filename, const std::string & format){
			if (format.compare("ppm") != 0) {
				cout << "Wrong format" << endl;
				return false;
			}
			if(buffer.empty()) { 
				return false; 
			}
			float* floatArray = new float[3 * getWidth()*getHeight()];
			int f = -1;
			for (unsigned int i = 0; i <= 3 * getWidth()*getHeight() - 3; i += 3) {
				f++;
				for (unsigned int j = 0; j < 3; j++) {
					floatArray[i + j] = (float)buffer.at(f)[j];
				}
			}
			return image::WritePPM(floatArray, Image::getWidth(), Image::getHeight(), filename.c_str());

		};
		Image() {}
		~Image() {}
		Image(const Image& image) :Array2D <Color>(image) {}
		

	};

} //namespace image
#endif