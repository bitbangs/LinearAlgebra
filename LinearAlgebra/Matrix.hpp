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
		size_t cols;
		size_t rows;
		std::unique_ptr<T[]> elements;
	public:
		Matrix(size_t cols, size_t rows) :
			cols(cols),
			rows(rows),
			elements(std::make_unique<T[]>(cols * rows))
		{
			for (size_t ii = 0; ii < cols; ++ii) {
				for (size_t jj = 0; jj < rows; ++jj) {
					elements[(ii * cols) + jj] = (T)0;
				}
			}
		}
		Matrix(size_t cols, size_t rows, std::initializer_list<T> list) :
			cols(cols),
			rows(rows),
			elements(std::make_unique<T[]>(list.size()))
		{
			if (cols * rows != list.size()) {
				throw std::runtime_error("cols and rows passed to Matrix constructor do not match size of initializer list");
			}
			for (size_t ii = 0; ii < list.size(); ++ii) {
				elements[ii] = *(list.begin() + ii);
			}
		}

		//equality
		bool operator==(const Matrix<T>& other) const {
			if (cols != other.cols || rows != other.rows) {
				return false;
			}
			for (size_t ii = 0; ii < cols * rows; ++ii) {
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
			if (cols != right.rows) {
				throw std::runtime_error("cannot multiply matrices of different size");
			}
			Matrix<T> result(cols, right.rows);
			for (size_t ii = 0; ii < right.rows; ++ii) { //row
				for (size_t jj = 0; jj < cols; ++jj) { //column
					for (size_t kk = 0; kk < cols; ++kk) { //number of sums for each element
						result.elements[ii + (jj * cols)] +=
							elements[ii + (kk * rows)] * right.elements[(jj * right.cols) + kk]; //don't think the scales are correct
					}
				}
			}
			return result;
		}

		//opengl needs access
		size_t GetSizeInBytes() const {
			return cols * rows * sizeof T;
		}
		const T* GetPointerToData() const {
			return elements.get();
		}
	};
}