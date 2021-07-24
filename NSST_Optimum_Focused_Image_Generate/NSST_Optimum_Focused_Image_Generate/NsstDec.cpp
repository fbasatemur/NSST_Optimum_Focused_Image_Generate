#pragma once
#include <math.h>
#include "NsstDec.h"
#include "MatlabFuncs.h"
#include "NSSTFuncs.h"
#include "FFT_Conv2D.h"


/// <summary>
///		This function computes the(local) nonsubsampled shearlet transform as given
/// </summary>
/// <param name="image"> 
///		input image 
/// </param>
/// <param name="shearParam">
///		shear_parameters.dcomp - a vector such that.dcomp(i) indicates that the
/// 	ith decomposition level has 2 ^ decomp(i)
/// 	directions.The length of the vector plus 1 is
/// 	total the number of decompostions.
/// </param>
/// <param name="filters">
///		
/// </param>
/// <param name="shearFilters"></param>
/// <returns></returns>
Cont* NsstDec1e(Matrix* image, const ShearParameters& shearParam, Cont* filters, const Cont* shearFilters)
{
	int level = shearParam.dcompSize;

	//Laplacian Pyramid decomposition	//NSLP //cok olceklilik
	//Katsayilara gore alt-goruntuler elde edilir.
	Cont* y = AtrousDec(image, filters, level);
	Cont* dst = new Cont(level + 1);
	dst->mats[0] = y->mats[0];

	int size;
	for (int i = 0; i < level; i++)
	{
		size = (int)pow(2, shearParam.dcomp[i]);	// goruntuye uygulanacak yon sayisi belirlenir.
		dst->CreateCells(i + 1, size);

		for (int k = 0; k < size; k++) {
			//dst->mats[i + 1][k] = Conv2(y->mats[i + 1], &shearF->mats[i][k], "same");			 // Cok yonluluk - Time Domain Conv (TDC), slow
			dst->mats[i + 1][k] = FFTConv2D(y->mats[i + 1], &shearFilters->mats[i][k], "same");	 // Cok yonluluk - Frequency Domain Conv, faster than TDC
		}
		dst->mats[i + 1]->depth = size;
	}

	int depth;
	for (int cell = 1; cell < 5; cell++) {

		depth = y->mats[cell]->depth;
		for (int d = 0; d < depth; d++)
			delete[] y->mats[cell][d].mat;
	}

	return dst;
}
