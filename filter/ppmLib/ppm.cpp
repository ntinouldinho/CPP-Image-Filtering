#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string.h>
#include <algorithm>

#include "ppm.h"

using namespace std;

float * image::ReadPPM(const char * filename, int * w, int * h) {
	ifstream iFile(filename, std::ios::binary);
	if (!iFile.is_open()) {
		cout << "Cannot open file\n";
		return nullptr;
	}
	string p = "";
	int w1 = 0;
	int h1 = 0;
	int max = 0;
	int k = 0;
	iFile >> p >> w1 >> h1 >> max;
	int num;
	//Header check
	if (p != "P6") {
		cout << "The file input is not of type P6" << endl;
		return nullptr;
	}
	if (max == 0) {
		cout << "The max number wasn't given" << endl;
		return nullptr;
	}
	if (h1 == 0) {
		cout << "The height wasn't given" << endl;
		return nullptr;
	}
	*h = h1; //put the height to return the height of the image into

	if (w1 == 0) {
		cout << "The width wasn't given" << endl;
		return nullptr;
	}
	*w = w1; //put the width to return the width of the image into.

	if (max > 255) {
		cout << "The max value is larger than 255" << endl;
		return nullptr;
	}
	iFile.read((char *)&num, 1);
	int size = 3 * (*w)*(*h);
	//initialize array with chars
	unsigned char* buffer = new unsigned char[size];
	//With one read command read all binary
	iFile.read((char*)(buffer), size);
	//initialize array with floats
	float* buffer2 = new float[size];
	//conversion of chars to numbers in [0,1]
	for (int i = 0; i < size; i++) {
		buffer2[i] = (float)buffer[i] / 255;
	}
	delete[]buffer;
	iFile.close();
	return buffer2;
}



bool image::WritePPM(const float * data, int w, int h, const char* filename) {
	ofstream file(filename, ios::out | ios::binary);
	if (!file.is_open()) {
		printf("Could not open file!\n");
		return false;
	}
	//Write header
	file << "P6" << "\n" << w << "\n" << h << "\n" << 255 << endl;
	//Write binary
	for (int i = 0; i < 3 * w*h; i++) {
		char val = data[i] * 255;
		file.write((char*)&val, sizeof(char));
	}
	// Make sure everything passed into the file
	file.flush();
	//Close file
	file.close();
	return true;
}
