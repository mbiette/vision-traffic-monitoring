#pragma once

#include "main.h"
#include "ManagedMonitor.h"
#include "Merging.h"

namespace TrafficMonitorGUIEmbedded {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Form1 The Main GUI For our Application
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
public ref class Form1 : public System::Windows::Forms::Form
{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			/*this->strbuf = new stringstream(stringstream::in|stringstream::out);
			this->old = cout.rdbuf();
			this->out = this->strbuf->rdbuf();
			cout.rdbuf(this->out);*/

			this->KeepOn = false;
			this->VideoPath = NULL;
			this->Merger = new Merging();
			this->transcoder = gcnew ManagedMonitor(this->NumBus,this->NumVehicle,this->NumCars, this->NumPed, this->NumUndef, this->TrafficState, this->OnroadSpeed, this->textBox1);
			this->sb = gcnew System::Text::StringBuilder(this->textBox1->Text);
			this->Hijack = gcnew System::IO::StringWriter(this->sb);
			System::Console::SetOut(this->Hijack);
			this->textBox1->Text = L"Program Loaded, all check clear, Program Start";
			Application::Idle += gcnew EventHandler(this, &TrafficMonitorGUIEmbedded::Form1::OnIdle);
			//cout.rdbuf(this->old);
			
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
			if(this->Computingthread->IsAlive) this->Computingthread->Abort();
		}
	private: Merging* Merger;
	private: ManagedMonitor^ transcoder;
	private: char* VideoPath;
	private: bool KeepOn;
	private: streambuf* out;
	private: ostringstream* strbuf;
	private: streambuf* old;
	private: Thread ^Computingthread;
	private: System::Text::StringBuilder^ sb;

	private: System::Windows::Forms::Label^  infoSpeed;


	private: System::Windows::Forms::Label^  infoVehicle;
	private: System::IO::StringWriter^ Hijack;		 


	private: System::Windows::Forms::Label^  NumVehicle;



	private: System::Windows::Forms::Label^  infoTraffic;
	private: System::Windows::Forms::Label^  OnroadSpeed;
	private: System::Windows::Forms::Label^  TrafficState;



private: System::Windows::Forms::OpenFileDialog^  openVideoFile;
private: System::Windows::Forms::Button^  Starting;

private: System::Windows::Forms::Button^  Start;
private: System::Windows::Forms::ProgressBar^  VideoState;
private: System::Windows::Forms::Label^  infoCars;
private: System::Windows::Forms::Label^  infoBus;
private: System::Windows::Forms::Label^  infoPed;
private: System::Windows::Forms::Label^  infoUndef;
private: System::Windows::Forms::Label^  NumCars;
private: System::Windows::Forms::Label^  NumBus;








private: System::Windows::Forms::Label^  NumPed;

private: System::Windows::Forms::Label^  NumUndef;
private: System::Windows::Forms::Label^  liar;
private: System::Windows::Forms::Button^  Pausing;
private: System::Windows::Forms::TextBox^  textBox1;


private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::Label^  swatch;
private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;

private: System::ComponentModel::IContainer^  components;





	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->infoSpeed = (gcnew System::Windows::Forms::Label());
			this->infoVehicle = (gcnew System::Windows::Forms::Label());
			this->NumVehicle = (gcnew System::Windows::Forms::Label());
			this->infoTraffic = (gcnew System::Windows::Forms::Label());
			this->OnroadSpeed = (gcnew System::Windows::Forms::Label());
			this->TrafficState = (gcnew System::Windows::Forms::Label());
			this->openVideoFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->Starting = (gcnew System::Windows::Forms::Button());
			this->VideoState = (gcnew System::Windows::Forms::ProgressBar());
			this->infoCars = (gcnew System::Windows::Forms::Label());
			this->infoBus = (gcnew System::Windows::Forms::Label());
			this->infoPed = (gcnew System::Windows::Forms::Label());
			this->infoUndef = (gcnew System::Windows::Forms::Label());
			this->NumCars = (gcnew System::Windows::Forms::Label());
			this->NumBus = (gcnew System::Windows::Forms::Label());
			this->NumPed = (gcnew System::Windows::Forms::Label());
			this->NumUndef = (gcnew System::Windows::Forms::Label());
			this->liar = (gcnew System::Windows::Forms::Label());
			this->Pausing = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->swatch = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->SuspendLayout();
			// 
			// infoSpeed
			// 
			this->infoSpeed->AutoSize = true;
			this->infoSpeed->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoSpeed->Location = System::Drawing::Point(45, 32);
			this->infoSpeed->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->infoSpeed->Name = L"infoSpeed";
			this->infoSpeed->Size = System::Drawing::Size(129, 15);
			this->infoSpeed->TabIndex = 1;
			this->infoSpeed->Text = L"Mean On Road Speed :";
			// 
			// infoVehicle
			// 
			this->infoVehicle->AutoSize = true;
			this->infoVehicle->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoVehicle->Location = System::Drawing::Point(45, 117);
			this->infoVehicle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->infoVehicle->Name = L"infoVehicle";
			this->infoVehicle->Size = System::Drawing::Size(146, 15);
			this->infoVehicle->TabIndex = 3;
			this->infoVehicle->Text = L"Number of Seen Vehicles :";
			// 
			// NumVehicle
			// 
			this->NumVehicle->AutoSize = true;
			this->NumVehicle->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->NumVehicle->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NumVehicle->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NumVehicle->Location = System::Drawing::Point(261, 117);
			this->NumVehicle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->NumVehicle->MinimumSize = System::Drawing::Size(40, 17);
			this->NumVehicle->Name = L"NumVehicle";
			this->NumVehicle->Size = System::Drawing::Size(40, 18);
			this->NumVehicle->TabIndex = 6;
			this->NumVehicle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumVehicle->UseCompatibleTextRendering = true;
			this->NumVehicle->UseMnemonic = false;
			// 
			// infoTraffic
			// 
			this->infoTraffic->AutoSize = true;
			this->infoTraffic->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoTraffic->Location = System::Drawing::Point(45, 74);
			this->infoTraffic->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->infoTraffic->Name = L"infoTraffic";
			this->infoTraffic->Size = System::Drawing::Size(77, 15);
			this->infoTraffic->TabIndex = 2;
			this->infoTraffic->Text = L"Traffic State :";
			// 
			// OnroadSpeed
			// 
			this->OnroadSpeed->AutoSize = true;
			this->OnroadSpeed->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->OnroadSpeed->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->OnroadSpeed->ForeColor = System::Drawing::SystemColors::WindowText;
			this->OnroadSpeed->Location = System::Drawing::Point(261, 30);
			this->OnroadSpeed->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->OnroadSpeed->MinimumSize = System::Drawing::Size(40, 17);
			this->OnroadSpeed->Name = L"OnroadSpeed";
			this->OnroadSpeed->Size = System::Drawing::Size(40, 18);
			this->OnroadSpeed->TabIndex = 4;
			this->OnroadSpeed->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->OnroadSpeed->UseCompatibleTextRendering = true;
			this->OnroadSpeed->UseMnemonic = false;
			// 
			// TrafficState
			// 
			this->TrafficState->AutoSize = true;
			this->TrafficState->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->TrafficState->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TrafficState->ForeColor = System::Drawing::SystemColors::WindowText;
			this->TrafficState->Location = System::Drawing::Point(262, 74);
			this->TrafficState->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->TrafficState->MinimumSize = System::Drawing::Size(39, 17);
			this->TrafficState->Name = L"TrafficState";
			this->TrafficState->Size = System::Drawing::Size(39, 18);
			this->TrafficState->TabIndex = 5;
			this->TrafficState->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->TrafficState->UseCompatibleTextRendering = true;
			this->TrafficState->UseMnemonic = false;
			// 
			// openVideoFile
			// 
			this->openVideoFile->Filter = L"\"avi files(.avi)|*.avi|mp4 files(.mp4)|*.mp4|QuickTime movie(.mov)|*.mov|Matroska" 
				L" video(.mkv)|*.mkv*\"";
			this->openVideoFile->InitialDirectory = L".\\\\Resources";
			this->openVideoFile->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::Checkvideo);
			// 
			// Starting
			// 
			this->Starting->AutoSize = true;
			this->Starting->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->Starting->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Starting->Location = System::Drawing::Point(48, 478);
			this->Starting->Name = L"Starting";
			this->Starting->Size = System::Drawing::Size(108, 25);
			this->Starting->TabIndex = 9;
			this->Starting->Text = L"Start Monitoring";
			this->Starting->UseVisualStyleBackColor = false;
			this->Starting->Click += gcnew System::EventHandler(this, &Form1::GetitOn);
			// 
			// VideoState
			// 
			this->VideoState->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->VideoState->ForeColor = System::Drawing::Color::Lime;
			this->VideoState->Location = System::Drawing::Point(48, 527);
			this->VideoState->Maximum = 97;
			this->VideoState->Name = L"VideoState";
			this->VideoState->Size = System::Drawing::Size(253, 17);
			this->VideoState->TabIndex = 10;
			// 
			// infoCars
			// 
			this->infoCars->AutoSize = true;
			this->infoCars->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoCars->Location = System::Drawing::Point(45, 163);
			this->infoCars->Name = L"infoCars";
			this->infoCars->Size = System::Drawing::Size(147, 15);
			this->infoCars->TabIndex = 11;
			this->infoCars->Text = L"Number of Light Vehicles :";
			// 
			// infoBus
			// 
			this->infoBus->AutoSize = true;
			this->infoBus->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoBus->Location = System::Drawing::Point(45, 208);
			this->infoBus->Name = L"infoBus";
			this->infoBus->Size = System::Drawing::Size(154, 15);
			this->infoBus->TabIndex = 12;
			this->infoBus->Text = L"Number of Heavy Vehicles :";
			// 
			// infoPed
			// 
			this->infoPed->AutoSize = true;
			this->infoPed->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoPed->Location = System::Drawing::Point(45, 251);
			this->infoPed->Name = L"infoPed";
			this->infoPed->Size = System::Drawing::Size(138, 15);
			this->infoPed->TabIndex = 13;
			this->infoPed->Text = L"Number of Pedestrians :";
			// 
			// infoUndef
			// 
			this->infoUndef->AutoSize = true;
			this->infoUndef->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->infoUndef->Location = System::Drawing::Point(45, 301);
			this->infoUndef->Name = L"infoUndef";
			this->infoUndef->Size = System::Drawing::Size(173, 15);
			this->infoUndef->TabIndex = 14;
			this->infoUndef->Text = L"Number of Undefined Vehicles:";
			// 
			// NumCars
			// 
			this->NumCars->AutoSize = true;
			this->NumCars->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->NumCars->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NumCars->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NumCars->Location = System::Drawing::Point(261, 163);
			this->NumCars->MinimumSize = System::Drawing::Size(40, 17);
			this->NumCars->Name = L"NumCars";
			this->NumCars->Size = System::Drawing::Size(40, 18);
			this->NumCars->TabIndex = 15;
			this->NumCars->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumCars->UseCompatibleTextRendering = true;
			this->NumCars->UseMnemonic = false;
			// 
			// NumBus
			// 
			this->NumBus->AutoSize = true;
			this->NumBus->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->NumBus->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NumBus->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NumBus->Location = System::Drawing::Point(261, 205);
			this->NumBus->MinimumSize = System::Drawing::Size(40, 17);
			this->NumBus->Name = L"NumBus";
			this->NumBus->Size = System::Drawing::Size(40, 18);
			this->NumBus->TabIndex = 16;
			this->NumBus->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumBus->UseCompatibleTextRendering = true;
			this->NumBus->UseMnemonic = false;
			// 
			// NumPed
			// 
			this->NumPed->AutoSize = true;
			this->NumPed->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->NumPed->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NumPed->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NumPed->Location = System::Drawing::Point(261, 248);
			this->NumPed->MinimumSize = System::Drawing::Size(40, 17);
			this->NumPed->Name = L"NumPed";
			this->NumPed->Size = System::Drawing::Size(40, 18);
			this->NumPed->TabIndex = 17;
			this->NumPed->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumPed->UseCompatibleTextRendering = true;
			this->NumPed->UseMnemonic = false;
			// 
			// NumUndef
			// 
			this->NumUndef->AutoSize = true;
			this->NumUndef->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->NumUndef->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->NumUndef->ForeColor = System::Drawing::SystemColors::WindowText;
			this->NumUndef->Location = System::Drawing::Point(261, 298);
			this->NumUndef->MinimumSize = System::Drawing::Size(40, 17);
			this->NumUndef->Name = L"NumUndef";
			this->NumUndef->Size = System::Drawing::Size(40, 18);
			this->NumUndef->TabIndex = 18;
			this->NumUndef->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NumUndef->UseCompatibleTextRendering = true;
			this->NumUndef->UseMnemonic = false;
			// 
			// liar
			// 
			this->liar->AutoSize = true;
			this->liar->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->liar->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->liar->Location = System::Drawing::Point(332, 386);
			this->liar->Name = L"liar";
			this->liar->Size = System::Drawing::Size(0, 15);
			this->liar->TabIndex = 19;
			this->liar->Visible = false;
			this->liar->TextChanged += gcnew System::EventHandler(this, &Form1::LiarsRealm);
			// 
			// Pausing
			// 
			this->Pausing->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->Pausing->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Pausing->Location = System::Drawing::Point(193, 478);
			this->Pausing->Name = L"Pausing";
			this->Pausing->Size = System::Drawing::Size(108, 25);
			this->Pausing->TabIndex = 20;
			this->Pausing->Text = L"Pause";
			this->Pausing->UseVisualStyleBackColor = false;
			this->Pausing->Click += gcnew System::EventHandler(this, &Form1::GetToPause);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(48, 353);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(253, 108);
			this->textBox1->TabIndex = 21;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::updatetime);
			// 
			// swatch
			// 
			this->swatch->AutoSize = true;
			this->swatch->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->swatch->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->swatch->Location = System::Drawing::Point(301, 557);
			this->swatch->Name = L"swatch";
			this->swatch->Size = System::Drawing::Size(2, 17);
			this->swatch->TabIndex = 22;
			this->swatch->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dateTimePicker1->Location = System::Drawing::Point(335, 251);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 22);
			this->dateTimePicker1->TabIndex = 23;
			this->dateTimePicker1->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(350, 581);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->swatch);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Pausing);
			this->Controls->Add(this->liar);
			this->Controls->Add(this->NumUndef);
			this->Controls->Add(this->NumPed);
			this->Controls->Add(this->NumBus);
			this->Controls->Add(this->NumCars);
			this->Controls->Add(this->infoUndef);
			this->Controls->Add(this->infoPed);
			this->Controls->Add(this->infoBus);
			this->Controls->Add(this->infoCars);
			this->Controls->Add(this->VideoState);
			this->Controls->Add(this->Starting);
			this->Controls->Add(this->NumVehicle);
			this->Controls->Add(this->TrafficState);
			this->Controls->Add(this->OnroadSpeed);
			this->Controls->Add(this->infoVehicle);
			this->Controls->Add(this->infoTraffic);
			this->Controls->Add(this->infoSpeed);
			this->Font = (gcnew System::Drawing::Font(L"Californian FB", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"Form1";
			this->Text = L"Traffic Monitor";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Ending);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	



private: System::Void GetitOn(System::Object^  sender, System::EventArgs^  e) {
			 this->openVideoFile->ShowDialog(this);
		 }
private: System::Void Ending(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 this->textBox1->Text += L" Program Exiting! ";
			   // If the no button was pressed ...
			 if (MessageBox::Show("Are you sure you want to quit the Monitor?", "Exiting Monitor", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
			 {
					//cancel the closure of the form.
					e->Cancel = true;
					this->textBox1->Text += L" Exit Canceled! ";
			 }
		 }







private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Checkvideo(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 System::String^ FileInfo = this->openVideoFile->FileName;
			 this->VideoPath = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(FileInfo);
			 this->Merger->changeVideo(this->VideoPath);
			 this->KeepOn = true;
			 this->textBox1->Text += L" Loaded File: ! ";
			 this->textBox1->Text->Concat(this->textBox1->Text, FileInfo);
			 this->textBox1->Text += L" Monitoring Starting! ";
			
		 }

	private: void ThreadTask()
	{
		this->Merger->Run();
	}
	private: void OnIdle(Object^ sender, EventArgs^ e)
	{
		System::String ^test;
		 if(this->KeepOn)
		 {
			this->Merger->Run();
			this->transcoder->UpdateTextOutputs(this->Merger);
			this->VideoState->Value = this->Merger->VideoEnd;
			if(this->VideoState->Value.Equals(this->VideoState->Value.MaxValue))
			{
				this->textBox1->Text += L" End of actual video file ";
				this->KeepOn = false;
			}
			test = gcnew System::String(this->Merger->outputs.c_str());
			if( System::String::Compare(test, System::String::Empty) != 0) 
				this->liar->Text = test;
			test = gcnew System::String(this->Merger->outblob.c_str());
			if( System::String::Compare(test, System::String::Empty) != 0) 
				this->textBox1->Text = test;
		 }
		 
	}


private: System::Void LiarsRealm(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void GetToPause(System::Object^  sender, System::EventArgs^  e) {
			 if(this->KeepOn)
			 {
				this->Pausing->Text = L"Resume";
				this->textBox1->Text += L" Monitor paused! ";
				this->KeepOn = false;
			 }
			 else
			 {
				this->Pausing->Text = L"Pause";
				this->textBox1->Text += L" Monitor Resumed! ";
				this->KeepOn = true;
			 }
		 }

private: System::Void dateTimePicker1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void updatetime(System::Object^  sender, System::EventArgs^  e) {
			 this->dateTimePicker1->Value = System::DateTime::Now;
			 this->swatch->Text = this->dateTimePicker1->Value.ToString();
		 }
};
	
}

