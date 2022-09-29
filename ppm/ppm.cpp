#include <string>
#include <fstream>
#include <iostream>
#include "ppm.h"

namespace image {

	float* ReadPPM(const char* filename, int* w, int* h) {

		//	We open the stream that will read the ppm file
		//	in binary mode.
		std::ifstream reader(filename, std::ios::in | std::ios::binary);
		
		//	Check that file exists - Opened normally
		if (!reader.is_open()) {

			std::cerr << "Error while opening the file: " << filename << "\n";
			reader.close();
			return nullptr;

		} else {

			//	We initialize the needed variables
			int maxVal;
			float* imageArray;

			std::string line;
			reader >> line;

			//	For now only the P6 "Magic Number" (Image format) is supported
			if (line == "p6" || line == "P6") {

				reader >> *w;
				reader >> *h;
				reader >> maxVal;

				int totalBytes = 3 * ((*w) * (*h));

				if (reader.fail()) {
					std::cerr << "Error reading header\n";
					reader.close();
					return nullptr;
				}

				if (*w < 0 || *h < 0) {

					std::cerr << "Dimentions are smaller than 0\n";
					reader.close();
					return nullptr;

				} else if (maxVal <= 0 || maxVal > 255) {

					std::cerr << "Wrong value range (Should be 255)\n";
					reader.close();
					return nullptr;

				}

				/*	Get the position of our input sequence,
				*	then set the position of the next character to be read
				*	in our input sequence
				*/	 
				reader.seekg((int)reader.tellg() + 1, 0);

				imageArray = new float[totalBytes];
				char* buffer = new char[totalBytes];
				reader.read(buffer, totalBytes);

				for (int i = 0; i < totalBytes; i++) {
					imageArray[i] = buffer[i] / 255.0f;
				}

				reader.close();
				delete[] buffer;
				return imageArray;

			} else if (line == "p3" || line == "P3") {

				/*	Here we handle P3 format.
				*	-In P3 images the image is given as ASCII text
				*	-In P6 images the image data is stored in byte format, 
				*	one byte per colour component (r,g,b)
				*/ 

			} else {
				std::cerr << "Invalid PPM format\n";
				reader.close();
				return nullptr;
			}
		}
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {

		std::ofstream writer;
		writer.open(filename, std::ios::binary | std::ios::out);

		if (writer.fail()) {
			std::cerr << "Write process failed \n";
			writer.close();
			return false;

		} else {
			int size = 3 * h * w;
			char* normalizedData = new char[size];

			writer << "P6 \n" << w << " " << h << "\n" << "255\n";

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