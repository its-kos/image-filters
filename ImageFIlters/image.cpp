#include <iostream>
#include "Image.h"
#include "ppm.h"

/*
 *	Default constructor.
 *	Using initializer list to call the base class constructor.
 *	Having default values allows us the constructor to be used the default constructor.
 */	
Image::Image() : Array2D<Color>() {}

//	Constructor.
//	Using initializer list to call the base class constructor.
Image::Image(unsigned int width, unsigned int height, const Color* data_ptr) : Array2D<Color>(width, height, data_ptr) {}

//	Copy constructor.
//	Using initializer list to call the base class constructor.
Image::Image(const Image& src) : Array2D<Color>(src) {}

bool Image::load(const std::string& filename, const std::string& format) {

	if (format == "ppm") {

		int m_width, m_height;
		float* im_p = image::ReadPPM(filename.c_str(), &m_width, &m_height);

		if (!im_p) {
			return false;
		}

		m_buffer.clear();
		for (int i = 0; i < m_width * m_height * 3; i += 3) {
			Color c(im_p[i], im_p[i + 1], im_p[i + 2]);
			m_buffer.push_back(c);
		}

		delete[] im_p;
		return true;

	} else {
		std::cout << "Only the ppm image format is supported for now. \n";
		return false;
	}
}

bool Image::save(const std::string& filename, const std::string& format) {
	const char* path = filename.c_str();
	if (format == "ppm") {
		return image::WritePPM((float*)m_buffer.data(), m_width, m_height, path);
	}
	else {
		std::cout << "Only the ppm image format is supported for now. \n";
		return false;
	}
}