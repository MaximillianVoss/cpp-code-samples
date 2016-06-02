#include "PlotPoint.h"
#include "Results.h"
#include <map>
#pragma once
using namespace System;
using namespace std;

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
			labelAccValue->Text = "";
			labelDirection->Text = "";
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

	private: System::Windows::Forms::Label^  uLabel;
	private: System::Windows::Forms::Label^  angleLabel;






	private: System::Windows::Forms::Label^  resultLabel;


	private: System::Windows::Forms::DataVisualization::Charting::Chart^  firstChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  secondChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  thirdChart;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  fourthChart;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::Label^  labelAccValue;

	private: System::Windows::Forms::Label^  labelDirection;
	private: System::Windows::Forms::NumericUpDown^  angleNumeric;




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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->calcBtn = (gcnew System::Windows::Forms::Button());
			this->massTextBox = (gcnew System::Windows::Forms::TextBox());
			this->massLabel = (gcnew System::Windows::Forms::Label());
			this->uTextBox = (gcnew System::Windows::Forms::TextBox());
			this->uLabel = (gcnew System::Windows::Forms::Label());
			this->angleLabel = (gcnew System::Windows::Forms::Label());
			this->resultLabel = (gcnew System::Windows::Forms::Label());
			this->firstChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->secondChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->thirdChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->fourthChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->labelAccValue = (gcnew System::Windows::Forms::Label());
			this->labelDirection = (gcnew System::Windows::Forms::Label());
			this->angleNumeric = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->firstChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thirdChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fourthChart))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->angleNumeric))->BeginInit();
			this->SuspendLayout();
			// 
			// calcBtn
			// 
			this->calcBtn->Location = System::Drawing::Point(12, 387);
			this->calcBtn->Name = L"calcBtn";
			this->calcBtn->Size = System::Drawing::Size(115, 58);
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
			this->uTextBox->Text = L"0.3";
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
			// resultLabel
			// 
			this->resultLabel->AutoSize = true;
			this->resultLabel->Location = System::Drawing::Point(12, 170);
			this->resultLabel->Name = L"resultLabel";
			this->resultLabel->Size = System::Drawing::Size(0, 13);
			this->resultLabel->TabIndex = 8;
			this->resultLabel->Click += gcnew System::EventHandler(this, &Form1::resultLabel_Click);
			// 
			// firstChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->firstChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->firstChart->Legends->Add(legend1);
			this->firstChart->Location = System::Drawing::Point(6, 6);
			this->firstChart->Name = L"firstChart";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->firstChart->Series->Add(series1);
			this->firstChart->Size = System::Drawing::Size(703, 402);
			this->firstChart->TabIndex = 11;
			this->firstChart->Text = L"chart2";
			// 
			// secondChart
			// 
			chartArea2->Name = L"ChartArea1";
			this->secondChart->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->secondChart->Legends->Add(legend2);
			this->secondChart->Location = System::Drawing::Point(6, 6);
			this->secondChart->Name = L"secondChart";
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->secondChart->Series->Add(series2);
			this->secondChart->Size = System::Drawing::Size(700, 399);
			this->secondChart->TabIndex = 12;
			this->secondChart->Text = L"chart2";
			// 
			// thirdChart
			// 
			chartArea3->Name = L"ChartArea1";
			this->thirdChart->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->thirdChart->Legends->Add(legend3);
			this->thirdChart->Location = System::Drawing::Point(6, 6);
			this->thirdChart->Name = L"thirdChart";
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"Series1";
			this->thirdChart->Series->Add(series3);
			this->thirdChart->Size = System::Drawing::Size(700, 399);
			this->thirdChart->TabIndex = 13;
			this->thirdChart->Text = L"chart3";
			// 
			// fourthChart
			// 
			chartArea4->Name = L"ChartArea1";
			this->fourthChart->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend1";
			this->fourthChart->Legends->Add(legend4);
			this->fourthChart->Location = System::Drawing::Point(6, 6);
			this->fourthChart->Name = L"fourthChart";
			series4->ChartArea = L"ChartArea1";
			series4->Legend = L"Legend1";
			series4->Name = L"Series1";
			this->fourthChart->Series->Add(series4);
			this->fourthChart->Size = System::Drawing::Size(700, 399);
			this->fourthChart->TabIndex = 14;
			this->fourthChart->Text = L"chart4";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(129, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(720, 437);
			this->tabControl1->TabIndex = 15;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->firstChart);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(712, 411);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->secondChart);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(712, 411);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->thirdChart);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(712, 411);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->fourthChart);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(712, 411);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"4";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// labelAccValue
			// 
			this->labelAccValue->AutoSize = true;
			this->labelAccValue->Location = System::Drawing::Point(13, 179);
			this->labelAccValue->Name = L"labelAccValue";
			this->labelAccValue->Size = System::Drawing::Size(35, 13);
			this->labelAccValue->TabIndex = 16;
			this->labelAccValue->Text = L"label1";
			// 
			// labelDirection
			// 
			this->labelDirection->AutoSize = true;
			this->labelDirection->Location = System::Drawing::Point(13, 154);
			this->labelDirection->Name = L"labelDirection";
			this->labelDirection->Size = System::Drawing::Size(35, 13);
			this->labelDirection->TabIndex = 17;
			this->labelDirection->Text = L"label2";
			// 
			// angleNumeric
			// 
			this->angleNumeric->Location = System::Drawing::Point(12, 118);
			this->angleNumeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 90, 0, 0, 0 });
			this->angleNumeric->Name = L"angleNumeric";
			this->angleNumeric->Size = System::Drawing::Size(96, 20);
			this->angleNumeric->TabIndex = 18;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(852, 454);
			this->Controls->Add(this->angleNumeric);
			this->Controls->Add(this->labelDirection);
			this->Controls->Add(this->labelAccValue);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->resultLabel);
			this->Controls->Add(this->angleLabel);
			this->Controls->Add(this->uLabel);
			this->Controls->Add(this->uTextBox);
			this->Controls->Add(this->massLabel);
			this->Controls->Add(this->massTextBox);
			this->Controls->Add(this->calcBtn);
			this->Name = L"Form1";
			this->Text = L"Зависимости a и F от angle и mu";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->firstChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->secondChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thirdChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fourthChart))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->angleNumeric))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma endregion 

#pragma region Methods
		string ConvertString(String ^ s) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string os = chars;
			//Marshal::FreeHGlobal(IntPtr((void*)chars));
			return os;
		}
		void Drawchart(System::Windows::Forms::DataVisualization::Charting::Chart^ control,String ^ seriesName, std::vector<PlotPoint> points)
		{
			if (control->Series->FindByName(seriesName))
				control->Series->Remove(control->Series->FindByName(seriesName));
			 
			control->Series->Add(seriesName);
			control->Series[seriesName]->Name = seriesName;
			control->Series[seriesName]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			control->Series[seriesName]->Color = Drawing::Color::Red;
			for each (PlotPoint item in points)
			{
				control->Series[seriesName]->Points->AddXY(item.x, item.y);
			}

		}
#pragma endregion

#pragma region EVENTS
	private: System::Void calcBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (atof(ConvertString(uTextBox->Text).c_str())<=0.3)
		{
			Results *res = new Results(ConvertString(massTextBox->Text), ConvertString(uTextBox->Text), ConvertString(angleNumeric->Text));
			if (res->firstMass != 0)
			{
				double acceleration = res->GetAceleration();
				labelAccValue->Text = System::Convert::ToString(acceleration);
				if (acceleration > 0)
					labelDirection->Text = "Тело движется вверх";
				else if (acceleration < 0)
					labelDirection->Text = "Тело движется вниз";
				else
					labelDirection->Text = "Тело не движется";

				Drawchart(firstChart, "Зависимость ускорения от u", res->accWithMu);
				Drawchart(secondChart, "Зависимость ускорения от угла", res->accWithAngle);
				Drawchart(thirdChart, "Зависимость силы от угла", res->forceWithAngle);
				Drawchart(fourthChart, "Зависимость силы от u", res->forceWtithMu);
			}
			else
				labelDirection->Text = "некорректное значение массы";
		}
		else
		{
			labelDirection->Text = "коэффициент трения не может быть больше 0.3";
		}

		
	}
	private: System::Void firstPlot_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
	}
#pragma endregion

	private: System::Void resultLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}

};
}

