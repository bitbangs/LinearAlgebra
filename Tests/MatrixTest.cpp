#include "pch.h"
#include "Matrix.hpp"

TEST(MatrixTest, TestEquality) {
	LinearAlgebra::Matrix<int> mat1(2);
	LinearAlgebra::Matrix<int> mat2(2);
	EXPECT_EQ(mat1, mat2);
	LinearAlgebra::Matrix<int> mat3({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 7
	});
	LinearAlgebra::Matrix<int> mat4({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 7
	});
	EXPECT_EQ(mat3, mat4);
}

TEST(MatrixTest, TestInequality) {
	LinearAlgebra::Matrix<int> mat1(2);
	LinearAlgebra::Matrix<int> mat2(3);
	EXPECT_NE(mat1, mat2);
	LinearAlgebra::Matrix<int> mat3({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 7
	});
	LinearAlgebra::Matrix<int> mat4({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 9
	});
	EXPECT_NE(mat3, mat4);
}

TEST(MatrixTest, TestEqualityAfterMoveConstruction) {
	LinearAlgebra::Matrix<int> mat1({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 7
	});
	LinearAlgebra::Matrix<int> mat2({
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 2, 3,
		4, 5, 6, 7
	});
	LinearAlgebra::Matrix<int> mat3(std::move(mat2));
	EXPECT_EQ(mat1, mat3);
}

TEST(MatrixTest, TestMultiplyOfZeroMatsReturnsZeroMat) {
	LinearAlgebra::Matrix<int> mat1(4);
	LinearAlgebra::Matrix<int> mat2(4);
	LinearAlgebra::Matrix<int> mat3 = mat1 * mat2;
	EXPECT_EQ(mat1, mat3);
}

TEST(MatrixTest, TestMultiplyOfIdentityMatsReturnsIdentityMat) {
	LinearAlgebra::Matrix<int> mat1({
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	});
	LinearAlgebra::Matrix<int> mat2({
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	});
	LinearAlgebra::Matrix<int> mat3 = mat1 * mat2;
	EXPECT_EQ(mat1, mat3);
	LinearAlgebra::Matrix<float> mat4({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	});
	LinearAlgebra::Matrix<float> mat5({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	});
	LinearAlgebra::Matrix<float> mat6 = mat4 * mat5;
	EXPECT_EQ(mat4, mat6);
}

