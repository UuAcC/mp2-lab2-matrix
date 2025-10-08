#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) // 1
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) // 2
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) // 3
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) // 4
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) // 5
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) // 6
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	EXPECT_NE(m.get_pMem(), m1.get_pMem());
}

TEST(TDynamicMatrix, can_get_size) // 7
{
	int size = 71;
	TDynamicMatrix<int> m(size);

	EXPECT_EQ(m.size(), size);
}

TEST(TDynamicMatrix, can_set_and_get_element) // 8
{
	int size = 71, a = 5431;
	TDynamicMatrix<int> m(size);

	m[0][0] = a;
	EXPECT_EQ(a, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) // 9
{
  TDynamicMatrix<int> m(5);
  EXPECT_ANY_THROW(m[0][-1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) // 10
{
	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW(m[1000][0]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) // 11
{
	TDynamicMatrix<int> m(5);
	EXPECT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) // 12
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) // 13
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(457);
	m = m1;
	size_t sm = m.size(), sm1 = m1.size();
	EXPECT_EQ(sm1, sm);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) // 14
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(457);
	EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) // 15
{
	TDynamicMatrix<int> m(5);
	m[0][4] = 23; m[1][3] = 5;
	TDynamicMatrix<int> m1(m);
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	ADD_FAILURE();
}

