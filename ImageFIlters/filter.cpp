#include "Filter.h"
#include "vec3.h"
#include <math.h>
#include <iostream>


FilterLinear::FilterLinear(float a1, float a2, float a3, float c1, float c2, float c3) {
	Color tempA(a1, a2, a3);
	Color tempB(c1, c2, c3);
	m_a = tempA;
	m_c = tempB;
}

Image FilterLinear::operator<< (const Image& image) {
	unsigned int width = image.getWidth();
	unsigned int height = image.getHeight();

	Image tempImage = Image(image);

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			tempImage(j, i) *= m_a;
			tempImage(j, i) += m_c;
			tempImage(j, i) = tempImage(j, i).clampToLowerBound(0.0).clampToUpperBound(1.0);
		}
	}
	return tempImage;
}


FilterGamma::FilterGamma(double g) {
	m_g = g;
}

Image FilterGamma::operator<< (const Image& image) {
	unsigned int width = image.getWidth();
	unsigned int height = image.getHeight();

	Image tempImage = Image(image);

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			tempImage(j, i).x = pow(tempImage(j, i).x, m_g);
			tempImage(j, i).y = pow(tempImage(j, i).y, m_g);
			tempImage(j, i).z = pow(tempImage(j, i).z, m_g);
			tempImage(j, i) = tempImage(j, i).clampToLowerBound(0.5).clampToLowerBound(2);
		}
	}
	return tempImage;
}