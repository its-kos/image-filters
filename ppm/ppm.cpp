#include <string>
#include <fstream>
#include <iostream>
#include "ppm.h"

namespace image {
	float* ReadPPM(const char* filename, int* w, int* h) {

		/*
		 *	We open the stream that will read the ppm file
		 *	in binary mode (Since the P6 format stores the image data
		 *	as binary).
		 */
		std::ifstream reader(filename, std::ios::in | std::ios::binary);
		
		//	Check that file exists - Opened normally
		if (!reader.is_open()) {

			std::cerr << "Error while opening the file: " << filename << "\n";
			reader.close();
			return nullptr;

		} else {

			//	We initialize the needed variables
			float maxVal;
			std::string line;

			reader >> line;

			while (line[0] == '#') {
				std::getline(reader, line);
			}

			//	For now only the P6 "Magic Number" (Image format) is supported
			if (line == "p6" || line == "P6") {

				reader >> *w;
				while (line[0] == '#') {
					std::getline(reader, line);
				}
				reader >> *h;
				while (line[0] == '#') {
					std::getline(reader, line);
				}

				reader >> maxVal;

				if (reader.fail()) {
					std::cerr << "Error reading header\n";
					reader.close();
					return nullptr;

				} else if (*w < 0 || *h < 0) {
					std::cerr << "Dimentions are smaller than 0\n";
					reader.close();
					return nullptr;

				} else if (maxVal <= 0 || maxVal > 255) {
					std::cerr << "Max value cannot be <= 0 or > 255 for P6 images\n";
					reader.close();
					return nullptr;
				} 

				int size = 3 * ((*w) * (*h));

				/*	
				 *	Get the position of our input sequence,
				 *	then set the position of the next character to be read
				 *	in our input sequence
				 */	 
				reader.seekg((int)reader.tellg() + 1, 0);

				/*
				 *	We normalize the image data before returning them,
				 *  so all images behave the same after reading them.
				 * 
				 *	In essence we abstract the value range for all image 
				 *	formats to just [0, 1].
				 */
				float* imageArray = new float[size];
				char* buffer = new char[size];
				reader.read(buffer, size);

				for (int i = 0; i < size; i++) {
					imageArray[i] = ((float)buffer[i]) / maxVal;
				}

				reader.close();
				delete[] buffer;
				return imageArray;

			} else if (line == "p3" || line == "P3") {

				/*	
				 *	Here we handle P3 format.
				 *	-In P3 images the image is given as ASCII text
				 *	-In P6 images the image data is stored in byte format, 
				 *	one byte per colour component (r,g,b)
				 */ 

				/*	
				 *	We open the stream that will read the ppm file
		         *	in ASCII mode (Since the P3 format stores the image data 
				 *	as ASCII).
				 */	
				std::ifstream reader(filename, std::ios::in);

			} else {
				std::cerr << "Invalid PPM format\n";
				reader.close();
				return nullptr;
			}
		}
	}

	// Now only supports P6 format.
	// TODO: implement P3 support.
	bool WritePPM(const char* filename, int w, int h, const float* data) {

		std::ofstream writer(filename, std::ios::binary | std::ios::out);

		if (writer.fail()) {
			std::cerr << "Write process failed \n";
			writer.close();
			return false;
		} else {
			int size = 3 * h * w;
			char* normalizedData = new char[size];

			writer << "P6\n" << w << " " << h << "\n" << "255\n";

			for (int i = 0; i < size; i++) {
				normalizedData[i] = data[i] * 255.0f;
			}

			writer.write(normalizedData, size);
			writer.close();

			delete[]normalizedData;
			return true;
		}
	}
}