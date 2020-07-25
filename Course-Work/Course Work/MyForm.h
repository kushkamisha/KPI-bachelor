#pragma once
#include "stdafx.h"
#include "functions.h"

namespace CourseWork {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  graph;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->graph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graph))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(61, 287);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(61, 53);
			this->button1->TabIndex = 0;
			this->button1->Text = L"GO!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(113, 90);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(126, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"(x-1)^2";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(229, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(311, 39);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Find extremum program";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 90);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Input function";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(12, 131);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(114, 16);
			this->label4->TabIndex = 5;
			this->label4->Text = L"X changes from";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(174, 135);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(21, 16);
			this->label5->TabIndex = 6;
			this->label5->Text = L"to";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(132, 131);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(36, 20);
			this->textBox2->TabIndex = 7;
			this->textBox2->Text = L"1";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(201, 131);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(38, 20);
			this->textBox3->TabIndex = 8;
			this->textBox3->Text = L"2";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(89, 176);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(53, 20);
			this->textBox4->TabIndex = 9;
			this->textBox4->Text = L"0,01";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(12, 176);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(71, 16);
			this->label6->TabIndex = 10;
			this->label6->Text = L"accuracy";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(327, 90);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(170, 16);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Choose solving method";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton1->Location = System::Drawing::Point(330, 135);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(182, 20);
			this->radioButton1->TabIndex = 12;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Golden-section search";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton2->Location = System::Drawing::Point(330, 176);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(193, 20);
			this->radioButton2->TabIndex = 13;
			this->radioButton2->Text = L"\?Bracketing a minimum\?";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton3->Location = System::Drawing::Point(330, 219);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(154, 20);
			this->radioButton3->TabIndex = 14;
			this->radioButton3->Text = L"Dichotomy method";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(280, 287);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(107, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Answer will be here...";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(15, 222);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(107, 17);
			this->checkBox1->TabIndex = 16;
			this->checkBox1->Text = L"Save result to file";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// graph
			// 
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->ScaleView->SizeType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Number;
			chartArea1->Name = L"ChartArea1";
			this->graph->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->graph->Legends->Add(legend1);
			this->graph->Location = System::Drawing::Point(576, 40);
			this->graph->Name = L"graph";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->graph->Series->Add(series1);
			this->graph->Size = System::Drawing::Size(300, 300);
			this->graph->TabIndex = 17;
			this->graph->Text = L"chart1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(909, 402);
			this->Controls->Add(this->graph);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Find extremum";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graph))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// axis X
		graph->ChartAreas[0]->AxisX->ScaleView->Zoom(-20, 20);
		graph->ChartAreas[0]->CursorX->IsUserEnabled = true;
		graph->ChartAreas[0]->CursorX->IsUserSelectionEnabled = true;
		graph->ChartAreas[0]->AxisX->ScaleView->Zoomable = true;
		graph->ChartAreas[0]->AxisX->ScrollBar->IsPositionedInside = true;

		// axis Y
		graph->ChartAreas[0]->AxisY->ScaleView->Zoom(-20, 20);
		graph->ChartAreas[0]->CursorY->IsUserEnabled = true;
		graph->ChartAreas[0]->CursorY->IsUserSelectionEnabled = true;
		graph->ChartAreas[0]->AxisY->ScaleView->Zoomable = true;
		graph->ChartAreas[0]->AxisY->ScrollBar->IsPositionedInside = true;
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ func = textBox1->Text;
	std::string ff = msclr::interop::marshal_as<std::string>(func);

	// if a == b -> ERROR
	// if a, b, acc - NaN -> ERROR
	// (Solved) if function is incorrect (y * t) -> ERROR

	// input function has incorrect format
	if (!CheckFunction(ff))
		MessageBox::Show("Input function has incorrect format, try enter it again.", "Error");
	else
	{
		// input x range and accuracy
		// input a
		bool error = false;
		double a = 1, b = 2, acc = 0.01;
		std::string help_str = msclr::interop::marshal_as<std::string>(textBox2->Text);
		help_str = ReplaceAll(help_str, ".", ","); // replace '.' by ',' (3.14 (NaN) -> 3,14(Number))
		if (IsNumber(help_str))
		{
			a = Convert::ToDouble(msclr::interop::marshal_as<String^>(help_str));
			error = false;
		}
		else
		{
			MessageBox::Show("Bottom x border is incorrect, try enter again.", "Error");
			error = true;
		}

		// input b
		help_str = msclr::interop::marshal_as<std::string>(textBox3->Text);
		help_str = ReplaceAll(help_str, ".", ",");
		if (IsNumber(help_str))
		{
			b = Convert::ToDouble(msclr::interop::marshal_as<String^>(help_str));
			error = false;
		}
		else
		{
			MessageBox::Show("Up x border is incorrect, try enter again.", "Error");
			error = true;
		}

		// input acc
		help_str = msclr::interop::marshal_as<std::string>(textBox4->Text);
		help_str = ReplaceAll(help_str, ".", ",");
		if (IsNumber(help_str))
		{
			acc = Convert::ToDouble(msclr::interop::marshal_as<String^>(help_str));
			error = false;
		}
		else
		{
			MessageBox::Show("Accuracy is incorrect, try enter again.", "Error");
			error = true;
		}

		if (!error)
		{
			// uncorrect function boundaries
			if (a > b)
			{
				double c = a;
				a = b;
				b = c;
			}

			// replace x^3 by x*x*x and so on
			PowerReplace(ff);

			// draw graph
			graph->Series[0]->Points->Clear();
			for (int i = -20; i < 20; ++i)
				graph->Series[0]->Points->AddXY(i, f(ff, i));

			// choose method
			std::string result = "";
			if (radioButton1->Checked)
				result = GoldenSectionSearch(ff, a, b, acc);
			if (radioButton2->Checked)
				result = BracketingMinimum(ff, a, b, acc);
			if (radioButton3->Checked)
				result = DichotomyMethod(ff, a, b, acc);

			// save result to file
			if (checkBox1->Checked)
			{
				SaveToFile(result);
				MessageBox::Show("File \"extremums.txt\" was successfully created.", "Success");
			}

			label2->Text = msclr::interop::marshal_as<String^>(result);
		}
	}
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
