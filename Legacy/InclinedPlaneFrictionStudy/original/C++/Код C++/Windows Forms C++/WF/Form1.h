#include "PlotPoint.h"
#include "Results.h"
#include <map>
#pragma once
using namespace System;
namespace WF {
#pragma region FORM
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  calcBtn;
	private: System::Windows::Forms::TextBox^  massTextBox;
	private: System::Windows::Forms::Label^  massLabel;
	protected:



	private: System::Windows::Forms::TextBox^  uTextBox;
	private: System::Windows::Forms::TextBox^  angleTextBox;
	private: System::Windows::Forms::Label^  uLabel;
	private: System::Windows::Forms::Label^  angleLabel;
	private: System::Windows::Forms::PictureBox^  firstPlot;





	private: System::Windows::Forms::Label^  resultLabel;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->calcBtn = (gcnew System::Windows::Forms::Button());
			this->massTextBox = (gcnew System::Windows::Forms::TextBox());
			this->massLabel = (gcnew System::Windows::Forms::Label());
			this->uTextBox = (gcnew System::Windows::Forms::TextBox());
			this->angleTextBox = (gcnew System::Windows::Forms::TextBox());
			this->uLabel = (gcnew System::Windows::Forms::Label());
			this->angleLabel = (gcnew System::Windows::Forms::Label());
			this->firstPlot = (gcnew System::Windows::Forms::PictureBox());
			this->resultLabel = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->firstPlot))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// calcBtn
			// 
			this->calcBtn->Location = System::Drawing::Point(12, 527);
			this->calcBtn->Name = L"calcBtn";
			this->calcBtn->Size = System::Drawing::Size(157, 23);
			this->calcBtn->TabIndex = 0;
			this->calcBtn->Text = L"Вычислить";
			this->calcBtn->UseVisualStyleBackColor = true;
			this->calcBtn->Click += gcnew System::EventHandler(this, &Form1::calcBtn_Click);
			// 
			// massTextBox
			// 
			this->massTextBox->Location = System::Drawing::Point(12, 42);
			this->massTextBox->Name = L"massTextBox";
			this->massTextBox->Size = System::Drawing::Size(100, 20);
			this->massTextBox->TabIndex = 1;
			this->massTextBox->Text = L"10";
			// 
			// massLabel
			// 
			this->massLabel->AutoSize = true;
			this->massLabel->Location = System::Drawing::Point(9, 26);
			this->massLabel->Name = L"massLabel";
			this->massLabel->Size = System::Drawing::Size(39, 13);
			this->massLabel->TabIndex = 2;
			this->massLabel->Text = L"масса";
			// 
			// uTextBox
			// 
			this->uTextBox->Location = System::Drawing::Point(12, 79);
			this->uTextBox->Name = L"uTextBox";
			this->uTextBox->Size = System::Drawing::Size(100, 20);
			this->uTextBox->TabIndex = 3;
			this->uTextBox->Text = L"0.5";
			// 
			// angleTextBox
			// 
			this->angleTextBox->Location = System::Drawing::Point(12, 118);
			this->angleTextBox->Name = L"angleTextBox";
			this->angleTextBox->Size = System::Drawing::Size(100, 20);
			this->angleTextBox->TabIndex = 4;
			this->angleTextBox->Text = L"30";
			// 
			// uLabel
			// 
			this->uLabel->AutoSize = true;
			this->uLabel->Location = System::Drawing::Point(9, 62);
			this->uLabel->Name = L"uLabel";
			this->uLabel->Size = System::Drawing::Size(114, 13);
			this->uLabel->TabIndex = 5;
			this->uLabel->Text = L"коэффициент трения";
			// 
			// angleLabel
			// 
			this->angleLabel->AutoSize = true;
			this->angleLabel->Location = System::Drawing::Point(9, 102);
			this->angleLabel->Name = L"angleLabel";
			this->angleLabel->Size = System::Drawing::Size(29, 13);
			this->angleLabel->TabIndex = 6;
			this->angleLabel->Text = L"угол";
			// 
			// firstPlot
			// 
			this->firstPlot->Location = System::Drawing::Point(286, 42);
			this->firstPlot->Name = L"firstPlot";
			this->firstPlot->Size = System::Drawing::Size(315, 189);
			this->firstPlot->TabIndex = 7;
			this->firstPlot->TabStop = false;
			this->firstPlot->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::firstPlot_Paint);
			// 
			// resultLabel
			// 
			this->resultLabel->AutoSize = true;
			this->resultLabel->Location = System::Drawing::Point(13, 175);
			this->resultLabel->Name = L"resultLabel";
			this->resultLabel->Size = System::Drawing::Size(35, 13);
			this->resultLabel->TabIndex = 8;
			this->resultLabel->Text = L"label1";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(16, 208);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(264, 160);
			this->listBox1->TabIndex = 9;
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(797, 335);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(8, 8);
			this->chart1->TabIndex = 10;
			this->chart1->Text = L"chart1";
			// 
			// chart2
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(635, 43);
			this->chart2->Name = L"chart2";
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(300, 300);
			this->chart2->TabIndex = 11;
			this->chart2->Text = L"chart2";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1047, 562);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->resultLabel);
			this->Controls->Add(this->firstPlot);
			this->Controls->Add(this->angleLabel);
			this->Controls->Add(this->uLabel);
			this->Controls->Add(this->angleTextBox);
			this->Controls->Add(this->uTextBox);
			this->Controls->Add(this->massLabel);
			this->Controls->Add(this->massTextBox);
			this->Controls->Add(this->calcBtn);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->firstPlot))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma endregion 

#pragma region Methods
		void DrawMarks(Graphics^ g, std::vector<PlotPoint> points)
		{
			for (int i = 0;i < points.size() - 1;i += 2)
			{
				DrawLine(g, points[i], points[i + 1], System::Drawing::Pens::Black);
			}
		}
		void DrawLine(Graphics^ g, PlotPoint start, PlotPoint end, System::Drawing::Pen^ pen)
		{
			g->DrawLine(pen, start.x, start.y, end.x, end.y);
		}
		void DrawMultiLine(Graphics^ g, std::vector<PlotPoint> points, System::Drawing::Pen^ pen)
		{
			if (points.size() > 0)
			{
				for (int i = 0;i < points.size() - 1;i++)
				{
					listBox1->Items->Add(points[i].x.ToString() + "," + points[i].y.ToString());
					g->DrawLine(pen, points[i].x, points[i].y,
						points[i + 1].x, points[i + 1].y);
				}
			}
		}
		std::string ConvertString(String ^ s) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string os = chars;
			//Marshal::FreeHGlobal(IntPtr((void*)chars));
			return os;
		}
#pragma endregion

#pragma region EVENTS
	private: System::Void calcBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//Results *res = new Results(massTextBox->Text, uTextBox->Text, angleTextBox->Text, 1, firstPlot->Height - 1, 1, 500);
		//if (res->firstMass != 0)
		//	resultLabel->Text = System::Convert::ToString(res->GetAceleration());
		//else
		//	resultLabel->Text = "некорректное значение массы";
		firstPlot->Refresh();
	}
	private: System::Void firstPlot_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		std::map < std::string, std::string > strValues;
		std::map<std::string, int> intValues;
		std::string ii= ConvertString(massTextBox->Text);
		strValues.insert(std::make_pair("mas", ConvertString(massTextBox->Text)));
		strValues.insert(std::make_pair("mu", ConvertString(uTextBox->Text)));
		strValues.insert(std::make_pair("angle", ConvertString(angleTextBox->Text)));

		intValues.insert(std::make_pair("scale", 1));
		intValues.insert(std::make_pair("offsetX", 5));
		intValues.insert(std::make_pair("offsetY", firstPlot->Height-10));
		intValues.insert(std::make_pair("axis x length", firstPlot->Width-10));
		intValues.insert(std::make_pair("axis y length", firstPlot->Height-10));
		
		Results *res = new Results(strValues,intValues);
		if (res->firstMass != 0)
			resultLabel->Text = System::Convert::ToString(res->GetAceleration());
		else
			resultLabel->Text = "некорректное значение массы";
		DrawMultiLine(e->Graphics, res->accWithMu, System::Drawing::Pens::OrangeRed);
		DrawMultiLine(e->Graphics, res->axisX, System::Drawing::Pens::Black);
		DrawMultiLine(e->Graphics, res->axisY, System::Drawing::Pens::Black);
		DrawMarks(e->Graphics, res->marksY);
		DrawMarks(e->Graphics, res->marksX);
	}
#pragma endregion

	};
}

