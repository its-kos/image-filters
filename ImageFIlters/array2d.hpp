#include "array2d.h"
#include "vec3.h"

using namespace math;

template <typename T>
const unsigned int Array2D<T>::getWidth() const {
	return m_width;
}

template <typename T>
const unsigned int Array2D<T>::getHeight() const {
	return m_height;
}

template <typename T>
T* Array2D<T>::getRawDataPtr() {
	return m_buffer;
}

template <typename T>
void Array2D<T>::setData(const T* const data_ptr) {
	m_buffer.clear();
	for (int i = 0; i < m_width * m_height; i++) {
		m_buffer.push_back(*(data_ptr + i));
	}
}

template <typename T>
T& Array2D<T>::operator() (unsigned int x, unsigned int y) {
	return m_buffer.at(x + (y * m_width));
}

template <typename T>
Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
	m_width = width;
	m_height = height;
	if (data_ptr != nullptr) {
		for (int i = 0; i < (width * height); i++) {
			m_buffer.push_back(data_ptr[i]);
		}
	} else {
		Vec3<float> vector(0);
		for (int i = 0; i < (width * height); i++) {
			m_buffer.push_back(vector);
		}
	}
}

/*
 *	Rule of 3:
 *	"If you need to explicitly declare either the destructor,
 *	copy constructor or copy assignment operator yourself,
 *	you probably need to explicitly declare all three of them."
 */

template <typename T>
Array2D<T>::Array2D(const Array2D& src) {
	m_width = src.getWidth();
	m_height = src.getHeight();
	setData(src.m_buffer.data());
}

template <typename T>
Array2D<T>::~Array2D() {}

template <typename T>
Array2D<T>& Array2D<T>::operator= (const Array2D<T>& that) {
	if (this != &that) {
		m_width = that.getWidth();
		m_height = that.getHeight();
		m_buffer.clear();
		setData(that.m_buffer.data());
	}
	return *this;
}