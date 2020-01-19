#include "pch.h"
#include "Vector.hpp"
#include <exception>

TEST(TestVector, TestSumIsCorrect) {
    LinearAlgebra::Vector<int> vec({ 1, 2, 3 });
    EXPECT_EQ(6, vec.Sum());
    LinearAlgebra::Vector<float> vecf({ 1.0f, 2.0f, 3.0f });
    EXPECT_EQ(6.0f, vecf.Sum());
}

TEST(TestVector, TestSumIsCorrectAfterMoveConstruction) {
    LinearAlgebra::Vector<int> vec1({ 1, 2, 3 });
    LinearAlgebra::Vector<int> vec2(std::move(vec1));
    EXPECT_EQ(6, vec2.Sum());
    LinearAlgebra::Vector<float> vec1f({ 1.0f, 2.0f, 3.0f });
    LinearAlgebra::Vector<float> vec2f(std::move(vec1f));
    EXPECT_EQ(6.0f, vec2f.Sum());
}

TEST(TestVector, TestSumIsCorrectAfterMoveAssignment) {
    LinearAlgebra::Vector<int> vec1({ 3, 1, 2, 3, 4 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 3 });
    vec1 = std::move(vec2);
    EXPECT_EQ(6, vec1.Sum());
}

TEST(TestVector, TestEquality) {
    LinearAlgebra::Vector<int> vec1({ 1, 2, 3 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 3 });
    EXPECT_EQ(vec1, vec2);
}

TEST(TestVector, TestInequality) {
    LinearAlgebra::Vector<int> vec1({ 1, 2, 3 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 2 });
    EXPECT_NE(vec1, vec2);
}

TEST(TestVector, TestDotThrowsRuntimeExceptionOnSizeMismatch) {
    LinearAlgebra::Vector<int> vec1({ 3, 1, 2, 3, 4 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 3 });
    EXPECT_THROW(vec1.Dot(vec2), std::runtime_error);
}

TEST(TestVector, TestDotReturnsCorrectValue) {
    LinearAlgebra::Vector<int> vec1({ 3, 1, 2 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 3 });
    EXPECT_EQ(11, vec1.Dot(vec2));
}

TEST(TestVector, TestDiffReturnsCorrectVector) {
    LinearAlgebra::Vector<int> vec1({ 3, 1, 2 });
    LinearAlgebra::Vector<int> vec2({ 1, 2, 3 });
    LinearAlgebra::Vector<int> vec3({ 2, -1, -1});
    EXPECT_EQ(vec3, vec1 - vec2);
}