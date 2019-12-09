#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length) {
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector) {
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length) {
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex) {
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector) {
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one){
	TVector<int> v(10);

	for (int i = 0; i < 10; i++) v[i] = i;

	TVector<int> v1(v);
	EXPECT_EQ(v,v1);
}

TEST(TVector, copied_vector_has_its_own_memory) {
	int size = 10;
	TVector<int> *v;
	v = new TVector<int>(size);

	for (int i = 0; i < size; i++) (*v)[i] = i;

	TVector<int> v1(*v);
	delete v;

	for (int i = 0; i < size; i++) EXPECT_EQ(v1[i], i);
}

TEST(TVector, can_get_size) {
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index) {
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element) {
  TVector<int> v(4);
  ASSERT_NO_THROW(v[0] = 4);

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index) {
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index) {
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[5]);
}

TEST(TVector, can_assign_vector_to_itself) {
	TVector<int> v(5);
	v[1] = 1;
	v[2] = 5;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v, v);
}

TEST(TVector, can_assign_vectors_of_equal_size) {
	 int size = 4;
	TVector<int> v1(size), v2(size);
	// v1 = {1, 3}
	v1[0] = 1;
	v1[2] = 3;
	ASSERT_NO_THROW(v2=v1);
	EXPECT_EQ(v1, v2); 
}

TEST(TVector, assign_operator_change_vector_size) {
	TVector<int> a(5),a1(10);
	a1 = a;
	EXPECT_EQ(a1.GetSize(), a.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size) {
	const int size1 = 4,size2=5;
	TVector<int> v1(size1), v2(size2);
	// v1 = {1, 3}
	v1[0] = 1;
	v1[2] = 3;
	v2 = v1;
	EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true) {
	bool a;
	TVector<int> v1(5), v2(5);
	v1[0] = 1;
	v1[3] = 5;
	v2[0] = 1;
	v2[3] = 5;
	a = (v2 == v1);
	EXPECT_EQ(true, a);
}

TEST(TVector, compare_vector_with_itself_return_true) {
	bool a;
	TVector<int> v1(5);
	v1[0] = 1;
	v1[3] = 5;
	a = (v1==v1);
	EXPECT_EQ(true, a);
}

TEST(TVector, vectors_with_different_size_are_not_equal) {
	TVector<int> v1(6), v2(5);
	v1[0] = 1;
	v1[3] = 5;
	v2[0] = 1;
	v2[3] = 5;
	EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector) {
	TVector<int> v(10),v1(v);

	for (int i = 0; i < 10; i++) v[i] = 0;

	ASSERT_NO_THROW(v = v + 5);

	for (int i = 0; i < 10; i++) v1[i] = 5;

	EXPECT_EQ(v,v1);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(10), v1(v);

	for (int i = 0; i < 10; i++) v[i] = 7;

	ASSERT_NO_THROW(v = v - 5);

	for (int i = 0; i < 10; i++) v1[i] = 2;

	EXPECT_EQ(v, v1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(10), v1(v);

	for (int i = 0; i < 10; i++) v[i] = 7;

	ASSERT_NO_THROW(v = 5*v);

	for (int i = 0; i < 10; i++) v1[i] = 35;

	EXPECT_EQ(v, v1);
}

TEST(TVector, can_add_vectors_with_equal_size) {
	TVector<int> v1(10), v2(10), v3(10), res(10);

	for (int i = 0; i < 10; i++) v1[i] = i;
	for (int i = 0; i < 10; i++) v2[i] = i;

	ASSERT_NO_THROW(res = v1 + v2);

	for (int i = 0; i < 10; i++) v3[i] = 2*i;

	EXPECT_EQ(v3, res);
}

TEST(TVector, cant_add_vectors_with_not_equal_size) {
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size) {
	TVector<int> v1(10), v2(10), v3(10), res(10);

	for (int i = 0; i < 10; i++) v1[i] = 2*i;
	for (int i = 0; i < 10; i++) v2[i] = i;

	ASSERT_NO_THROW(res = v1 - v2);

	for (int i = 0; i < 10; i++) v3[i] =  i;

	EXPECT_EQ(v3, res);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size) {
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size) {
	TVector<int> v1(5), v2(5);

	for (int i = 0; i < 5; i++) v1[i] = v2[i] = i;

	ASSERT_NO_THROW(v1 * v2);
	EXPECT_EQ(v1*v2,30);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size) {
	TVector<int> v1(5), v2(10);

	ASSERT_ANY_THROW(v1 * v2);
}

