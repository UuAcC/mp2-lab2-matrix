#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length) // 1
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector) // 2
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) // 3
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector) // 4
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) // 5
{
	TDynamicVector<int> v(10); v[3] = 45;
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) // 6
{
	TDynamicVector<int> v(10); v[3] = 45;
	TDynamicVector<int> v1(v);
	EXPECT_NE(v.get_pMem(), v1.get_pMem());
}

TEST(TDynamicVector, can_get_size) // 7
{
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) // 8
{
  TDynamicVector<int> v(4);
  v[0] = 4;
  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) // 9
{
	TDynamicVector<int> m(5);
	EXPECT_ANY_THROW(m[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) // 10
{
	TDynamicVector<int> m(5);
	EXPECT_ANY_THROW(m[3254625373467]);
}

TEST(TDynamicVector, can_assign_vector_to_itself) // 11
{
	TDynamicVector<int> m(5); m[0] = 43;
	EXPECT_NO_THROW(m = m);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) // 12
{
	TDynamicVector<int> m(5); m[0] = 43;
	TDynamicVector<int> m1(5);
	EXPECT_NO_THROW(m1 = m);
}

TEST(TDynamicVector, assign_operator_change_vector_size) // 13
{
	TDynamicVector<int> m(5); 
	TDynamicVector<int> m1(457); m1[32] = 43;
	m = m1;
	EXPECT_EQ(457, m.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) // 14
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(457); m1[32] = 43;
	EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) // 15
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(457); m1[32] = 43;
	m = m1;
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) // 16
{
	TDynamicVector<int> m(5);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) // 17
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(457);
	EXPECT_FALSE(m == m1);
}

TEST(TDynamicVector, can_add_scalar_to_vector) // 18
{
	TDynamicVector<int> m(5);
	m += 1;
	EXPECT_EQ(1, m[0]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) // 19
{
	TDynamicVector<int> m(5); m += 7;
	m -= 1;
	EXPECT_EQ(6, m[0]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)  // 20
{
	TDynamicVector<int> m(5); m += 7;
	m *= 46;
	EXPECT_EQ(46 * 7, m[0]);
	EXPECT_EQ(46 * 7, m[3]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) // 21
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(5); m1[0] = 46; m1[3] = 43;
	m += m1;
	EXPECT_EQ(53, m[0]);
	EXPECT_EQ(7, m[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) // 22
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(457); m1[0] = 46; m1[3] = 43;
	EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) // 23
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(5); m1[0] = 46; m1[3] = 43;
	m -= m1;
	EXPECT_EQ(-39, m[0]);
	EXPECT_EQ(7, m[1]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) // 24
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(457); m1[0] = 46; m1[3] = 43;
	EXPECT_ANY_THROW(m - m1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) // 25
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(5); m1[0] = 46; m1[3] = 43;
	int res = m * m1;
	EXPECT_EQ(623, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) // 26
{
	TDynamicVector<int> m(5); m += 7;
	TDynamicVector<int> m1(457); m1[0] = 46; m1[3] = 43;
	EXPECT_ANY_THROW(m * m1);
}

