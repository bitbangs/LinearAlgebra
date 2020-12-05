#pragma once

#include <algorithm>
#include <cmath>
#include <exception>
#include <initializer_list>
#include <memory>
#include <stdexcept>
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
			mag(T(0))
		{}
		Vector(std::initializer_list<T> list) :
			size(list.size()),
			elements(std::make_unique<T[]>(list.size())),
			mag(T(0))
		{
			for (size_t ii = 0; ii < list.size(); ++ii) {
				elements[ii] = *(list.begin() + ii);
				mag += *(list.begin() + ii) * *(list.begin() + ii);
			}
			mag = (T)std::sqrt(mag);
		}

		T const GetMagnitude() const {
			return mag;
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

		//add
		Vector<T> operator+(const Vector<T>& other) const {
			if (size != other.size) {
				throw std::runtime_error("in LinearAlgebra::Vector::operator-(...), vector size mismatch");
			}
			Vector<T> result(size);
			for (size_t ii = 0; ii < size; ++ii) {
				T sum = elements[ii] + other.elements[ii];
				result.elements[ii] = sum;
				result.mag += sum * sum;
			}
			result.mag = (T)std::sqrt(result.mag);
			return result;
		}
		Vector<T>& operator+=(const Vector<T>& other) {
			*this = *this + other;
			return *this;
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
		Vector<T>& operator-=(const Vector<T>& other) {
			*this = *this - other;
			return *this;
		}

		//access
		const T& operator[](size_t idx) const {
			return elements[idx];
		}

		//scale each element by the same factor
		Vector<T> Scale(T factor) {
			Vector<T> result(size);
			for (size_t ii = 0; ii < size; ++ii) {
				result.elements[ii] = elements[ii] * factor;
			}
			return result;
		}

		//scale each element by a vector of the same length; element by element
		Vector<T> operator*(const Vector<T>& other) const {
			if (size != other.size) {
				throw std::runtime_error("in LinearAlgebra::Vector::operator-(...), vector size mismatch");
			}
			Vector<T> result(size);
			for (size_t ii = 0; ii < size; ++ii) {
				T prod = elements[ii] * other.elements[ii];
				result.elements[ii] = prod;
				result.mag += prod * prod;
			}
			result.mag = (T)std::sqrt(result.mag);
			return result;
		}
		Vector<T>& operator*=(const Vector<T>& other) {
			*this = *this * other;
			return *this;
		}

		//sum of all elements
		T Sum() const {
			T sum = (T)0;
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