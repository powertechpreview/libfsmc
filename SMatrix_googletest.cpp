#include "SMatrix.h"
#include <gtest/gtest.h>
#include <stdlib.h>
using namespace std;

void randMat(double data[], int tam) {
	for (int i = 0; i < tam*tam; i++)
		data[i] = rand() % 100; // random number between 0 and 99
}

// test for matrix multiplication between two 4x4 row major matrices
TEST(mul4x4, RMRM) {
	const int tam = 4;
	SMatrix<double, tam, tam> m1, m2, mref(0);

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

// test for matrix multiplication between a 4x4 column major matrix and a 4x4 row major matrix
TEST(mul4x4, CMRM) {
	const int tam = 4;
	SMatrix<double, tam, tam> m2, mref(0);
	SMatrix<double, tam, tam, ColMajor> m1;

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

// test for matrix multiplication between two 9x9 row major matrices
TEST(mul9x9, RMRM) {
	const int tam = 9;
	SMatrix<double, tam, tam> m1, m2, mref(0);

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

// test for matrix multiplication between a 9x9 column major matrix and a 9x9 row major matrix
TEST(mul9x9, CMRM) {
	const int tam = 9;
	SMatrix<double, tam, tam> m2, mref(0);
	SMatrix<double, tam, tam, ColMajor> m1;

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

// test for matrix multiplication between two 12x12 row major matrices
TEST(mul12x12, RMRM) {
	const int tam = 12;
	SMatrix<double, tam, tam> m1, m2, mref(0);

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

// test for matrix multiplication between a 12x12 column major matrix and a 12x12 row major matrix
TEST(mul12x12, CMRM) {
	const int tam = 12;
	SMatrix<double, tam, tam> m2, mref(0);
	SMatrix<double, tam, tam, ColMajor> m1;

	randMat(m1.m_data, tam);
	randMat(m2.m_data, tam);

	for(int i = 0; i < m1.m_rows; i++)
	{
		for(int j = 0; j < m2.m_cols; j++)
		{
			for(int k = 0; k < m1.m_cols; k++)
		    {
		        mref.m_data[mref.storage_order == RowMajor ? i*m2.m_cols + j : j*m1.m_rows + i] += m1.m_data[m1.storage_order == RowMajor ? i*m1.m_cols + k : k*m1.m_rows + i]*m2.m_data[m2.storage_order == RowMajor ? k*m2.m_cols + j : j*m1.m_cols + k];
			}
		}
	}

	SMatrix<double, tam, tam> mres = m1.mul<tam>(m2);
	for (int i = 0; i < tam*tam; i++)
		EXPECT_EQ(mref.m_data[i], mres.m_data[i]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
