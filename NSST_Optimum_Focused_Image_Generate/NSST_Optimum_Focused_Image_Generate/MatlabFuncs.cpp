#include <string.h>		//for strcmp
#include "MatlabFuncs.h"
#include <cmath>
#include "Process.h"
#include <algorithm>

float Realmod(float x, float y)
{
	float result = fmod(x, y);
	return result >= 0 ? result : result + y;
}

Matrix* Sum(Matrix* mats, int dim) {

	int imageSize = mats->GetSize2D();
	Matrix* retMat = new Matrix;
	retMat->CreateMatrix(mats->height, mats->width, 1);

	if (dim == 3) {

		float total = 0.0F;
		for (int i = 0; i < imageSize; i++)
		{
			total = 0.0;
			for (int d = 0; d < mats->depth; d++)
				total += mats[d].mat[i];
			retMat->mat[i] = total;
		}
	}

	else exit(1);

	return retMat;
}

float* Eye(int size) {

	float* identityMat = new float[size * size]();

	// If row == col then set 1.0
	for (int i = 0; i < size; i++)
		identityMat[i * size + i] = 1.0F;

	return identityMat;
}

Matrix* EyeMatrix(int size) {

	Matrix* identityMat = new Matrix;
	identityMat->CreateMatrix(size, size, 1);		// zero matrix

	// If row == col then set 1.0
	for (int i = 0; i < size; i++)
		identityMat->mat[i * size + i] = 1.0F;

	return identityMat;
}

float* Ones(int width, int height)
{
	float* onesMat = new float[width * height];
	std::fill_n(onesMat, width * height, 1.0F);

	return onesMat;
}

float* Zeros(int width, int height, int depth)
{
	return new float[width * height * depth]();
}

Matrix* Conv2(Matrix* image, const Matrix* kernel, char* type)
{
	int outRow, outCol, edgeRows, edgeCols;

	if (!strcmp(type, "full"))
	{
		outRow = image->height + kernel->height - 1;
		outCol = image->width + kernel->width - 1;
		edgeRows = kernel->height - 1;
		edgeCols = kernel->width - 1;
	}
	else if (!strcmp(type, "same"))
	{
		outRow = image->height;
		outCol = image->width;
		edgeRows = (kernel->height - 1) / 2;
		edgeCols = (kernel->width - 1) / 2;
	}
	else if (!strcmp(type, "valid"))
	{
		outRow = image->height - kernel->height + 1;
		outCol = image->width - kernel->width + 1;
		edgeRows = edgeCols = 0;
	}
	else
	{
		return (Matrix*)-1;
	}

	Matrix* outMat = new Matrix;
	outMat->CreateMatrix(outRow, outCol);

	int iImage, iKernel, jImage, jKernel, jKernelTemp, jImageTemp;
	float sum;

	for (int i = 0; i < outRow; i++) {
		for (int j = 0; j < outCol; j++)
		{
			sum = 0.0F;
			iKernel = kernel->height - 1 - max(0, edgeRows - i);
			iImage = max(0, i - edgeRows);
			jKernelTemp = kernel->width - 1 - max(0, edgeCols - j);
			jImageTemp = max(0, j - edgeCols);

			for (; (iKernel >= 0) && (iImage < image->height); iKernel--, iImage++)
				for (jKernel = jKernelTemp, jImage = jImageTemp; (jKernel >= 0) && (jImage < image->width); jKernel--, jImage++)
					sum += image->mat[image->width * iImage + jImage] * kernel->mat[kernel->width * iKernel + jKernel];

			outMat->mat[i * outCol + j] = sum;
		}
	}

	return outMat;
}

float* Fliplr(const float* arry, int height, int width) {

	float* returnBuffer = new float[width * height];

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			returnBuffer[row * width + width - col - 1] = arry[row * width + col];

	return returnBuffer;
}

float* Flipud(const float* arry, int height, int width) {

	float* returnBuffer = new float[width * height];

	for (int col = 0; col < width; col++)
		for (int row = 0; row < height; row++)
			returnBuffer[(height - row - 1) * width + col] = arry[row * width + col];

	return returnBuffer;
}

// mat1H and mat2H are must equie
Matrix* MatrixColExtend(float* mat1, int mat1H, int mat1W, float* mat2, int mat2H, int mat2W) {

	int extWidth = mat1W + mat2W;
	Matrix* extMatrix = new Matrix;
	extMatrix->CreateMatrix(mat1H, extWidth, 1);

	unsigned int byteM1Width = mat1W * sizeof(float);
	unsigned int byteM2Width = mat2W * sizeof(float);

	for (int row = 0; row < mat1H; row++)
	{
		memcpy((extMatrix->mat + row * extWidth), (mat1 + row * mat1W), byteM1Width);
		memcpy((extMatrix->mat + row * extWidth + mat1W), (mat2 + row * mat2W), byteM2Width);
	}

	return extMatrix;
}

// mat1W and mat2W are must equie
Matrix* MatrixRowExtend(float* mat1, int mat1H, int mat1W, float* mat2, int mat2H, int mat2W) {

	int extHeight = mat1H + mat2H;
	Matrix* extMatrix = new Matrix;
	extMatrix->CreateMatrix(extHeight, mat1W, 1);

	for (int col = 0; col < mat1W; col++)
	{
		for (int row = 0; row < mat1H; row++)
			extMatrix->mat[row * mat1W + col] = mat1[row * mat1W + col];

		for (int row = mat1H; row < extHeight; row++)
			extMatrix->mat[row * mat1W + col] = mat2[(row - (mat1H)) * mat1W + col];
	}

	return extMatrix;
}

Matrix* MatrixCut(const float* mat, int height, int width, int rowStartIndex, int rowEndIndex, int colStartIndex, int colEndIndex) {

	int cutHeight = rowEndIndex - rowStartIndex + 1;
	int cutWidth = colEndIndex - colStartIndex + 1;

	Matrix* cutMatrix = new Matrix;
	cutMatrix->CreateMatrix(cutHeight, cutWidth, 1);
	unsigned int byteCutWidth = cutWidth * sizeof(*mat);

	for (int row = rowStartIndex; row <= rowEndIndex; row++)
		memcpy((cutMatrix->mat + (row - rowStartIndex) * cutWidth), (mat + row * width + colStartIndex), byteCutWidth);

	return cutMatrix;
}

Matrix* MatrixCut(const float* mat, int height, int width, int rowStartIndex, int rowEndIndex, int colStartIndex, int colEndIndex, int rowStep, int colStep) {

	int cutHeight, cutWidth;
	Matrix* cutMatrix = new Matrix;

	//-,-
	if ((rowStep < 0 && rowStartIndex >= rowEndIndex) && (colStep < 0 && colStartIndex >= colEndIndex)) {
		cutHeight = rowStartIndex - rowEndIndex + 1;
		cutWidth = colStartIndex - colEndIndex + 1;
		cutMatrix->CreateMatrix(cutHeight, cutWidth, 1);
		for (int row = rowStartIndex; row >= rowEndIndex; row += rowStep)
			for (int col = colStartIndex; col >= colEndIndex; col += colStep)
				cutMatrix->mat[(rowStartIndex - row) * cutWidth + (colStartIndex - col)] = mat[row * width + col];
	}
	//-,+
	else if ((rowStep < 0 && rowStartIndex >= rowEndIndex) && (colStep > 0 && colStartIndex <= colEndIndex)) {
		cutHeight = rowStartIndex - rowEndIndex + 1;
		cutWidth = colEndIndex - colStartIndex + 1;
		cutMatrix->CreateMatrix(cutHeight, cutWidth, 1);
		for (int row = rowStartIndex; row >= rowEndIndex; row += rowStep)
			for (int col = colStartIndex; col <= colEndIndex; col += colStep)
				cutMatrix->mat[(rowStartIndex - row) * cutWidth + col] = mat[row * width + col];
	}
	//+,-
	else if ((rowStep > 0 && rowStartIndex <= rowEndIndex) && (colStep < 0 && colStartIndex >= colEndIndex)) {
		cutHeight = rowEndIndex - rowStartIndex + 1;
		cutWidth = colStartIndex - colEndIndex + 1;
		cutMatrix->CreateMatrix(cutHeight, cutWidth, 1);
		for (int row = rowStartIndex; row <= rowEndIndex; row += rowStep)
			for (int col = colStartIndex; col >= colEndIndex; col += colStep)
				cutMatrix->mat[row * cutWidth + (colStartIndex - col)] = mat[row * width + col];
	}
	//+,+
	else if ((rowStep > 0 && rowStartIndex <= rowEndIndex) && (colStep > 0 && colStartIndex <= colEndIndex)) {
		cutHeight = rowEndIndex - rowStartIndex + 1;
		cutWidth = colEndIndex - colStartIndex + 1;
		cutMatrix->CreateMatrix(cutHeight, cutWidth, 1);
		for (int row = rowStartIndex; row <= rowEndIndex; row += rowStep)
			for (int col = colStartIndex; col <= colEndIndex; col += colStep)
				cutMatrix->mat[row * cutWidth + col] = mat[row * width + col];
	}
	return cutMatrix;
}

float* ScalarMatMul(float* mat1, int matSize, float scalarValue)
{
	float* mat2 = new float[matSize]();

	for (int i = 0; i < matSize; i++)
		mat2[i] = mat1[i] * scalarValue;

	return mat2;
}

Matrix* ScalarMatMul(Matrix& matx, float scalarValue)
{
	Matrix* ret = new Matrix(matx.height, matx.width, matx.depth);
	ret->mat = ScalarMatMul(matx.mat, matx.GetSize3D(), scalarValue);
	return ret;
}

float* RDivide(float* mat, float* rMat, int size)
{
	float* retMat = new float[size];

	for (int i = 0; i < size; i++)
		retMat[i] = mat[i] / rMat[i];

	return retMat;
}

float* MatrixMultiplication(float* m1, int row1, int col1, float* m2, int row2, int col2)
{
	if (col1 != row2)
		exit(1);

	float* m3 = new float[row1 * col2];
	float sum;

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			sum = 0.0F;
			for (int k = 0; k < col1; k++) {
				sum += m1[i * col1 + k] * m2[k * col2 + j];
			}
			m3[i * col2 + j] = sum;
		}
	}

	return m3;
}

void Circshift(float* output, float* input, int rows, int cols, int yshift, int xshift)
{
	for (int r = 0; r < rows; r++) {

		int newR = (r + yshift) % rows;
		if (newR < 0)	newR = rows + newR;

		for (int c = 0; c < cols; c++) {

			int newC = (c + xshift) % cols;
			if (newC < 0)	newC = cols + newC;

			output[newR * cols + newC] = input[r * cols + c];
		}
	}
}

float* FFTShift2D(float* input, int width, int height) {

	float* temp = new float[width * height];

	// x = circshift(x,floor(size(x)/2));
	Circshift(temp, input, height, width, floor(height / 2), floor(width / 2));

	return temp;
}