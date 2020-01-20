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
		T mag;
	public:
		Vector() = delete;
		Vector(size_t size) :
			size(size),
			elements(std::make_unique<T[]>(size)),
			mag(0)
		{}
		Vector(std::initializer_list<T> list) :
			size(list.size()),
			elements(std::make_unique<T[]>(list.size()))
		{
			for (size_t ii = 0; ii < list.size(); ++ii) {
				elements[ii] = *(list.begin() + ii);
				mag += *(list.begin() + ii) * *(list.begin() + ii);
			}
			mag = (T)std::sqrt(mag);
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

		//diff
		Vector<T> operator-(const Vector<T>& other) const {
			if (size != other.size) {
				throw std::runtime_error("in LinearAlgebra::Vector::operator-(...), vector size mismatch");
			}
			Vector<T> result(size);
			for (size_t ii = 0; ii < size; ++ii) {
				T diff = elements[ii] - other.elements[ii];
				result.elements[ii] = diff;
				result.mag += diff * diff;
			}
			result.mag = (T)std::sqrt(result.mag);
			return result;
		}
		Vector<T>& operator-=(const Vector<T> other) {
			*this = *this - other;
			return *this;
		}

		//access
		const T& operator[](size_t idx) const {
			return elements[idx];
		}

		//scale
		void Scale(T factor) {
			for (size_t ii = 0; ii < size; ++ii) {
				elements[ii] *= factor;
			}
		}

		//sum of all elements
		T Sum() const {
			T sum = 0;
			for (size_t ii = 0; ii < size; ++ii) {
				sum += elements[ii];
			}
			return sum;
		}

		//normalize
		Vector<T> Normalize() const {
			Vector<T> normal(size);
			for (size_t ii = 0; ii < size; ++ii) {
				normal.elements[ii] = elements[ii] / mag;
			}
			normal.mag = (T)1;
			return normal;
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
		/*Vector<T> Cross(const Vector<T>& other) const {
			if (size != other.size) {
				throw std::runtime_error("in LinearAlgebra::Vector::Cross(...), vector size mismatch");
			}
			Vector<T> cross(size);
			for (size_t ii = 0; ii < size; ++ii) {
				dot += elements[ii] * other.elements[ii];
			}
			return cross;
		}*/

		//opengl needs access
		/*size_t GetSizeInBytes() const {
			return size * sizeof T;
		}
		const T* GetPointerToData() const {
			return elements.get();
		}*/
	};
}