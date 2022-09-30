# pragma once

#include <vector>
#include "array2d.h"
#include "vec3.h"

namespace math {

	/*	
	 *	It is the class that represents a generic data container for a two-dimensional array of data.
	 *
	 *	It holds the actual buffer of the data values and provides methods for accessing them,
	 *	either as individual tokens or as a memory block.
	 *	
	 *	It is templated so it can act as a base container for data other than images / colors.
	 */
	template <typename T>
	class Array2D {
		protected:

			//	Holds the array data.
			std::vector<T> m_buffer;       

			//	The width and height of the array (in pixels)
			unsigned int m_width, m_height;
			         		                 
		public:

			//	Returns the width of the array
			const unsigned int getWidth() const;

			//	Returns the height of the array
			const unsigned int getHeight() const;

			/*	Data accessors and mutators	*/

			/*	
			 *	Obtains a pointer to the internal data.
			 *
			 *  This is NOT a copy of the internal array data, but rather a pointer
			 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
			 */
			T* getRawDataPtr();

			/*	
			 *	Copies the array data from an external buffer to the internal array buffer.
			 *
			 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
			 *  Array2D object. If the input array buffer cannot be properly resized or the width or height of the array are 0,
			 *  the method should exit immediately.
			 * 
			 *	TODO: Check for buffer size compatibility
			 *
			 *  \param data_ptr is the const pointer to the preallocated buffer from where to copy the data to the Array2D object.
			 */
			void setData(const T* const data_ptr);

			/*
			 *	Returns a reference to the stored item at location (x,y).
			 *
			 *	\param x is the horizontal coordinate of the item.
			 *  \param y is the vertical coordinate of the item.
			 *
			 *  \return a reference to the item at location (x,y).
			 */
			T& operator() (unsigned int x, unsigned int y);

			/* constructors and destructor */

			/*	
			 *	Constructor with data initialization.
			 *	Default parameters let it be used as a default constructor as well.
			 *
			 *	\param width is the desired width of the new array.
			 *	\param height is the desired height of the new array.
			 *	\param data_ptr is the source of the data to copy to the internal array buffer.
			 *	If none is provided, but the width and height are non-zero, the buffer is initialized to default values (all zero - black).
			 *
			 *	\see setData
			 */
			Array2D(unsigned int width = 0, unsigned int height = 0, const T* data_ptr = nullptr);

			/*	
			 *	Copy constructor.
			 *
			 *	\param src is the source array to replicate in this object.
			 */
			Array2D(const Array2D& src);

			//	The Array2D destructor.
			~Array2D();

			/*	
			 *	Copy assignment operator.
			 *
			 *	\param right is the source array.
			 */
			Array2D& operator = (const Array2D& right);

	};
} 

/*	
 *	Templates need to be instantiated by the compiler before actually compiling them into object code. 
 *	This instantiation can only be achieved if the template arguments are known.
 * 
 *	Thus, we cannot put template implementations in separete ".cpp" files, so we include the implementation in 
 *	this header file.
 */

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
	m_width = src.width;
	m_height = src.height;
	setData(src.m_buffer.data());
}

template <typename T>
Array2D<T>::~Array2D() {}

template <typename T>
Array2D<T>& Array2D<T>::operator= (const Array2D<T>& that) {
	if (this != &that) {
		m_width = that.width;
		m_height = that.height;
		m_buffer.clear();
		setData(that.m_buffer.data());
	}
	return *this;
}