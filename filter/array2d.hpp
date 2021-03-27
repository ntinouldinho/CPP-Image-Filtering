//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2019 - 2020
//
//

#ifndef _ARRAY2D
#define _ARRAY2D
#include <vector>


namespace math
{

//------------------------------------ class Array2D ------------------------------------------------

	/*! It is the class that represents a generic data container for a two-dimensional array of data.
	 * 
	 * It holds the actual buffer of the data values and provides methods for accessing them, 
	 * either as individual tokens or as a memory block. 
	 *
	 */ 
	template <typename T>
	class Array2D
	{

	protected:
		std::vector<T> buffer;                       //! Holds the array data.

		unsigned int width, 						 //! The width of the array (in pixels)
					 height;		                 //! The height of the array (in pixels)

	public:
		void Replicate(const Array2D<T>& right) { //usage:copy constructor and operator =
			width = right.width;
			height = right.height;
			for (auto it = right.buffer.begin(); it != right.buffer.end(); ++it) {
				buffer.push_back(*it);
			}
		}
		/*! Returns the width of the array
		 */
		const unsigned int getWidth() const { return width; }
		
		/*! Returns the height of the array
		 */
		const unsigned int getHeight() const { return height; }

		// data accessors and mutators
		
		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal array data, but rather a pointer 
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer. 
		 */
		T * getRawDataPtr(){return buffer;};

		/*! Copies the array data from an external raw buffer to the internal array buffer. 
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the 
		 *  Array2D object. If the array buffer cannot be properly resized or the width or height of the array are 0, 
		 *  the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Array2D object.
		 */
		void setData(const T* const& data_ptr) { //set buffer to buffer at (x,y)
			if (data_ptr == nullptr || sizeof(data_ptr)/sizeof(data_ptr[0]) == 0) {
				return;
			}
			for (unsigned int i = 0; i < sizeof(data_ptr) / sizeof(*data_ptr); i++) {
				buffer[i] = *(data_ptr + i);
			}
		};


		/*! Returns a reference to the stored item at location (x,y).
		 *
		 *	\param x is the horizontal coordinate of the item.
		 *  \param y is the vertical coordinate of the item.
		 *
		 *  \return a reference to the item at location (x,y).
		 */
		T & operator () (unsigned int x, unsigned int y){return buffer[x*getWidth() + y];};

		T getT(unsigned int x, unsigned int y) const { //get data for buffer at (x,y)
			if (y > getHeight() || x > getWidth() || y < 0 || x < 0) {
				return T();
			}
			else {
				return buffer[y * getWidth() + x];
			}
		};

		void setT(unsigned int x, unsigned int y, T& value) { //set value to buffer at (x,y)
			if (y > getHeight() || x > getWidth() || y < 0 || x < 0) {
				return;
			}
			else {
				buffer[y * getWidth() + x] = value;
			}
		};

		// constructors and destructor

		/*! Constructor with data initialization.
		 * 
		 * Default parameters let it also be used as a default constructor.
		 *
		 * \param width is the desired width of the new array.
		 * \param height is the desired height of the new array.
		 * \param data_ptr is the source of the data to copy to the internal array buffer. 
		 * If none is provided, but the width and height are non-zero, the buffer is initialized to default values (all zero - black).
		 * 
		 * \see setData
		 */ 
		Array2D(unsigned int width = 0, unsigned int height = 0, const T * data_ptr = 0){Array2D<T>::setData(data_ptr);};
		
		/*! Copy constructor.
		 *
		 * \param src is the source array to replicate in this object.
		 */
		Array2D(const Array2D &src){Replicate(src);};
		
		/*! The Array2D destructor.
		 */
		~Array2D(){width = height = 0;};

		/*! Copy assignment operator.
		 *
		 * \param right is the source array.
		 */
		Array2D & operator = (const Array2D & right){
			if (&right == this) {
				return *this;
			}
			if (!buffer.empty()) {
				buffer.clear();
			}
			Replicate(right);
			return *this;
		};

	};
	
} //namespace math

/* Do not modify the current file to provide the implementation for the 2D array class. Instead, use the array2d.hpp file to
   provide the difinitions of the class member functions:
*/
#include "array2d.hpp"
#include "array2d.h"


#endif