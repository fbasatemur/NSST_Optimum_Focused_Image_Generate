#include "NSST_Focused_Image_Form.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	NSST_Focused_Image_Form::NSST_Focused_Image_Form form;
	Application::Run(%form);
}