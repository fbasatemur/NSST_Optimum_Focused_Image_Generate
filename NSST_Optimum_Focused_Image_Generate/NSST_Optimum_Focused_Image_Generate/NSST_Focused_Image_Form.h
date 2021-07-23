#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "Image.h"
#include "Process.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>

#include "ShearParameters.h"
#include "Container.h"
#include "NsstDec.h"
#include "NsstRec.h"
#include "MatlabFuncs.h"
#include "NSSTFuncs.h"

#define RANGE0255(a) (a < 0 ? 0 : ((a > 255) ? 255 : a))

namespace NSST_Focused_Image_Form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class NSST_Focused_Image_Form : public System::Windows::Forms::Form
	{
	public:
		NSST_Focused_Image_Form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NSST_Focused_Image_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ labelPath;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelPath = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"bmp files (*.bmp)|*.bmp";
			this->openFileDialog1->Multiselect = true;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1050, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem1 });
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->openToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem1
			// 
			this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			this->openToolStripMenuItem1->Size = System::Drawing::Size(128, 26);
			this->openToolStripMenuItem1->Text = L"Open";
			this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &NSST_Focused_Image_Form::openToolStripMenuItem1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 82);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 500);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(528, 82);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(500, 500);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Path:";
			// 
			// labelPath
			// 
			this->labelPath->AutoSize = true;
			this->labelPath->Location = System::Drawing::Point(60, 32);
			this->labelPath->Name = L"labelPath";
			this->labelPath->Size = System::Drawing::Size(20, 17);
			this->labelPath->TabIndex = 4;
			this->labelPath->Text = L"...";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(143, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"First image in dataset";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(525, 59);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 17);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Generated image";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1050, 600);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->labelPath);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"NSST Optimum Focused Image Generate";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			long size;
			BYTE* buffer;
			int width, height;
			const char* lpfilt = "maxflat";

			ShearParameters shearParameters;
			shearParameters.dcompSize = 4;				// K => numbers of YFK
			shearParameters.dcomp = new int[4]{ 3, 3, 4, 4 };
			shearParameters.dsize = new int[4]{ 32, 32, 16, 16 };

			int selectedImages = openFileDialog1->FileNames->GetLength(0);

			int imageSize, * maxX, * maxY;
			float* IXYBuffer;

			Matrix* image;
			Cont* dst = new Cont;
			Cont* coefficients;
			int* depths = new int[5]{ 1, 8, 8, 16, 16 };


			// Low and High Frequences Coefficients -- 2D Laplacian Pyramid filters
			Cont* filters = AtrousFilters(lpfilt);

			// New filter coefficients are obtained	-- Only once -- Optional
			/*filters->mats[1] = Conv2(filters->mats[1], filters->mats[0], "same");
			filters->mats[3] = Conv2(filters->mats[3], filters->mats[2], "same");*/


			Matrix** shearFilterMyer = new Matrix * [shearParameters.dcompSize];
			for (int i = 0; i < shearParameters.dcompSize; i++)
				shearFilterMyer[i] = ShearingFiltersMyer(shearParameters.dsize[i], shearParameters.dcomp[i]);


			for (int imgIndex = 0; imgIndex < selectedImages; imgIndex++)
			{
				CString path = openFileDialog1->FileNames[imgIndex];

				// LoadBMP can read only 24 bit image depth
				buffer = LoadBMP(width, height, size, (LPCTSTR)path);
				// return [intensity, X, Y]
				IXYBuffer = ConvertBMPToYCbCr(buffer, width, height);
				/* INFO
					IXYBuffer[0..imageSize]				=> Intensity
					IXYBuffer[imageSize..2*imageSize]	=> X (Cb)
					IXYBuffer[2*imageSize..3*imageSize] => Y (Cr)
				*/

				// Only once initialize
				if (imgIndex == 0) {

					imageSize = width * height;

					image = new Matrix(height, width, 1);
					maxX = new int[imageSize]();		// "Fuzyon Secme Kurali 2" will apply for X. Result will storage in maxX
					maxY = new int[imageSize]();		// "Fuzyon Secme Kurali 2" will apply for Y. Result will storage in maxY

					coefficients = new Cont(5);			// "Fuzyon Secme Kurali 1" will apply for dst. Results will storage in coefficients
					for (int i = 0; i < 5; i++)
					{
						coefficients->CreateCells(i, depths[i]);

						for (int d = 0; d < depths[i]; d++)
						{
							coefficients->mats[i][d].CreateMatrix(height, width, 1);
						}
					}
				}

				// "Fuzyon Secme Kurali 2" is applying for X and Y
				for (int i = 0; i < imageSize; i++)
				{
					if (abs(IXYBuffer[i + imageSize]) > abs(maxX[i])) {
						maxX[i] = (int)IXYBuffer[i + imageSize];			// Cb => X
					}
					if (abs(IXYBuffer[i + imageSize * 2]) > abs(maxY[i])) {
						maxY[i] = (int)IXYBuffer[i + imageSize * 2];		// Cr => Y
					}
				}

				image->mat = IXYBuffer;										// I => Intensity

				// NSST - Non Subsampled Shearlet Transform
				dst = NsstDec1e(image, shearParameters, filters, shearFilterMyer);
				/*	INFO
					dst->mats[cellIndex][deepIndex]
					dst->mats[0][0]			=> AFK is 1 piece and deep	 => 1
					dst->mats[1..4][deep]	=> YFK is 4 pieces and deeps => {8, 8, 16, 16}
				*/


				// AFK => "Fuzyon Secme Kurali 1" - step 1
				for (int i = 0; i < imageSize; i++)
					coefficients->mats[0][0].mat[i] += dst->mats[0][0].mat[i];

				coefficients->mats[0]->depth = depths[0];

				// YFK => "Fuzyon Secme Kurali 2"
				for (int k = 1; k < 5; k++)
				{
					coefficients->mats[k]->depth = depths[k];

					for (int d = 0; d < depths[k]; d++)
						for (int i = 0; i < imageSize; i++)
							if (abs(dst->mats[k][d].mat[i]) > abs(coefficients->mats[k][d].mat[i]))
								coefficients->mats[k][d].mat[i] = dst->mats[k][d].mat[i];
				}

				delete[] buffer;
				delete[] IXYBuffer;
				delete dst;
			}

			// AFK => "Fuzyon Secme Kurali 1" - step 2
			for (int i = 0; i < imageSize; i++)
				coefficients->mats[0][0].mat[i] /= float(selectedImages);

			// Inverse NSST
			Matrix* inverseNSST = NsstRec1(coefficients, filters);

			// display result
			Bitmap^ surface2 = gcnew Bitmap(width, height);
			pictureBox2->Image = surface2;					// focused image
			Color c2;

			int red, green, blue;
			float* intensity = inverseNSST->mat;
			int* Cb = maxX;
			int* Cr = maxY;

			long pos;
			for (int row = 0; row < height; row++)
				for (int col = 0; col < width; col++) {

					pos = row * width + col;

					intensity[pos] -= 16.0F;
					Cb[pos] -= 128;
					Cr[pos] -= 128;

					// Convert YCbCr to RGB 
					red = (int)(1.164383F * intensity[pos] + 1.596026F * (float)Cr[pos]);
					green = (int)(1.164383F * intensity[pos] - 0.391762F * (float)Cb[pos] - 0.812967F * (float)Cr[pos]);
					blue = (int)(1.164383F * intensity[pos] + 2.017232F * (float)Cb[pos]);

					// JPEG Inverse YCbCr
					/*red = (int)(intensity[pos] + 1.402 * (Cr[pos] - 128));
					green = (int)(intensity[pos] - 0.344136 * (Cb[pos] - 128) - 0.714136 * (Cr[pos] - 128));
					blue = (int)(intensity[pos] + 1.772 * (Cb[pos] - 128));*/

					// only intensity
					/*red = (int)intensity[pos];
					green = (int)intensity[pos];
					blue = (int)intensity[pos];*/

					red = RANGE0255(red);
					green = RANGE0255(green);
					blue = RANGE0255(blue);

					c2 = Color::FromArgb(red, green, blue);
					surface2->SetPixel(col, row, c2);
				}

			pictureBox1->ImageLocation = openFileDialog1->FileName;
			labelPath->Text = pictureBox1->ImageLocation;


			delete[] maxX;
			delete[] maxY;
			delete inverseNSST;
			delete coefficients;
			delete[] depths;

			for (int i = 0; i < filters->matNums; i++)
				delete filters->mats[i];

			for (int i = 0; i < shearParameters.dcompSize; i++)
				delete[] shearFilterMyer[i];
			delete[] shearFilterMyer;
		}
	}
	};
}
