#pragma once

#include "Image.h"

typedef math::Vec3<float> Color;

class Filter {
	protected:
		virtual Image operator<< (const Image& image) = 0;
};

class FilterLinear : Filter {
	protected:
		Color m_a, m_c;
	public:
		FilterLinear(float a1, float a2, float a3, float c1, float c2, float c3);
		Image operator<< (const Image& image);
};

class FilterGamma : Filter {
	protected:
		double m_g;
	public:
		FilterGamma(double g);
		Image operator<< (const Image& image);
};