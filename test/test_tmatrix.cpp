#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length) {
	ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix) {
	ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length) {
	ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix) {
	TMatrix<int> m(5);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one) {
	int size = 5;
	TMatrix<int> a(size);
	
	for (int i = 0; i < 5; i++) for (int j = i; j < 5; j++)	a[i][j] = i * 10 + j;

	TMatrix<int> a1(a);
	EXPECT_EQ(a, a1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory) {
	int size = 5;
	TMatrix<int> *a;
	a = new TMatrix<int>(size);

	for (int i = 0; i < size; i++) for (int j = i; j < 5; j++) (*a)[i][j] = i + j;

	TMatrix<int> a1(*a);
	delete a;

	for (int i = 0; i < size; i++) for (int j = i; j < 5; j++) EXPECT_EQ(a1[i][j], i + j);
}

TEST(TMatrix, can_get_size) {
	TMatrix<int> a(5);

	EXPECT_EQ(5, a.GetSize());
}

TEST(TMatrix, can_set_and_get_element) {
	int size = 5;
	TMatrix<int>* a;
	a = new TMatrix<int>(size);

	for (int i = 0; i < size; i++) for (int j = i; j < 5; j++) ASSERT_NO_THROW((*a)[i][j] = i + j);

	for (int i = 0; i < size; i++) for (int j = i; j < 5; j++) EXPECT_EQ((*a)[i][j], i + j);
}

TEST(TMatrix, throws_when_set_element_with_negative_index) {
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[-1][-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index) {
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[1][5]);
}

TEST(TMatrix, can_assign_matrix_to_itself) {
	TMatrix<int> a(5);
	a[1][1] = 1;
	a[2][3] = 5;
	ASSERT_NO_THROW(a = a);
	EXPECT_EQ(a, a);
}

TEST(TMatrix, can_assign_matrices_of_equal_size) {
	int size = 4;
	TMatrix<int> a(size), a1(size);

	a[0][1] = 1;
	a1[2][2] = 3;
	ASSERT_NO_THROW(a1 = a);
	EXPECT_EQ(a1, a);
}

TEST(TMatrix, assign_operator_change_matrix_size) {
	TMatrix<int> a(5), a1(10);
	a1 = a;
	EXPECT_EQ(a1.GetSize(), a.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size) {
	int size1 = 4, size2 = 5;
	TMatrix<int> a(size1), a1(size2);
	a[1][1] = 1;
	a[2][2] = 2;
	a1[1][1] = 3;
	a1[2][2] = 5;

	ASSERT_NO_THROW(a = a1);
	EXPECT_EQ(a, a1);
}

TEST(TMatrix, compare_equal_matrices_return_true) {
	bool t;
	TMatrix<int> a(5), a1(5);
	a[1][1] = 1;
	a[2][2] = 2;
	a1[1][1] = 1;
	a1[2][2] = 2;
	t = (a == a1);
	EXPECT_EQ(true, t);
}

TEST(TMatrix, compare_matrix_with_itself_return_true) {
	bool t;
	TMatrix<int> a(5);
	a[0][0] = 1;
	a[3][3] = 5;
	t = (a == a);
	EXPECT_EQ(true, t);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal) {
	bool t;
	TMatrix<int> a(5), a1(6);
	a[1][1] = 1;
	a[2][2] = 2;
	a1[1][1] = 1;
	a1[2][2] = 2;
	t = (a == a1);
	EXPECT_EQ(false, t);
}

TEST(TMatrix, can_add_matrices_with_equal_size) {
	int size = 5;
	TMatrix<int> a(size),a1(size),res(size);
	for (int i = 0; i < size; i++) 
		for (int j = i; j < 5; j++)
		{
			a[i][j] = i + j;
			a1[i][j] = i + j;
			res[i][j] = 2 * (i + j);
		}
	ASSERT_NO_THROW(a + a1);
	EXPECT_EQ(a+a1, res);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size) {
	TMatrix<int> a1(5), a2(10);

	ASSERT_ANY_THROW(a1 + a2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size) {
	int size = 5;
	TMatrix<int> a(size), a1(size), res(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < 5; j++)
		{
			a[i][j] = 2*i + 2*j;
			a1[i][j] = i + j;
			res[i][j] = i + j;
		}
	ASSERT_NO_THROW(a - a1);
	EXPECT_EQ(a - a1, res);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size) {
	TMatrix<int> a1(5), a2(10);

	ASSERT_ANY_THROW(a1 - a2);
}
