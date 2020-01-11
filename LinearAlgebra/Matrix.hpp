#pragma once

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <memory>

namespace LinearAlgebra
{
	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class Matrix
	{
	private:
		size_t size;
		std::unique_ptr<T[]> elements;
	public:
		Matrix(size_t size) :
			size(size),
			elements(std::make_unique<T[]>(size * size))
		{
			if (size < 2 || size > 4) {
				throw std::runtime_error("size of matrix must be 2x2, 3x3, or 4x4");
			}
			for (size_t ii = 0; ii < size; ++ii) {
				for (size_t jj = 0; jj < size; ++jj) {
					elements[(ii * size) + jj] = (T)0;
				}
			}
		}
		Matrix(std::initializer_list<T> list) :
			elements(std::make_unique<T[]>(list.size()))
		{
			switch (list.size()) {
			case 4:
				size = 2;
				break;
			case 9:
				size = 3;
				break;
			case 16:
				size = 4;
				break;
			default:
				throw std::runtime_error("size of matrix must be 2x2, 3x3, or 4x4");
			}
			for (size_t ii = 0; ii < list.size(); ++ii) {
				elements[ii] = *(list.begin() + ii);
			}
		}

		//equality
		bool operator==(const Matrix<T>& other) const {
			if (size != other.size) {
				return false;
			}
			for (size_t ii = 0; ii < size * size; ++ii) {
				if (elements[ii] != other.elements[ii]) {
					return false;
				}
			}
			return true;
		}
		bool operator!=(const Matrix<T>& other) const {
			return !(*this == other);
		}

		//multiply
		Matrix<T> operator*(const Matrix<T>& right) const {
			if (size != right.size) {
				throw std::runtime_error("cannot multiply matrices of different size");
			}
			Matrix<T> result(size);
			for (size_t ii = 0; ii < size; ++ii) { //row
				for (size_t jj = 0; jj < size; ++jj) { //column
					for (size_t kk = 0; kk < size; ++kk) {
						result.elements[ii + (jj * size)] +=
							elements[ii + (kk * size)] *
							right.elements[(jj * size) + kk];
					}
				}
			}
			return result;
		}

		//opengl needs access
		size_t GetSizeInBytes() const {
			return size * size * sizeof T;
		}
		const T* GetPointerToData() const {
			return elements.get();
		}
	};
}