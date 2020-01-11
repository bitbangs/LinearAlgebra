#pragma once

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <memory>
#include <type_traits>

namespace LinearAlgebra
{
	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class Vector
	{
	private:
		size_t size;
		std::unique_ptr<T[]> elements;
	public:
		Vector() = delete;
		Vector(size_t size) :
			size(size),
			elements(std::make_unique<T[]>(size))
		{}
		Vector(std::initializer_list<T> list) :
			size(list.size()),
			elements(std::make_unique<T[]>(list.size()))
		{
			for (size_t ii = 0; ii < list.size(); ++ii) {
				elements[ii] = *(list.begin() + ii);
			}
		}

		//equality
		bool operator==(const Vector<T>& other) const {
			if (size != other.size) {
				return false;
			}
			for (size_t ii = 0; ii < size; ++ii) {
				if (elements[ii] != other.elements[ii]) {
					return false;
				}
			}
			return true;
		}
		bool operator!=(const Vector<T>& other) const {
			return !(*this == other);
		}

		//sum of all elements
		T Sum() const {
			T sum = 0;
			for (size_t ii = 0; ii < size; ++ii) {
				sum += elements[ii];
			}
			return sum;
		}

		//dot product
		T Dot(const Vector<T>& other) const {
			if (size != other.size) {
				throw std::runtime_error("in LinearAlgebra::Vector::Dot(...), vector size mismatch");
			}
			T dot = 0;
			for (size_t ii = 0; ii < size; ++ii) {
				dot += elements[ii] * other.elements[ii];
			}
			return dot;
		}

		//cross product

	};
}