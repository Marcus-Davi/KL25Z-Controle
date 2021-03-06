/*
 * Matrix.h
 *
 *  Created on: 25 de set de 2019
 *      Author: marcus
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "arm_math.h"
#include "stdint.h"
#include "fsl_debug_console.h" //PRITNF

class Matrix {
public:
	Matrix(int lines,int columns);
	Matrix(int lines,int columns,float* data);
	void SetValue(int i,int j,float value);
	void SetValues(const float* values);
	void Print();
	static void Copy(Matrix const& A,Matrix &B);

	virtual ~Matrix();


	static arm_status Add(Matrix const& A,Matrix const&B,Matrix &Res);
	static arm_status Sub(Matrix const& A,Matrix const&B,Matrix &Res);
	static arm_status Mult(Matrix const& A,Matrix const&B,Matrix &Res);
	static arm_status Scale(Matrix const& A,Matrix &B,float k);
	static arm_status Transpose(Matrix const& A,Matrix &Res);
	static arm_status Inverse(Matrix const& A,Matrix &Res);

private:

	void deuRuim();

	uint8_t rows;
	uint8_t columns;
	float* data;
	arm_matrix_instance_f32 M;
};

//o acesso elementar eh feito em forma de array 1D, mapeando em [Ncol*lin + col], onde col e lin sao iteradores, Ncol eh o numero de colunas
//da matriz partindo do 0. ==> A(i,j) = A[Ncol*i + j].

//typedef enum
//{
//  ARM_MATH_SUCCESS = 0,                /**< No error */
//  ARM_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
//  ARM_MATH_LENGTH_ERROR = -2,          /**< Length of data buffer is incorrect */
//  ARM_MATH_SIZE_MISMATCH = -3,         /**< Size of matrices is not compatible with the operation. */
//  ARM_MATH_NANINF = -4,                /**< Not-a-number (NaN) or infinity is generated */
//  ARM_MATH_SINGULAR = -5,              /**< Generated by matrix inversion if the input matrix is singular and cannot be inverted. */
//  ARM_MATH_TEST_FAILURE = -6           /**< Test Failed  */
//} arm_status;


#endif /* MATRIX_H_ */
