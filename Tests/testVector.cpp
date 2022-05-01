#include "pch.h"
#include "CGMath.h"

namespace TestVector {

	using namespace CGMath;

	TEST(TestVector, TestVectorAccessOperator)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(1.0f, v3[0]);
		EXPECT_EQ(2.0f, v3[1]);
		EXPECT_EQ(3.0f, v3[2]);
	}

	TEST(TestVector, TestVectorSize)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(3, v3.size());
	}

	TEST(TestVector, TestVectorShape)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		size_t n{ 1 };
		size_t m{ 3 };
		EXPECT_EQ(m, v3.shape().nrows);
		EXPECT_EQ(n, v3.shape().ncols);

		Vector<float, 3, false> v3t;
		v3t = transpose(v3);
		EXPECT_EQ(n, v3t.shape().nrows);
		EXPECT_EQ(m, v3t.shape().ncols);
	}

	TEST(TestVector, TestVectorSum)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(6.0f, sum(v3));
	}

	TEST(TestVector, TestVectorNorm2)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(14.0f, v3.norm2());
	}

	TEST(TestVector, TestVectorNorm)
	{
		Vec3f v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(std::sqrt(14.0f), v3.norm());
	}

	TEST(TestVector, TestDotProduct)
	{
		Vec4f v4(2.0f);
		Vec4f v44(2.0f);
		EXPECT_EQ(16.0f, dot(v4, v44));
	}

	TEST(TestVector, TestCrossProduct)
	{
		Vec3f v3{ 1, 2, 3 };
		Vec3f v33(2.0f);
		Vec3f crossvec = cross(v3, v33);
		Vec3f result{ -2, 4, -2 };
		for (size_t i = 0; i < v3.size(); i++)
		{
			EXPECT_EQ(result[i], crossvec[i]);
		}
	}

	TEST(TestVector, TestVectorNormalizedInPlace)
	{
		Vec4f v4(2.0f);
		v4.normalized();
		Vec4f v4Norm(0.5f);
		EXPECT_TRUE((v4 == v4Norm));
	}

	TEST(TestVector, TestVectorNormalizedCopy)
	{
		Vec4f v4(2.0f);
		Vec4f v4Norm(0.5f);
		EXPECT_TRUE((normalize(v4) == v4Norm));
	}

	TEST(TestVector, TestVectorVectorSum)
	{
		Vec3f v3(3.0f);
		Vec3f v33(2.0f);
		Vec3f v3sum(5.0f);
		Vec3f v3summed = v3 + v33;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorScalarSum)
	{
		Vec3f v3(3.0f);
		float scalar{ 2.0f };
		Vec3f v3sum(5.0f);
		Vec3f v3summed = v3 + scalar;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorVectorDifference)
	{
		Vec3f v3(3.0f);
		Vec3f v33(2.0f);
		Vec3f v3sum(1.0f);
		Vec3f v3summed = v3 - v33;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorScalarDifference)
	{
		Vec3f v3(3.0f);
		float scalar{ 2.0f };
		Vec3f v3sum(1.0f);
		Vec3f v3summed = v3 - scalar;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorVectorMult)
	{
		Vec3f v3(3.0f);
		Vec3f v33(2.0f);
		Vec3f v3sum(6.0f);
		Vec3f v3summed = v3 * v33;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorScalarMult)
	{
		Vec3f v3(3.0f);
		float scalar{ 2.0f };
		Vec3f v3sum(6.0f);
		Vec3f v3summed = v3 * scalar;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorVectorDiv)
	{
		Vec3f v3(4.0f);
		Vec3f v33(2.0f);
		Vec3f v3sum(2.0f);
		Vec3f v3summed = v3 / v33;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorScalarDiv)
	{
		Vec3f v3(4.0f);
		float scalar{ 2.0f };
		Vec3f v3sum(2.0f);
		Vec3f v3summed = v3 / scalar;
		for (size_t i = 0; i < v3sum.size(); i++)
		{
			EXPECT_EQ(v3sum[i], v3summed[i]);
		}
	}

	TEST(TestVector, TestVectorVectorComparison)
	{
		Vec3f v3(3.0f);
		Vec3f v33{ 1, 2, 3 };
		Vec3f v333(3.0f);
		EXPECT_FALSE(v3 == v33);
		EXPECT_TRUE(v3 == v333);
	}

	TEST(TestVector, TestVectorScalarComparison)
	{
		Vec3f v3(3.0f);
		float x{ 1 };
		float y{ 3 };
		EXPECT_TRUE(any((v3 == y)));
		EXPECT_TRUE(all(v3 == y));
		EXPECT_FALSE(any(v3 == x));
		EXPECT_FALSE(all(v3 == x));
	}

} // namespace
