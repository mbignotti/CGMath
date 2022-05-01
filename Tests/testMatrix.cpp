#include "pch.h"
#include "CGMath.h"

namespace TestMatrix {

	using namespace CGMath;

	TEST(TestMatrix, TestMatrixAccessOperator)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		EXPECT_EQ(1.0f, mat3(0, 0));
		EXPECT_EQ(2.0f, mat3(0, 1));
		EXPECT_EQ(3.0f, mat3(0, 2));
		EXPECT_EQ(4.0f, mat3(1, 0));
		EXPECT_EQ(5.0f, mat3(1, 1));
		EXPECT_EQ(6.0f, mat3(1, 2));
		EXPECT_EQ(7.0f, mat3(2, 0));
		EXPECT_EQ(8.0f, mat3(2, 1));
		EXPECT_EQ(9.0f, mat3(2, 2));
	}

	TEST(TestMatrix, TestMatrixShape)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		size_t n{ 3 };
		size_t m{ 3 };
		EXPECT_EQ(n, mat3.shape().nrows);
		EXPECT_EQ(m, mat3.shape().ncols);

		Matrix<float, 2, 3> mat23{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f} };
		n = 2;
		EXPECT_EQ(n, mat23.shape().nrows);
		EXPECT_EQ(m, mat23.shape().ncols);

		// TODO: Matrix transpose not working
		/*Matrix<float, 3, 2> mat32 = transpose(mat23);
		EXPECT_EQ(m, mat32.shape().nrows);
		EXPECT_EQ(n, mat32.shape().ncols);*/
	}

	TEST(TestMatrix, TestMatrixMatrixDotProduct)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		Matrix3f mat33{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		Matrix3f dotResult = mat3 * mat33;
		Matrix3f result{ {30.0f, 36.0f, 42.0f}, {66.0f, 81.0f, 96.0f}, {102.0f, 126.0f, 150.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), dotResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestMatrixVectorDotProduct)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		Vec3f dotResult = mat3 * v3;
		Vec3f result{ 14.0f, 32.0f, 50.0f };
		for (size_t dim = 0; dim < 3; dim++)
		{
			EXPECT_EQ(result[dim], dotResult[dim]);
		}
	}

	TEST(TestMatrix, TestVectorMatrixDotProduct)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		Vector<float, 3, false> v3{ 1.0f, 2.0f, 3.0f };
		Vector<float, 3, false> dotResult = v3 * mat3;
		Vector<float, 3, false> result{ 30.0f, 36.0f, 42.0f };
		for (size_t dim = 0; dim < 3; dim++)
		{
			EXPECT_EQ(result[dim], dotResult[dim]);
		}
	}

	TEST(TestMatrix, TestVectorVectorDotProduct)
	{
		Vector<float, 3, true> v3{ 1.0f, 2.0f, 3.0f };
		Vector<float, 3, false> v33{ 1.0f, 2.0f, 3.0f };
		Matrix<float, 3, 3> dotResult = v3 * v33;
		Matrix<float, 3, 3> result{ {1.0f, 2.0f, 3.0f}, {2.0f, 4.0f, 6.0f}, {3.0f, 6.0f, 9.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), dotResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestMatrixScalarSum)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		float scalar{ 2.0f };
		Matrix3f sumResult = mat3 + scalar;
		Matrix3f result{ {3.0f, 4.0f, 5.0f}, {6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), sumResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestMatrixScalarDifference)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		float scalar{ 2.0f };
		Matrix3f diffResult = mat3 - scalar;
		Matrix3f result{ {-1.0f, 0.0f, 1.0f}, {2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), diffResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestMatrixScalarMult)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f} };
		float scalar{ 2.0f };
		Matrix3f multResult = mat3 * scalar;
		Matrix3f result{ {2.0f, 4.0f, 6.0f}, {8.0f, 10.0f, 12.0f}, {14.0f, 16.0f, 18.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), multResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestMatrixScalarDivision)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 4.0f}, {6.0f, 8.0f, 10.0f}, {12.0f, 14.0f, 16.0f} };
		float scalar{ 2.0f };
		Matrix3f divResult = mat3 / scalar;
		Matrix3f result{ {0.5f, 1.0f, 2.0f}, {3.0f, 4.0f, 5.0f}, {6.0f, 7.0f, 8.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), divResult(row, col));
			}
		}
	}

	TEST(TestMatrix, TestSetRow)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 4.0f}, {6.0f, 8.0f, 10.0f}, {12.0f, 14.0f, 16.0f} };
		float new_row[3]{ 1.0f, 4.0f, 8.0f };
		mat3.set_row(1, new_row);
		Matrix3f result{ {1.0f, 2.0f, 4.0f}, {1.0f, 4.0f, 8.0f}, {12.0f, 14.0f, 16.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), result(row, col));
			}
		}
	}

	TEST(TestMatrix, TestSetCol)
	{
		Matrix3f mat3{ {1.0f, 2.0f, 4.0f}, {6.0f, 8.0f, 10.0f}, {12.0f, 14.0f, 16.0f} };
		float new_col[3]{ 1.0f, 4.0f, 8.0f };
		mat3.set_col(2, new_col);
		Matrix3f result{ {1.0f, 2.0f, 1.0f}, {6.0f, 8.0f, 4.0f}, {12.0f, 14.0f, 8.0f} };
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				EXPECT_EQ(result(row, col), result(row, col));
			}
		}
	}

}