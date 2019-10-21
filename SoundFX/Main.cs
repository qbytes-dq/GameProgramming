/*
look at for different VU meters.
Z:\_        burn 4 - programming\C#\MP3 Players\__nBASS-0.9.6.1[1]\StreamTest

msdn doc and downloads
http://msdn.microsoft.com/library/default.asp?url=/downloads/list/directx.asp

more doc
http://msdn.microsoft.com/library/default.asp?url=/code/list/directx.asp

*/
//----------------------------------------------------------------------------
// File: Main.cs
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------

using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;


using Microsoft.DirectX;
using Microsoft.DirectX.DirectSound;
using Buffer = Microsoft.DirectX.DirectSound.Buffer;

using SoundFX;

public class MainForm : Form
{
	FFT fft;// = new FFT();

	int lastGoodFrequency = 10000;
	const int maxFrequency = 200000;
	//const int FFT_LEN = 1024;
	private Bitmap bit1;

	#region Control declarations
	private System.Windows.Forms.ListBox listboxEffects;
	private System.Windows.Forms.RadioButton radiobuttonRadioSine;
	private Button buttonOk;
	private GroupBox groupboxFrame;
	private Label labelParamName1;
	private Label labelParamValue1;
	private TrackBar trackbarSlider1;
	private Label labelParamMin1;
	private Label labelParamMax1;
	private Label labelParamName2;
	private Label labelParamValue2;
	private TrackBar trackbarSlider2;
	private Label labelParamMin2;
	private Label labelParamMax2;
	private Label labelParamName3;
	private Label labelParamValue3;
	private TrackBar trackbarSlider3;
	private Label labelParamMin3;
	private Label labelParamMax3;
	private Label labelParamName4;
	private Label labelParamValue4;
	private TrackBar trackbarSlider4;
	private Label labelParamMin4;
	private Label labelParamMax4;
	private Label labelParamName5;
	private Label labelParamValue5;
	private TrackBar trackbarSlider5;
	private Label labelParamMin5;
	private Label labelParamMax5;
	private Label labelParamName6;
	private Label labelParamValue6;
	private TrackBar trackbarSlider6;
	private Label labelParamMin6;
	private Label labelParamMax6;
	private RadioButton radiobuttonTriangle;
	private RadioButton radiobuttonSquare;
	private GroupBox groupboxFrameWaveform;
	private Button buttonOpen;
	private Label labelTextFilename;
	private Label labelStatic2;
	private Label labelTextStatus;
	private CheckBox checkboxLoop;
	private Button buttonPlay;
	private Button buttonStop;
	private Label labelStatic3;
	private GroupBox groupboxFramePhase;
	private Label labelStatic4;
	private RadioButton radiobuttonRadioNeg180;
	private RadioButton radiobuttonRadioNeg90;
	private RadioButton radiobuttonRadioZero;
	private RadioButton radiobuttonRadio90;
	private RadioButton radiobuttonRadio180;
	private System.Windows.Forms.GroupBox groupboxEffects;
	#endregion

	#region form stuff
	private struct EffectInfo
	{
		public EffectDescription description;
		public object EffectSettings;
		public object Effect;
	};

	ArrayList effectDescription	= new ArrayList();
	SecondaryBuffer applicationBuffer = null;
	Device applicationDevice = null;
	string fileName = string.Empty;
	string path = string.Empty;
	bool shouldLoop = false;
    private System.Windows.Forms.Button buttonDelete;
    private System.Windows.Forms.Timer timer1;
    private System.ComponentModel.IContainer components;
    private System.Windows.Forms.ComboBox comboEffects;
	private System.Windows.Forms.Label lblMaxFreq;
	private System.Windows.Forms.Label lblMinFreq;
	private System.Windows.Forms.TextBox textFreq;
	private System.Windows.Forms.TrackBar tbarFreq;
	private System.Windows.Forms.Label label2;
	private System.Windows.Forms.TextBox textVolume;
	private System.Windows.Forms.Label label8;
	private System.Windows.Forms.Label label9;
	private System.Windows.Forms.Label label10;
	private System.Windows.Forms.TrackBar tbarVolume;
	private System.Windows.Forms.Label label5;
	private System.Windows.Forms.Label label6;
	private System.Windows.Forms.TrackBar tbarPan;
	private System.Windows.Forms.TextBox textPan;
	private System.Windows.Forms.Label label7;
	private System.Windows.Forms.Timer timer2;
	private System.Windows.Forms.Label label3;
	private System.Windows.Forms.RichTextBox richTextBox1;
	private System.Windows.Forms.PictureBox pictureBox1;
	private System.Windows.Forms.Timer timer3;
	private System.Windows.Forms.PictureBox pictureBox2;
	private System.Windows.Forms.Timer timer4;
	private System.Windows.Forms.Label label1;
	private System.Windows.Forms.Label label4;
	private System.Windows.Forms.Label label11;
	private System.Windows.Forms.Timer timer5;
	private System.Windows.Forms.TrackBar trackBar1;
	private System.Windows.Forms.TrackBar trackBar2;
	private System.Windows.Forms.TrackBar trackBar3;
	int currentIndex = 0;
	#endregion form stuff
	#region hide stuff

	public static int Main(string[] Args)
	{
		Application.Run(new MainForm());
		return 0;
	}    
	public MainForm()
	{
		InitializeComponent();

		this.tbarFreq.Minimum = 100;
		this.tbarFreq.Maximum = maxFrequency;
		this.lblMinFreq.Text = string.Format("{0} Hz", this.tbarFreq.Minimum);
		this.lblMaxFreq.Text = string.Format("{0} KHz", this.tbarFreq.Maximum/1000);

		bit1 = new Bitmap( pictureBox1.Width, pictureBox1.Height);

		InitDirectSound();
		ClearUI(true);
	}

    #region InitializeComponent code
	private void InitializeComponent()
	{
		this.components = new System.ComponentModel.Container();
		this.buttonOk = new System.Windows.Forms.Button();
		this.groupboxFrame = new System.Windows.Forms.GroupBox();
		this.labelParamName1 = new System.Windows.Forms.Label();
		this.labelParamValue1 = new System.Windows.Forms.Label();
		this.trackbarSlider1 = new System.Windows.Forms.TrackBar();
		this.labelParamMin1 = new System.Windows.Forms.Label();
		this.labelParamMax1 = new System.Windows.Forms.Label();
		this.labelParamName2 = new System.Windows.Forms.Label();
		this.labelParamValue2 = new System.Windows.Forms.Label();
		this.trackbarSlider2 = new System.Windows.Forms.TrackBar();
		this.labelParamMin2 = new System.Windows.Forms.Label();
		this.labelParamMax2 = new System.Windows.Forms.Label();
		this.labelParamName3 = new System.Windows.Forms.Label();
		this.labelParamValue3 = new System.Windows.Forms.Label();
		this.trackbarSlider3 = new System.Windows.Forms.TrackBar();
		this.labelParamMin3 = new System.Windows.Forms.Label();
		this.labelParamMax3 = new System.Windows.Forms.Label();
		this.labelParamName4 = new System.Windows.Forms.Label();
		this.labelParamValue4 = new System.Windows.Forms.Label();
		this.trackbarSlider4 = new System.Windows.Forms.TrackBar();
		this.labelParamMin4 = new System.Windows.Forms.Label();
		this.labelParamMax4 = new System.Windows.Forms.Label();
		this.labelParamName5 = new System.Windows.Forms.Label();
		this.labelParamValue5 = new System.Windows.Forms.Label();
		this.trackbarSlider5 = new System.Windows.Forms.TrackBar();
		this.labelParamMin5 = new System.Windows.Forms.Label();
		this.labelParamMax5 = new System.Windows.Forms.Label();
		this.labelParamName6 = new System.Windows.Forms.Label();
		this.labelParamValue6 = new System.Windows.Forms.Label();
		this.trackbarSlider6 = new System.Windows.Forms.TrackBar();
		this.labelParamMin6 = new System.Windows.Forms.Label();
		this.labelParamMax6 = new System.Windows.Forms.Label();
		this.radiobuttonTriangle = new System.Windows.Forms.RadioButton();
		this.radiobuttonSquare = new System.Windows.Forms.RadioButton();
		this.radiobuttonRadioSine = new System.Windows.Forms.RadioButton();
		this.groupboxFrameWaveform = new System.Windows.Forms.GroupBox();
		this.buttonOpen = new System.Windows.Forms.Button();
		this.labelTextFilename = new System.Windows.Forms.Label();
		this.labelStatic2 = new System.Windows.Forms.Label();
		this.labelTextStatus = new System.Windows.Forms.Label();
		this.checkboxLoop = new System.Windows.Forms.CheckBox();
		this.buttonPlay = new System.Windows.Forms.Button();
		this.buttonStop = new System.Windows.Forms.Button();
		this.labelStatic3 = new System.Windows.Forms.Label();
		this.labelStatic4 = new System.Windows.Forms.Label();
		this.radiobuttonRadioNeg180 = new System.Windows.Forms.RadioButton();
		this.radiobuttonRadioNeg90 = new System.Windows.Forms.RadioButton();
		this.radiobuttonRadioZero = new System.Windows.Forms.RadioButton();
		this.radiobuttonRadio90 = new System.Windows.Forms.RadioButton();
		this.radiobuttonRadio180 = new System.Windows.Forms.RadioButton();
		this.groupboxFramePhase = new System.Windows.Forms.GroupBox();
		this.groupboxEffects = new System.Windows.Forms.GroupBox();
		this.buttonDelete = new System.Windows.Forms.Button();
		this.listboxEffects = new System.Windows.Forms.ListBox();
		this.comboEffects = new System.Windows.Forms.ComboBox();
		this.timer1 = new System.Windows.Forms.Timer(this.components);
		this.lblMaxFreq = new System.Windows.Forms.Label();
		this.lblMinFreq = new System.Windows.Forms.Label();
		this.textFreq = new System.Windows.Forms.TextBox();
		this.tbarFreq = new System.Windows.Forms.TrackBar();
		this.label2 = new System.Windows.Forms.Label();
		this.textVolume = new System.Windows.Forms.TextBox();
		this.label8 = new System.Windows.Forms.Label();
		this.label9 = new System.Windows.Forms.Label();
		this.label10 = new System.Windows.Forms.Label();
		this.tbarVolume = new System.Windows.Forms.TrackBar();
		this.label5 = new System.Windows.Forms.Label();
		this.label6 = new System.Windows.Forms.Label();
		this.tbarPan = new System.Windows.Forms.TrackBar();
		this.textPan = new System.Windows.Forms.TextBox();
		this.label7 = new System.Windows.Forms.Label();
		this.timer2 = new System.Windows.Forms.Timer(this.components);
		this.label3 = new System.Windows.Forms.Label();
		this.richTextBox1 = new System.Windows.Forms.RichTextBox();
		this.pictureBox1 = new System.Windows.Forms.PictureBox();
		this.timer3 = new System.Windows.Forms.Timer(this.components);
		this.pictureBox2 = new System.Windows.Forms.PictureBox();
		this.timer4 = new System.Windows.Forms.Timer(this.components);
		this.label1 = new System.Windows.Forms.Label();
		this.label4 = new System.Windows.Forms.Label();
		this.label11 = new System.Windows.Forms.Label();
		this.timer5 = new System.Windows.Forms.Timer(this.components);
		this.trackBar1 = new System.Windows.Forms.TrackBar();
		this.trackBar2 = new System.Windows.Forms.TrackBar();
		this.trackBar3 = new System.Windows.Forms.TrackBar();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider1)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider2)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider3)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider4)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider5)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider6)).BeginInit();
		this.groupboxFrameWaveform.SuspendLayout();
		this.groupboxFramePhase.SuspendLayout();
		this.groupboxEffects.SuspendLayout();
		((System.ComponentModel.ISupportInitialize)(this.tbarFreq)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.tbarVolume)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.tbarPan)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar2)).BeginInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar3)).BeginInit();
		this.SuspendLayout();
		// 
		// buttonOk
		// 
		this.buttonOk.Location = new System.Drawing.Point(87, 432);
		this.buttonOk.Name = "buttonOk";
		this.buttonOk.Size = new System.Drawing.Size(67, 23);
		this.buttonOk.TabIndex = 0;
		this.buttonOk.Text = "E&xit";
		this.buttonOk.Click += new System.EventHandler(this.buttonOk_Click);
		// 
		// groupboxFrame
		// 
		this.groupboxFrame.Location = new System.Drawing.Point(165, 76);
		this.groupboxFrame.Name = "groupboxFrame";
		this.groupboxFrame.Size = new System.Drawing.Size(525, 380);
		this.groupboxFrame.TabIndex = 1;
		this.groupboxFrame.TabStop = false;
		this.groupboxFrame.Text = "Parameters";
		// 
		// labelParamName1
		// 
		this.labelParamName1.Location = new System.Drawing.Point(169, 112);
		this.labelParamName1.Name = "labelParamName1";
		this.labelParamName1.Size = new System.Drawing.Size(117, 13);
		this.labelParamName1.TabIndex = 2;
		this.labelParamName1.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue1
		// 
		this.labelParamValue1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue1.Location = new System.Drawing.Point(294, 112);
		this.labelParamValue1.Name = "labelParamValue1";
		this.labelParamValue1.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue1.TabIndex = 3;
		this.labelParamValue1.Text = "Value";
		this.labelParamValue1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider1
		// 
		this.trackbarSlider1.Location = new System.Drawing.Point(426, 112);
		this.trackbarSlider1.Name = "trackbarSlider1";
		this.trackbarSlider1.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider1.TabIndex = 4;
		this.trackbarSlider1.Text = "Slider1";
		this.trackbarSlider1.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider1.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin1
		// 
		this.labelParamMin1.Location = new System.Drawing.Point(366, 112);
		this.labelParamMin1.Name = "labelParamMin1";
		this.labelParamMin1.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin1.TabIndex = 5;
		this.labelParamMin1.Text = "min";
		this.labelParamMin1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax1
		// 
		this.labelParamMax1.Location = new System.Drawing.Point(627, 120);
		this.labelParamMax1.Name = "labelParamMax1";
		this.labelParamMax1.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax1.TabIndex = 6;
		this.labelParamMax1.Text = "max";
		this.labelParamMax1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamName2
		// 
		this.labelParamName2.Location = new System.Drawing.Point(169, 160);
		this.labelParamName2.Name = "labelParamName2";
		this.labelParamName2.Size = new System.Drawing.Size(117, 13);
		this.labelParamName2.TabIndex = 7;
		this.labelParamName2.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue2
		// 
		this.labelParamValue2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue2.Location = new System.Drawing.Point(294, 160);
		this.labelParamValue2.Name = "labelParamValue2";
		this.labelParamValue2.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue2.TabIndex = 8;
		this.labelParamValue2.Text = "Value";
		this.labelParamValue2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider2
		// 
		this.trackbarSlider2.Location = new System.Drawing.Point(426, 163);
		this.trackbarSlider2.Name = "trackbarSlider2";
		this.trackbarSlider2.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider2.TabIndex = 9;
		this.trackbarSlider2.Text = "Slider1";
		this.trackbarSlider2.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider2.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin2
		// 
		this.labelParamMin2.Location = new System.Drawing.Point(366, 160);
		this.labelParamMin2.Name = "labelParamMin2";
		this.labelParamMin2.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin2.TabIndex = 10;
		this.labelParamMin2.Text = "min";
		this.labelParamMin2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax2
		// 
		this.labelParamMax2.Location = new System.Drawing.Point(627, 168);
		this.labelParamMax2.Name = "labelParamMax2";
		this.labelParamMax2.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax2.TabIndex = 11;
		this.labelParamMax2.Text = "max";
		this.labelParamMax2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamName3
		// 
		this.labelParamName3.Location = new System.Drawing.Point(169, 208);
		this.labelParamName3.Name = "labelParamName3";
		this.labelParamName3.Size = new System.Drawing.Size(117, 13);
		this.labelParamName3.TabIndex = 12;
		this.labelParamName3.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue3
		// 
		this.labelParamValue3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue3.Location = new System.Drawing.Point(294, 208);
		this.labelParamValue3.Name = "labelParamValue3";
		this.labelParamValue3.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue3.TabIndex = 13;
		this.labelParamValue3.Text = "Value";
		this.labelParamValue3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider3
		// 
		this.trackbarSlider3.Location = new System.Drawing.Point(426, 208);
		this.trackbarSlider3.Name = "trackbarSlider3";
		this.trackbarSlider3.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider3.TabIndex = 14;
		this.trackbarSlider3.Text = "Slider1";
		this.trackbarSlider3.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider3.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin3
		// 
		this.labelParamMin3.Location = new System.Drawing.Point(366, 208);
		this.labelParamMin3.Name = "labelParamMin3";
		this.labelParamMin3.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin3.TabIndex = 15;
		this.labelParamMin3.Text = "min";
		this.labelParamMin3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax3
		// 
		this.labelParamMax3.Location = new System.Drawing.Point(627, 216);
		this.labelParamMax3.Name = "labelParamMax3";
		this.labelParamMax3.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax3.TabIndex = 16;
		this.labelParamMax3.Text = "max";
		this.labelParamMax3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamName4
		// 
		this.labelParamName4.Location = new System.Drawing.Point(169, 256);
		this.labelParamName4.Name = "labelParamName4";
		this.labelParamName4.Size = new System.Drawing.Size(117, 13);
		this.labelParamName4.TabIndex = 17;
		this.labelParamName4.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue4
		// 
		this.labelParamValue4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue4.Location = new System.Drawing.Point(294, 256);
		this.labelParamValue4.Name = "labelParamValue4";
		this.labelParamValue4.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue4.TabIndex = 18;
		this.labelParamValue4.Text = "Value";
		this.labelParamValue4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider4
		// 
		this.trackbarSlider4.Location = new System.Drawing.Point(426, 256);
		this.trackbarSlider4.Name = "trackbarSlider4";
		this.trackbarSlider4.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider4.TabIndex = 19;
		this.trackbarSlider4.Text = "Slider1";
		this.trackbarSlider4.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider4.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin4
		// 
		this.labelParamMin4.Location = new System.Drawing.Point(366, 256);
		this.labelParamMin4.Name = "labelParamMin4";
		this.labelParamMin4.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin4.TabIndex = 20;
		this.labelParamMin4.Text = "min";
		this.labelParamMin4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax4
		// 
		this.labelParamMax4.Location = new System.Drawing.Point(627, 256);
		this.labelParamMax4.Name = "labelParamMax4";
		this.labelParamMax4.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax4.TabIndex = 21;
		this.labelParamMax4.Text = "max";
		this.labelParamMax4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamName5
		// 
		this.labelParamName5.Location = new System.Drawing.Point(169, 304);
		this.labelParamName5.Name = "labelParamName5";
		this.labelParamName5.Size = new System.Drawing.Size(117, 13);
		this.labelParamName5.TabIndex = 22;
		this.labelParamName5.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue5
		// 
		this.labelParamValue5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue5.Location = new System.Drawing.Point(294, 304);
		this.labelParamValue5.Name = "labelParamValue5";
		this.labelParamValue5.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue5.TabIndex = 23;
		this.labelParamValue5.Text = "Value";
		this.labelParamValue5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider5
		// 
		this.trackbarSlider5.Location = new System.Drawing.Point(426, 304);
		this.trackbarSlider5.Name = "trackbarSlider5";
		this.trackbarSlider5.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider5.TabIndex = 24;
		this.trackbarSlider5.Text = "Slider1";
		this.trackbarSlider5.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider5.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin5
		// 
		this.labelParamMin5.Location = new System.Drawing.Point(366, 304);
		this.labelParamMin5.Name = "labelParamMin5";
		this.labelParamMin5.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin5.TabIndex = 25;
		this.labelParamMin5.Text = "min";
		this.labelParamMin5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax5
		// 
		this.labelParamMax5.Location = new System.Drawing.Point(627, 312);
		this.labelParamMax5.Name = "labelParamMax5";
		this.labelParamMax5.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax5.TabIndex = 26;
		this.labelParamMax5.Text = "max";
		this.labelParamMax5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamName6
		// 
		this.labelParamName6.Location = new System.Drawing.Point(169, 352);
		this.labelParamName6.Name = "labelParamName6";
		this.labelParamName6.Size = new System.Drawing.Size(117, 13);
		this.labelParamName6.TabIndex = 27;
		this.labelParamName6.TextAlign = System.Drawing.ContentAlignment.TopRight;
		// 
		// labelParamValue6
		// 
		this.labelParamValue6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelParamValue6.Location = new System.Drawing.Point(294, 352);
		this.labelParamValue6.Name = "labelParamValue6";
		this.labelParamValue6.Size = new System.Drawing.Size(67, 16);
		this.labelParamValue6.TabIndex = 28;
		this.labelParamValue6.Text = "Value";
		this.labelParamValue6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// trackbarSlider6
		// 
		this.trackbarSlider6.Location = new System.Drawing.Point(426, 352);
		this.trackbarSlider6.Name = "trackbarSlider6";
		this.trackbarSlider6.Size = new System.Drawing.Size(195, 45);
		this.trackbarSlider6.TabIndex = 29;
		this.trackbarSlider6.Text = "Slider1";
		this.trackbarSlider6.TickStyle = System.Windows.Forms.TickStyle.None;
		this.trackbarSlider6.Scroll += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// labelParamMin6
		// 
		this.labelParamMin6.Location = new System.Drawing.Point(366, 352);
		this.labelParamMin6.Name = "labelParamMin6";
		this.labelParamMin6.Size = new System.Drawing.Size(60, 16);
		this.labelParamMin6.TabIndex = 30;
		this.labelParamMin6.Text = "min";
		this.labelParamMin6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelParamMax6
		// 
		this.labelParamMax6.Location = new System.Drawing.Point(627, 352);
		this.labelParamMax6.Name = "labelParamMax6";
		this.labelParamMax6.Size = new System.Drawing.Size(52, 13);
		this.labelParamMax6.TabIndex = 31;
		this.labelParamMax6.Text = "max";
		this.labelParamMax6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// radiobuttonTriangle
		// 
		this.radiobuttonTriangle.Location = new System.Drawing.Point(16, 16);
		this.radiobuttonTriangle.Name = "radiobuttonTriangle";
		this.radiobuttonTriangle.Size = new System.Drawing.Size(69, 16);
		this.radiobuttonTriangle.TabIndex = 32;
		this.radiobuttonTriangle.Text = "Triangle";
		this.radiobuttonTriangle.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonSquare
		// 
		this.radiobuttonSquare.Location = new System.Drawing.Point(88, 16);
		this.radiobuttonSquare.Name = "radiobuttonSquare";
		this.radiobuttonSquare.Size = new System.Drawing.Size(64, 16);
		this.radiobuttonSquare.TabIndex = 33;
		this.radiobuttonSquare.Text = "Square";
		this.radiobuttonSquare.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonRadioSine
		// 
		this.radiobuttonRadioSine.Location = new System.Drawing.Point(152, 16);
		this.radiobuttonRadioSine.Name = "radiobuttonRadioSine";
		this.radiobuttonRadioSine.Size = new System.Drawing.Size(48, 16);
		this.radiobuttonRadioSine.TabIndex = 34;
		this.radiobuttonRadioSine.Text = "Sine";
		this.radiobuttonRadioSine.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// groupboxFrameWaveform
		// 
		this.groupboxFrameWaveform.Controls.Add(this.radiobuttonSquare);
		this.groupboxFrameWaveform.Controls.Add(this.radiobuttonTriangle);
		this.groupboxFrameWaveform.Controls.Add(this.radiobuttonRadioSine);
		this.groupboxFrameWaveform.Location = new System.Drawing.Point(180, 400);
		this.groupboxFrameWaveform.Name = "groupboxFrameWaveform";
		this.groupboxFrameWaveform.Size = new System.Drawing.Size(225, 42);
		this.groupboxFrameWaveform.TabIndex = 35;
		this.groupboxFrameWaveform.TabStop = false;
		this.groupboxFrameWaveform.Text = "Waveform";
		// 
		// buttonOpen
		// 
		this.buttonOpen.Location = new System.Drawing.Point(12, 12);
		this.buttonOpen.Name = "buttonOpen";
		this.buttonOpen.TabIndex = 47;
		this.buttonOpen.Text = "&Open File";
		this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
		// 
		// labelTextFilename
		// 
		this.labelTextFilename.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelTextFilename.Location = new System.Drawing.Point(94, 14);
		this.labelTextFilename.Name = "labelTextFilename";
		this.labelTextFilename.Size = new System.Drawing.Size(595, 20);
		this.labelTextFilename.TabIndex = 48;
		this.labelTextFilename.Text = "Filename";
		this.labelTextFilename.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
		// 
		// labelStatic2
		// 
		this.labelStatic2.Location = new System.Drawing.Point(19, 44);
		this.labelStatic2.Name = "labelStatic2";
		this.labelStatic2.Size = new System.Drawing.Size(67, 16);
		this.labelStatic2.TabIndex = 49;
		this.labelStatic2.Text = "Status";
		// 
		// labelTextStatus
		// 
		this.labelTextStatus.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelTextStatus.Location = new System.Drawing.Point(94, 44);
		this.labelTextStatus.Name = "labelTextStatus";
		this.labelTextStatus.Size = new System.Drawing.Size(595, 20);
		this.labelTextStatus.TabIndex = 50;
		this.labelTextStatus.Text = "No file loaded.";
		this.labelTextStatus.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
		// 
		// checkboxLoop
		// 
		this.checkboxLoop.Location = new System.Drawing.Point(42, 376);
		this.checkboxLoop.Name = "checkboxLoop";
		this.checkboxLoop.Size = new System.Drawing.Size(86, 16);
		this.checkboxLoop.TabIndex = 51;
		this.checkboxLoop.Text = "&Loop Sound";
		this.checkboxLoop.CheckedChanged += new System.EventHandler(this.checkboxLoop_CheckedChanged);
		// 
		// buttonPlay
		// 
		this.buttonPlay.Location = new System.Drawing.Point(10, 400);
		this.buttonPlay.Name = "buttonPlay";
		this.buttonPlay.Size = new System.Drawing.Size(67, 23);
		this.buttonPlay.TabIndex = 52;
		this.buttonPlay.Text = "&Play";
		this.buttonPlay.Click += new System.EventHandler(this.buttonPlay_Click);
		// 
		// buttonStop
		// 
		this.buttonStop.Enabled = false;
		this.buttonStop.Location = new System.Drawing.Point(87, 400);
		this.buttonStop.Name = "buttonStop";
		this.buttonStop.Size = new System.Drawing.Size(67, 23);
		this.buttonStop.TabIndex = 53;
		this.buttonStop.Text = "&Stop";
		this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
		// 
		// labelStatic3
		// 
		this.labelStatic3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelStatic3.Location = new System.Drawing.Point(372, 88);
		this.labelStatic3.Name = "labelStatic3";
		this.labelStatic3.Size = new System.Drawing.Size(52, 16);
		this.labelStatic3.TabIndex = 62;
		this.labelStatic3.Text = "Min";
		this.labelStatic3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// labelStatic4
		// 
		this.labelStatic4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
		this.labelStatic4.Location = new System.Drawing.Point(627, 88);
		this.labelStatic4.Name = "labelStatic4";
		this.labelStatic4.Size = new System.Drawing.Size(52, 16);
		this.labelStatic4.TabIndex = 64;
		this.labelStatic4.Text = "Max";
		this.labelStatic4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
		// 
		// radiobuttonRadioNeg180
		// 
		this.radiobuttonRadioNeg180.Location = new System.Drawing.Point(16, 16);
		this.radiobuttonRadioNeg180.Name = "radiobuttonRadioNeg180";
		this.radiobuttonRadioNeg180.Size = new System.Drawing.Size(45, 16);
		this.radiobuttonRadioNeg180.TabIndex = 65;
		this.radiobuttonRadioNeg180.Text = "-180";
		this.radiobuttonRadioNeg180.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonRadioNeg90
		// 
		this.radiobuttonRadioNeg90.Location = new System.Drawing.Point(72, 16);
		this.radiobuttonRadioNeg90.Name = "radiobuttonRadioNeg90";
		this.radiobuttonRadioNeg90.Size = new System.Drawing.Size(39, 16);
		this.radiobuttonRadioNeg90.TabIndex = 66;
		this.radiobuttonRadioNeg90.Text = "-90";
		this.radiobuttonRadioNeg90.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonRadioZero
		// 
		this.radiobuttonRadioZero.Location = new System.Drawing.Point(120, 16);
		this.radiobuttonRadioZero.Name = "radiobuttonRadioZero";
		this.radiobuttonRadioZero.Size = new System.Drawing.Size(30, 16);
		this.radiobuttonRadioZero.TabIndex = 67;
		this.radiobuttonRadioZero.Text = "0";
		this.radiobuttonRadioZero.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonRadio90
		// 
		this.radiobuttonRadio90.Location = new System.Drawing.Point(152, 16);
		this.radiobuttonRadio90.Name = "radiobuttonRadio90";
		this.radiobuttonRadio90.Size = new System.Drawing.Size(36, 16);
		this.radiobuttonRadio90.TabIndex = 68;
		this.radiobuttonRadio90.Text = "90";
		this.radiobuttonRadio90.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// radiobuttonRadio180
		// 
		this.radiobuttonRadio180.Location = new System.Drawing.Point(200, 16);
		this.radiobuttonRadio180.Name = "radiobuttonRadio180";
		this.radiobuttonRadio180.Size = new System.Drawing.Size(42, 16);
		this.radiobuttonRadio180.TabIndex = 69;
		this.radiobuttonRadio180.Text = "180";
		this.radiobuttonRadio180.CheckedChanged += new System.EventHandler(this.trackbarSliderScroll);
		// 
		// groupboxFramePhase
		// 
		this.groupboxFramePhase.Controls.Add(this.radiobuttonRadioNeg180);
		this.groupboxFramePhase.Controls.Add(this.radiobuttonRadioNeg90);
		this.groupboxFramePhase.Controls.Add(this.radiobuttonRadioZero);
		this.groupboxFramePhase.Controls.Add(this.radiobuttonRadio90);
		this.groupboxFramePhase.Controls.Add(this.radiobuttonRadio180);
		this.groupboxFramePhase.Location = new System.Drawing.Point(420, 400);
		this.groupboxFramePhase.Name = "groupboxFramePhase";
		this.groupboxFramePhase.Size = new System.Drawing.Size(247, 42);
		this.groupboxFramePhase.TabIndex = 63;
		this.groupboxFramePhase.TabStop = false;
		this.groupboxFramePhase.Text = "Phase (Degrees)";
		// 
		// groupboxEffects
		// 
		this.groupboxEffects.Controls.Add(this.buttonDelete);
		this.groupboxEffects.Controls.Add(this.listboxEffects);
		this.groupboxEffects.Controls.Add(this.comboEffects);
		this.groupboxEffects.Location = new System.Drawing.Point(8, 80);
		this.groupboxEffects.Name = "groupboxEffects";
		this.groupboxEffects.Size = new System.Drawing.Size(144, 248);
		this.groupboxEffects.TabIndex = 71;
		this.groupboxEffects.TabStop = false;
		this.groupboxEffects.Text = "Effects";
		// 
		// buttonDelete
		// 
		this.buttonDelete.Location = new System.Drawing.Point(40, 216);
		this.buttonDelete.Name = "buttonDelete";
		this.buttonDelete.Size = new System.Drawing.Size(64, 24);
		this.buttonDelete.TabIndex = 3;
		this.buttonDelete.Text = "Delete";
		this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
		// 
		// listboxEffects
		// 
		this.listboxEffects.Location = new System.Drawing.Point(8, 48);
		this.listboxEffects.Name = "listboxEffects";
		this.listboxEffects.Size = new System.Drawing.Size(128, 160);
		this.listboxEffects.TabIndex = 2;
		this.listboxEffects.KeyUp += new System.Windows.Forms.KeyEventHandler(this.listboxEffects_KeyUp);
		this.listboxEffects.SelectedIndexChanged += new System.EventHandler(this.listboxEffects_SelectedIndexChanged);
		// 
		// comboEffects
		// 
		this.comboEffects.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
		this.comboEffects.Items.AddRange(new object[] {
														  "Chorus",
														  "Compressor",
														  "Distortion",
														  "Echo",
														  "Flanger",
														  "Gargle",
														  "Waves Reverb",
														  "ParamEq"});
		this.comboEffects.Location = new System.Drawing.Point(8, 16);
		this.comboEffects.Name = "comboEffects";
		this.comboEffects.Size = new System.Drawing.Size(128, 21);
		this.comboEffects.TabIndex = 1;
		this.comboEffects.SelectedValueChanged += new System.EventHandler(this.comboEffects_SelectedValueChanged);
		// 
		// timer1
		// 
		this.timer1.Interval = 500;
		this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
		// 
		// lblMaxFreq
		// 
		this.lblMaxFreq.Location = new System.Drawing.Point(408, 472);
		this.lblMaxFreq.Name = "lblMaxFreq";
		this.lblMaxFreq.Size = new System.Drawing.Size(47, 20);
		this.lblMaxFreq.TabIndex = 74;
		this.lblMaxFreq.Text = "100 KHz";
		this.lblMaxFreq.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// lblMinFreq
		// 
		this.lblMinFreq.Location = new System.Drawing.Point(144, 472);
		this.lblMinFreq.Name = "lblMinFreq";
		this.lblMinFreq.Size = new System.Drawing.Size(41, 20);
		this.lblMinFreq.TabIndex = 75;
		this.lblMinFreq.Text = "100 Hz";
		this.lblMinFreq.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// textFreq
		// 
		this.textFreq.Location = new System.Drawing.Point(96, 472);
		this.textFreq.Name = "textFreq";
		this.textFreq.ReadOnly = true;
		this.textFreq.Size = new System.Drawing.Size(43, 20);
		this.textFreq.TabIndex = 72;
		this.textFreq.Text = "0";
		// 
		// tbarFreq
		// 
		this.tbarFreq.LargeChange = 1000;
		this.tbarFreq.Location = new System.Drawing.Point(176, 464);
		this.tbarFreq.Maximum = 100000;
		this.tbarFreq.Minimum = 100;
		this.tbarFreq.Name = "tbarFreq";
		this.tbarFreq.Size = new System.Drawing.Size(236, 45);
		this.tbarFreq.SmallChange = 100;
		this.tbarFreq.TabIndex = 76;
		this.tbarFreq.TickFrequency = 10000;
		this.tbarFreq.Value = 100;
		this.tbarFreq.MouseDown += new System.Windows.Forms.MouseEventHandler(this.tbarFreq_MouseDown);
		this.tbarFreq.Scroll += new System.EventHandler(this.tbarFreq_Scroll);
		// 
		// label2
		// 
		this.label2.Location = new System.Drawing.Point(16, 464);
		this.label2.Name = "label2";
		this.label2.Size = new System.Drawing.Size(73, 38);
		this.label2.TabIndex = 73;
		this.label2.Text = "Frequency";
		this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// textVolume
		// 
		this.textVolume.Location = new System.Drawing.Point(96, 552);
		this.textVolume.Name = "textVolume";
		this.textVolume.ReadOnly = true;
		this.textVolume.Size = new System.Drawing.Size(43, 20);
		this.textVolume.TabIndex = 80;
		this.textVolume.Text = "0";
		// 
		// label8
		// 
		this.label8.Location = new System.Drawing.Point(144, 552);
		this.label8.Name = "label8";
		this.label8.Size = new System.Drawing.Size(41, 20);
		this.label8.TabIndex = 84;
		this.label8.Text = "Low";
		this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// label9
		// 
		this.label9.Location = new System.Drawing.Point(408, 552);
		this.label9.Name = "label9";
		this.label9.Size = new System.Drawing.Size(47, 20);
		this.label9.TabIndex = 85;
		this.label9.Text = "High";
		this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// label10
		// 
		this.label10.Location = new System.Drawing.Point(16, 544);
		this.label10.Name = "label10";
		this.label10.Size = new System.Drawing.Size(73, 38);
		this.label10.TabIndex = 86;
		this.label10.Text = "Volume";
		this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// tbarVolume
		// 
		this.tbarVolume.Location = new System.Drawing.Point(176, 544);
		this.tbarVolume.Maximum = 1000;
		this.tbarVolume.Name = "tbarVolume";
		this.tbarVolume.Size = new System.Drawing.Size(236, 45);
		this.tbarVolume.TabIndex = 87;
		this.tbarVolume.TickFrequency = 25;
		this.tbarVolume.Value = 1000;
		this.tbarVolume.Scroll += new System.EventHandler(this.tbarVolume_Scroll);
		// 
		// label5
		// 
		this.label5.Location = new System.Drawing.Point(144, 512);
		this.label5.Name = "label5";
		this.label5.Size = new System.Drawing.Size(41, 20);
		this.label5.TabIndex = 81;
		this.label5.Text = "Left";
		this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// label6
		// 
		this.label6.Location = new System.Drawing.Point(408, 512);
		this.label6.Name = "label6";
		this.label6.Size = new System.Drawing.Size(47, 20);
		this.label6.TabIndex = 82;
		this.label6.Text = "Right";
		this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// tbarPan
		// 
		this.tbarPan.Location = new System.Drawing.Point(176, 504);
		this.tbarPan.Maximum = 20;
		this.tbarPan.Minimum = -20;
		this.tbarPan.Name = "tbarPan";
		this.tbarPan.Size = new System.Drawing.Size(236, 45);
		this.tbarPan.TabIndex = 88;
		this.tbarPan.TickFrequency = 5;
		this.tbarPan.MouseDown += new System.Windows.Forms.MouseEventHandler(this.tbarPan_MouseDown);
		this.tbarPan.Scroll += new System.EventHandler(this.tbarPan_Scroll);
		// 
		// textPan
		// 
		this.textPan.Location = new System.Drawing.Point(96, 512);
		this.textPan.Name = "textPan";
		this.textPan.ReadOnly = true;
		this.textPan.Size = new System.Drawing.Size(43, 20);
		this.textPan.TabIndex = 79;
		this.textPan.Text = "0";
		// 
		// label7
		// 
		this.label7.Location = new System.Drawing.Point(16, 504);
		this.label7.Name = "label7";
		this.label7.Size = new System.Drawing.Size(73, 38);
		this.label7.TabIndex = 83;
		this.label7.Text = "Pan";
		this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
		// 
		// timer2
		// 
		this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
		// 
		// label3
		// 
		this.label3.Location = new System.Drawing.Point(8, 336);
		this.label3.Name = "label3";
		this.label3.Size = new System.Drawing.Size(152, 24);
		this.label3.TabIndex = 89;
		this.label3.Text = "label3 - POS";
		// 
		// richTextBox1
		// 
		this.richTextBox1.Location = new System.Drawing.Point(696, 8);
		this.richTextBox1.Name = "richTextBox1";
		this.richTextBox1.Size = new System.Drawing.Size(232, 328);
		this.richTextBox1.TabIndex = 92;
		this.richTextBox1.Text = "richTextBox1";
		// 
		// pictureBox1
		// 
		this.pictureBox1.Location = new System.Drawing.Point(416, 464);
		this.pictureBox1.Name = "pictureBox1";
		this.pictureBox1.Size = new System.Drawing.Size(512, 128);
		this.pictureBox1.TabIndex = 93;
		this.pictureBox1.TabStop = false;
		// 
		// timer3
		// 
		this.timer3.Interval = 50;
		this.timer3.Tick += new System.EventHandler(this.timer3_Tick);
		// 
		// pictureBox2
		// 
		this.pictureBox2.Location = new System.Drawing.Point(696, 344);
		this.pictureBox2.Name = "pictureBox2";
		this.pictureBox2.Size = new System.Drawing.Size(232, 112);
		this.pictureBox2.TabIndex = 94;
		this.pictureBox2.TabStop = false;
		// 
		// timer4
		// 
		this.timer4.Interval = 200;
		this.timer4.Tick += new System.EventHandler(this.timer4_Tick);
		// 
		// label1
		// 
		this.label1.Location = new System.Drawing.Point(8, 592);
		this.label1.Name = "label1";
		this.label1.Size = new System.Drawing.Size(48, 16);
		this.label1.TabIndex = 95;
		this.label1.Text = "label1";
		// 
		// label4
		// 
		this.label4.Location = new System.Drawing.Point(56, 592);
		this.label4.Name = "label4";
		this.label4.Size = new System.Drawing.Size(40, 16);
		this.label4.TabIndex = 96;
		this.label4.Text = "label4";
		// 
		// label11
		// 
		this.label11.Location = new System.Drawing.Point(96, 592);
		this.label11.Name = "label11";
		this.label11.Size = new System.Drawing.Size(48, 16);
		this.label11.TabIndex = 97;
		this.label11.Text = "label11";
		// 
		// timer5
		// 
		this.timer5.Enabled = true;
		this.timer5.Interval = 30;
		this.timer5.Tick += new System.EventHandler(this.timer5_Tick);
		// 
		// trackBar1
		// 
		this.trackBar1.Location = new System.Drawing.Point(176, 584);
		this.trackBar1.Maximum = 10000;
		this.trackBar1.Name = "trackBar1";
		this.trackBar1.Size = new System.Drawing.Size(224, 45);
		this.trackBar1.TabIndex = 0;
		this.trackBar1.TickFrequency = 2000;
		this.trackBar1.Value = 107;
		// 
		// trackBar2
		// 
		this.trackBar2.Location = new System.Drawing.Point(400, 592);
		this.trackBar2.Maximum = 120;
		this.trackBar2.Minimum = 1;
		this.trackBar2.Name = "trackBar2";
		this.trackBar2.Size = new System.Drawing.Size(528, 45);
		this.trackBar2.TabIndex = 98;
		this.trackBar2.TickFrequency = 100;
		this.trackBar2.Value = 7;
		// 
		// trackBar3
		// 
		this.trackBar3.LargeChange = 100;
		this.trackBar3.Location = new System.Drawing.Point(400, 456);
		this.trackBar3.Maximum = 20000;
		this.trackBar3.Minimum = 20;
		this.trackBar3.Name = "trackBar3";
		this.trackBar3.Size = new System.Drawing.Size(528, 45);
		this.trackBar3.SmallChange = 10;
		this.trackBar3.TabIndex = 99;
		this.trackBar3.TickFrequency = 1000;
		this.trackBar3.Value = 20;
		this.trackBar3.Scroll += new System.EventHandler(this.trackBar3_Scroll);
		// 
		// MainForm
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
		this.ClientSize = new System.Drawing.Size(930, 616);
		this.Controls.Add(this.trackBar3);
		this.Controls.Add(this.pictureBox1);
		this.Controls.Add(this.trackBar2);
		this.Controls.Add(this.label11);
		this.Controls.Add(this.label4);
		this.Controls.Add(this.label1);
		this.Controls.Add(this.pictureBox2);
		this.Controls.Add(this.richTextBox1);
		this.Controls.Add(this.label3);
		this.Controls.Add(this.textVolume);
		this.Controls.Add(this.label8);
		this.Controls.Add(this.label9);
		this.Controls.Add(this.label10);
		this.Controls.Add(this.tbarVolume);
		this.Controls.Add(this.label5);
		this.Controls.Add(this.label6);
		this.Controls.Add(this.tbarPan);
		this.Controls.Add(this.textPan);
		this.Controls.Add(this.label7);
		this.Controls.Add(this.lblMaxFreq);
		this.Controls.Add(this.lblMinFreq);
		this.Controls.Add(this.textFreq);
		this.Controls.Add(this.tbarFreq);
		this.Controls.Add(this.label2);
		this.Controls.Add(this.groupboxEffects);
		this.Controls.Add(this.buttonOk);
		this.Controls.Add(this.labelParamName1);
		this.Controls.Add(this.labelParamValue1);
		this.Controls.Add(this.trackbarSlider1);
		this.Controls.Add(this.labelParamMin1);
		this.Controls.Add(this.labelParamMax1);
		this.Controls.Add(this.labelParamName2);
		this.Controls.Add(this.labelParamValue2);
		this.Controls.Add(this.trackbarSlider2);
		this.Controls.Add(this.labelParamMin2);
		this.Controls.Add(this.labelParamMax2);
		this.Controls.Add(this.labelParamName3);
		this.Controls.Add(this.labelParamValue3);
		this.Controls.Add(this.trackbarSlider3);
		this.Controls.Add(this.labelParamMin3);
		this.Controls.Add(this.labelParamMax3);
		this.Controls.Add(this.labelParamName4);
		this.Controls.Add(this.labelParamValue4);
		this.Controls.Add(this.trackbarSlider4);
		this.Controls.Add(this.labelParamMin4);
		this.Controls.Add(this.labelParamMax4);
		this.Controls.Add(this.labelParamName5);
		this.Controls.Add(this.labelParamValue5);
		this.Controls.Add(this.trackbarSlider5);
		this.Controls.Add(this.labelParamMin5);
		this.Controls.Add(this.labelParamMax5);
		this.Controls.Add(this.labelParamName6);
		this.Controls.Add(this.labelParamValue6);
		this.Controls.Add(this.trackbarSlider6);
		this.Controls.Add(this.labelParamMin6);
		this.Controls.Add(this.labelParamMax6);
		this.Controls.Add(this.buttonOpen);
		this.Controls.Add(this.labelTextFilename);
		this.Controls.Add(this.labelStatic2);
		this.Controls.Add(this.labelTextStatus);
		this.Controls.Add(this.checkboxLoop);
		this.Controls.Add(this.buttonPlay);
		this.Controls.Add(this.buttonStop);
		this.Controls.Add(this.labelStatic3);
		this.Controls.Add(this.labelStatic4);
		this.Controls.Add(this.groupboxFrameWaveform);
		this.Controls.Add(this.groupboxFramePhase);
		this.Controls.Add(this.groupboxFrame);
		this.Controls.Add(this.trackBar1);
		this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
		this.Location = new System.Drawing.Point(150, 160);
		this.MaximizeBox = false;
		this.Name = "MainForm";
		this.Text = "SoundFX - Sound effects applied to Device.SecondaryBuffer";
		this.Closing += new System.ComponentModel.CancelEventHandler(this.MainForm_Closing);
		this.Load += new System.EventHandler(this.MainForm_Load);
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider1)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider2)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider3)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider4)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider5)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackbarSlider6)).EndInit();
		this.groupboxFrameWaveform.ResumeLayout(false);
		this.groupboxFramePhase.ResumeLayout(false);
		this.groupboxEffects.ResumeLayout(false);
		((System.ComponentModel.ISupportInitialize)(this.tbarFreq)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.tbarVolume)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.tbarPan)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar2)).EndInit();
		((System.ComponentModel.ISupportInitialize)(this.trackBar3)).EndInit();
		this.ResumeLayout(false);

	}
    #endregion
	private void InitDirectSound()
	{
		BufferDescription description = new BufferDescription();
		WaveFormat wfx = new WaveFormat();

		applicationDevice = new Device();
		applicationDevice.SetCooperativeLevel(this, CooperativeLevel.Normal);		
	}
	private void buttonOpen_Click(object sender, System.EventArgs e)
	{
		BufferDescription description = new BufferDescription();

		OpenFileDialog ofd = new OpenFileDialog();

		labelTextStatus.Text = "Loading file...";
		// Get the default media path (something like C:\WINDOWS\MEDIA)
		if (string.Empty == path)
			path = Environment.SystemDirectory.Substring(0, Environment.SystemDirectory.LastIndexOf("\\")) + "\\media";

		ofd.DefaultExt = ".wav";
		ofd.Filter = "Wave Files|*.wav|All Files|*.*";
		ofd.FileName = fileName;
		ofd.InitialDirectory = path;
		ofd.InitialDirectory = @"C:\Documents and Settings\Rock\My Documents\My Music\Various Artists\Iasca Test Software #2";

		if (null != applicationBuffer)
		{
			applicationBuffer.Stop();
			applicationBuffer.SetCurrentPosition(0);
		}

		// Display the OpenFileName dialog. Then, try to load the specified file
		if (DialogResult.Cancel == ofd.ShowDialog(this))
		{
            if(null != applicationBuffer)
                applicationBuffer.Dispose();

			labelTextStatus.Text = "No file loaded.";
			return;
		}
		fileName = string.Empty;

		description.ControlEffects = true;
		description.ControlFrequency = true;
		description.ControlPan = true;
		description.ControlVolume = true;
		description.GlobalFocus = true;
    
        // Create a SecondaryBuffer using the file name.
        try
        {
            applicationBuffer = new SecondaryBuffer(ofd.FileName, description,  applicationDevice);

			int ABPS = description.Format.AverageBytesPerSecond;
			int	SPS = description.Format.SamplesPerSecond;
			int BPS = description.Format.BitsPerSample;
			int BB	= description.BufferBytes;
			tbarFreq.Value = SPS;
			textFreq.Text = tbarFreq.Value.ToString();
			lastGoodFrequency = SPS;
        }
        catch(BufferTooSmallException)
        {
            labelTextStatus.Text = "Wave file is too small to be used with effects.";
            return;
        }
        catch(FormatException)
        {
            // Invalid file was used. Managed DirectSound tries to convert any files less than
            // 8 bit to 8 bit. Some drivers don't support this conversion, so make sure to
            // catch the FormatException if it's thrown.
            labelTextStatus.Text = "Failed to create SecondaryBuffer from selected file.";
            return;
        }
        
		// Remember the file for next time
		if (null != applicationBuffer)
		{
			fileName = ofd.FileName;
			path =  fileName.Substring(0, fileName.LastIndexOf("\\"));
		}
		labelTextFilename.Text = fileName;
		labelTextStatus.Text = "File loaded.";
	}

	private void buttonPlay_Click(object sender, System.EventArgs e)
	{
		richTextBox1.Clear();
		BufferPlayFlags	bpf	= new BufferPlayFlags();

		if (null != applicationBuffer)
        {
			applicationBuffer.Play(0, (shouldLoop == true) ? BufferPlayFlags.Looping : BufferPlayFlags.Default);

            timer1.Enabled = true;
            labelTextStatus.Text="Sound playing.";

			buttonPlay.Enabled=false;
			buttonStop.Enabled=true;
			checkboxLoop.Enabled=false;
        }
    }

	private void tbarFreq_Scroll(object sender, System.EventArgs e)
	{
		int newFrequency = 0;
		if (null != applicationBuffer)
		{
			try
			{
				newFrequency = ((TrackBar)sender).Value;
				// Attempt to set the frequency to the new value
				applicationBuffer.Frequency = newFrequency;
				textFreq.Text = newFrequency.ToString();
				lastGoodFrequency = newFrequency;
			}
			catch 
			{
				// Let's try to guess why it failed..
				if ((applicationBuffer.Caps.LocateInHardware) && (newFrequency > applicationDevice.Caps.MaxSecondarySampleRate))
				{
					labelTextStatus.Text = "Hardware buffers don't support greater than Caps.MaxSecondarySampleRate";
				}
				else if (100000 < newFrequency)
				{
					// Some platforms (pre-WinXP SP1) don't support 
					// >100k Hz so they will fail when setting it higher
					labelTextStatus.Text = "Some OS platforms do not support >100k Hz";
				}
				else
				{
					labelTextStatus.Text = "Setting the frequency failed";
				}
				// Reset to the last valid frequency
				applicationBuffer.Frequency = lastGoodFrequency;
				((TrackBar)sender).Value = lastGoodFrequency;
			}
		}
	}

	private void tbarPan_Scroll(object sender, System.EventArgs e)
	{
		if (null != applicationBuffer)
		{
			textPan.Text = ((TrackBar)sender).Value.ToString();
			applicationBuffer.Pan = ((TrackBar)sender).Value * 500;
		}
	}

	private void tbarVolume_Scroll(object sender, System.EventArgs e)
	{
//		if (null != applicationBuffer)
//		{
//			textVolume.Text = ((TrackBar)sender).Value.ToString();
//			applicationBuffer.Volume = ((TrackBar)sender).Value * 100;
//		}

		float fVol = tbarVolume.Value;
		fVol /= 1000;

		int vol =  (int)(-2000.0 * Math.Log10(1.0f / fVol));

		if (vol < -5000)
			vol = -5000;
		if (vol > 0)
			vol = 0;

		textVolume.Text = vol.ToString();//+ " "+ tbarVolume.Value.ToString();
		if (null != applicationBuffer)
			applicationBuffer.Volume = vol; 
		//((TrackBar)sender).Value * 100;

		double vol1;
		vol1 = Math.Log10(1.0f/fVol);
		//vol1 = Math.Log(1.0f/fVol);
		vol1 *= (1024/3);
		label1.Text = vol1.ToString("g");
	}
	private void buttonStop_Click(object sender, System.EventArgs e)
	{
		if (null != applicationBuffer)
			if (applicationBuffer.Status.Playing == true)
			{
				applicationBuffer.Stop();
				applicationBuffer.SetCurrentPosition(0);
                timer1.Enabled = false;
                labelTextStatus.Text="Sound stopped.";

				buttonPlay.Enabled=true;
				buttonStop.Enabled=false;
				checkboxLoop.Enabled=true;
            }
	}
	private void comboEffects_SelectedValueChanged(object sender, System.EventArgs e)
	{
		string description	= string.Empty;

		if (null == applicationBuffer)
			return;

		EffectInfo[] temp = new EffectInfo[effectDescription.Count + 1];
		effectDescription.CopyTo(temp, 0);

		switch (comboEffects.SelectedIndex)
		{
			case 0:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardChorusGuid;
				description = "Chorus";
				break;
			case 1:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardCompressorGuid;
				description = "Compressor";
				break;
			case 2:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardDistortionGuid;
				description = "Distortion";
				break;
			case 3:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardEchoGuid;
				description = "Echo";
				break;
			case 4:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardFlangerGuid;
				description = "Flanger";
				break;
			case 5:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardGargleGuid;
				description = "Gargle";
				break;
			case 6:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardWavesReverbGuid;
				description = "Waves Reverb";
				break;
			case 7:
				temp[temp.Length - 1].description.GuidEffectClass = DSoundHelper.StandardParamEqGuid;
				description = "ParamEq";
				break;
		}		
		
		if (AddEffect(temp))
		{
			effectDescription.Clear();
			effectDescription.AddRange(temp);
			listboxEffects.Items.Add(description);
			listboxEffects.SelectedIndex = listboxEffects.Items.Count - 1;
		}
		
	}
	private bool AddEffect(EffectInfo[] temp)
	{
		EffectsReturnValue[] ret = null;
		EffectDescription[] fx = null;		
		bool WasPlaying	= false;		
		int count = 0;

		if (null != temp)
		{
			fx = new EffectDescription[temp.Length];
			count = temp.Length;
		}

		if (true == applicationBuffer.Status.Playing)
			WasPlaying = true;
		
		applicationBuffer.Stop();
		
		// Store the current params for each effect.
		for (int i=0; i < count; i++)
			fx[i] = ((EffectInfo)temp[i]).description;

		try
		{
			ret = applicationBuffer.SetEffects(fx);
		}
		catch(DirectXException)
		{
			labelTextStatus.Text = "Unable to set effect on the buffer. Some effects can't be set on 8 bit wave files.";

			// Revert to the last valid effects.
            if(temp.Length <= 1)
                return false;

			fx = new EffectDescription[temp.Length -1];;
			for (int i=0; i < count - 1; i++)
				fx[i] = ((EffectInfo)temp[i]).description;

			try{ applicationBuffer.SetEffects(fx); }
			catch(DirectXException){}

			return false;
		}
		
		// Restore the params for each effect.
		for (int i=0; i < count; i++)
		{
			EffectInfo eff = new EffectInfo();

			eff.Effect = applicationBuffer.GetEffects(i);
			eff.EffectSettings = temp[i].EffectSettings;
			eff.description = temp[i].description;

			Type efftype = eff.Effect.GetType();

			if (typeof(ChorusEffect) == efftype)
				if (null != eff.EffectSettings)
					((ChorusEffect)eff.Effect).AllParameters = (EffectsChorus)eff.EffectSettings;
				else
					eff.EffectSettings = ((ChorusEffect)eff.Effect).AllParameters;
			else if (typeof(CompressorEffect) ==efftype)
				if (null != eff.EffectSettings)
					((CompressorEffect)eff.Effect).AllParameters = (EffectsCompressor)eff.EffectSettings;
				else
					eff.EffectSettings = ((CompressorEffect)eff.Effect).AllParameters;
			else if (typeof(DistortionEffect) == efftype)
				if (null != eff.EffectSettings)
					((DistortionEffect)eff.Effect).AllParameters = (EffectsDistortion)eff.EffectSettings;
				else
					eff.EffectSettings = ((DistortionEffect)eff.Effect).AllParameters;
			else if (typeof(EchoEffect) == efftype)
				if (null != eff.EffectSettings)
					((EchoEffect)eff.Effect).AllParameters = (EffectsEcho)eff.EffectSettings;
				else
					eff.EffectSettings = ((EchoEffect)eff.Effect).AllParameters;
			else if (typeof(FlangerEffect) == efftype)
					 if (null != eff.EffectSettings)
						 ((FlangerEffect)eff.Effect).AllParameters = (EffectsFlanger)eff.EffectSettings;
					 else
						 eff.EffectSettings = ((FlangerEffect)eff.Effect).AllParameters;
			else if (typeof(GargleEffect) == efftype)
					 if (null != eff.EffectSettings)
						 ((GargleEffect)eff.Effect).AllParameters = (EffectsGargle)eff.EffectSettings;
					 else
						 eff.EffectSettings = ((GargleEffect)eff.Effect).AllParameters;
			else if (typeof(ParamEqEffect) == efftype)
					 if (null != eff.EffectSettings)
						 ((ParamEqEffect)eff.Effect).AllParameters = (EffectsParamEq)eff.EffectSettings;
					 else
						 eff.EffectSettings = ((ParamEqEffect)eff.Effect).AllParameters;
			else if (typeof(WavesReverbEffect) == efftype)
					 if (null != eff.EffectSettings)
						 ((WavesReverbEffect)eff.Effect).AllParameters = (EffectsWavesReverb)eff.EffectSettings;
					 else
						 eff.EffectSettings = ((WavesReverbEffect)eff.Effect).AllParameters;

			temp[i] = eff;
		}
		
		if (WasPlaying)
			applicationBuffer.Play(0, (shouldLoop == true) ? BufferPlayFlags.Looping : BufferPlayFlags.Default);

		if (null != temp)
			if ((EffectsReturnValue.LocatedInHardware == ret[temp.Length - 1]) || (EffectsReturnValue.LocatedInSoftware == ret[temp.Length - 1]))
				return true;

		return false;
	}
	private void checkboxLoop_CheckedChanged(object sender, System.EventArgs e)
	{
		shouldLoop = checkboxLoop.Checked;
	}
	private void listboxEffects_SelectedIndexChanged(object sender, System.EventArgs e)
	{
		if (-1 == listboxEffects.SelectedIndex)
			return;

		currentIndex = listboxEffects.SelectedIndex;

		UpdateUI(true);
	}
	private void UpdateUI(bool MoveControls)
	{
		ClearUI(MoveControls);
		
		Type	efftype = ((EffectInfo)effectDescription[currentIndex]).Effect.GetType();
		object	eff		= ((EffectInfo)effectDescription[currentIndex]).Effect;

		if (typeof(ChorusEffect) == efftype)
		{
			EffectsChorus temp = ((ChorusEffect)eff).AllParameters;

			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)ChorusEffect.WetDryMixMin;
				trackbarSlider1.Maximum = (int)ChorusEffect.WetDryMixMax;
				trackbarSlider1.Value = (int)temp.WetDryMix;
				trackbarSlider2.Minimum = (int)ChorusEffect.DepthMin;
				trackbarSlider2.Maximum = (int)ChorusEffect.DepthMax;
				trackbarSlider2.Value = (int)temp.Depth;
				trackbarSlider3.Minimum = (int)ChorusEffect.FeedbackMin;
				trackbarSlider3.Maximum = (int)ChorusEffect.FeedbackMax;
				trackbarSlider3.Value = (int)temp.Feedback;
				trackbarSlider4.Minimum = (int)ChorusEffect.FrequencyMin;
				trackbarSlider4.Maximum = (int)ChorusEffect.FrequencyMax;
				trackbarSlider4.Value = (int)temp.Frequency;
				trackbarSlider5.Minimum = (int)ChorusEffect.DelayMin;
				trackbarSlider5.Maximum = (int)ChorusEffect.DelayMax;
				trackbarSlider5.Value = (int)temp.Delay;

				if (ChorusEffect.WaveSin == temp.Waveform)
					radiobuttonRadioSine.Checked = true;
				else
					radiobuttonTriangle.Checked = true;

				if (ChorusEffect.PhaseNegative180 == temp.Phase)
					radiobuttonRadioNeg180.Checked = true;
				else if (ChorusEffect.PhaseNegative90 == temp.Phase)
					radiobuttonRadioNeg90.Checked = true;
				else if (ChorusEffect.PhaseZero == temp.Phase)
					radiobuttonRadioZero.Checked = true;
				else if (ChorusEffect.Phase90 == temp.Phase)
					radiobuttonRadio90.Checked = true;
				else if (ChorusEffect.Phase180 == temp.Phase)
					radiobuttonRadio180.Checked = true;

				groupboxFramePhase.Enabled = radiobuttonRadioNeg180.Enabled = radiobuttonRadioNeg90.Enabled = 
				radiobuttonRadioZero.Enabled = radiobuttonRadio90.Enabled = radiobuttonRadio180.Enabled = 
				groupboxFrameWaveform.Enabled = radiobuttonRadioSine.Enabled = 
                radiobuttonTriangle.Enabled = true;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
				trackbarSlider4.Enabled = trackbarSlider5.Enabled = true;
			}
			labelParamValue1.Text = temp.WetDryMix.ToString();
			labelParamName1.Text = "Wet/Dry Mix (%)";
			
			labelParamValue2.Text =  temp.Depth.ToString();
			labelParamName2.Text = "Depth (%)";

			labelParamValue3.Text = temp.Feedback.ToString();
			labelParamName3.Text = "Feedback (%)";

			labelParamValue4.Text = temp.Frequency.ToString();
			labelParamName4.Text = "Frequency (Hz)";

			labelParamValue5.Text = temp.Delay.ToString();
			labelParamName5.Text = "Delay (ms)" ;
		}
		else if (typeof(CompressorEffect) == efftype)
		{
			EffectsCompressor temp = ((CompressorEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)CompressorEffect.GainMin;
				trackbarSlider1.Maximum = (int)CompressorEffect.GainMax;
				trackbarSlider1.Value = (int)temp.Gain;
				trackbarSlider2.Minimum = (int)CompressorEffect.AttackMin;
				trackbarSlider2.Maximum = (int)CompressorEffect.AttackMax;
				trackbarSlider2.Value = (int)temp.Attack;
				trackbarSlider3.Minimum = (int)CompressorEffect.ReleaseMin;
				trackbarSlider3.Maximum = (int)CompressorEffect.ReleaseMax;
				trackbarSlider3.Value = (int)temp.Release;
				trackbarSlider4.Minimum = (int)CompressorEffect.ThresholdMin;
				trackbarSlider4.Maximum = (int)CompressorEffect.ThresholdMax;
				trackbarSlider4.Value = (int)temp.Threshold;
				trackbarSlider5.Minimum = (int)CompressorEffect.RatioMin;
				trackbarSlider5.Maximum = (int)CompressorEffect.RatioMax;
				trackbarSlider5.Value = (int)temp.Ratio;
				trackbarSlider6.Minimum = (int)CompressorEffect.PreDelayMin;
				trackbarSlider6.Maximum = (int)CompressorEffect.PreDelayMax;
				trackbarSlider6.Value = (int)temp.Predelay;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
					trackbarSlider4.Enabled = trackbarSlider5.Enabled = trackbarSlider6.Enabled = true;
			}
			labelParamValue1.Text = temp.Gain.ToString();
			labelParamName1.Text = "Gain (dB)";

			labelParamName2.Text = "Attack (ms)";
			labelParamValue2.Text = temp.Attack.ToString();
			
			labelParamName3.Text = "Release (ms)";
			labelParamValue3.Text = temp.Release.ToString();
			
			labelParamName4.Text = "Threshold (dB)";
			labelParamValue4.Text = temp.Threshold.ToString();
			
			labelParamName5.Text = "Ratio (x:1)";
			labelParamValue5.Text = temp.Ratio.ToString();
			
			labelParamName6.Text = "Predelay (ms)";
			labelParamValue6.Text = temp.Predelay.ToString();
		}
		else if (typeof(DistortionEffect) == efftype)
		{
			EffectsDistortion temp = ((DistortionEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)DistortionEffect.GainMin;
				trackbarSlider1.Maximum = (int)DistortionEffect.GainMax;
				trackbarSlider1.Value = (int)temp.Gain;
				trackbarSlider2.Minimum = (int)DistortionEffect.EdgeMin;
				trackbarSlider2.Maximum = (int)DistortionEffect.EdgeMax;
				trackbarSlider2.Value = (int)temp.Edge;
				trackbarSlider3.Minimum = (int)DistortionEffect.PostEqCenterFrequencyMin;
				trackbarSlider3.Maximum = (int)DistortionEffect.PostEqCenterFrequencyMax;
				trackbarSlider3.Value = (int)temp.PostEqCenterFrequency;
				trackbarSlider4.Minimum = (int)DistortionEffect.PostEqBandwidthMin;
				trackbarSlider4.Maximum = (int)DistortionEffect.PostEqBandwidthMax;
				trackbarSlider4.Value = (int)temp.PostEqBandwidth;
				trackbarSlider5.Minimum = (int)DistortionEffect.PreLowPassCutoffMin;
				trackbarSlider5.Maximum = (int)DistortionEffect.PreLowPassCutoffMax;
				trackbarSlider5.Value = (int)temp.PreLowpassCutoff;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
					trackbarSlider4.Enabled = trackbarSlider5.Enabled = true;
			}
			labelParamName1.Text = "Gain (dB)";
			labelParamValue1.Text = temp.Gain.ToString();
			
			labelParamName2.Text = "Edge (%)";
			labelParamValue2.Text = temp.Edge.ToString();
			
			labelParamName3.Text = "PostEQ Center Freq (Hz)";
			labelParamValue3.Text = temp.PostEqCenterFrequency.ToString();
			
			labelParamName4.Text = "PostEQ Bandwidth (Hz)";
			labelParamValue4.Text = temp.PostEqBandwidth.ToString();
			
			labelParamName5.Text = "PreLowpass Cutoff (Hz)";
			labelParamValue5.Text = temp.PreLowpassCutoff.ToString();
		}
		else if (typeof(EchoEffect) == efftype)
		{
			EffectsEcho temp = ((EchoEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)EchoEffect.WetDryMixMin;
				trackbarSlider1.Maximum = (int)EchoEffect.WetDryMixMax;
				trackbarSlider1.Value = (int)temp.WetDryMix;
				trackbarSlider2.Minimum = (int)EchoEffect.FeedbackMin;
				trackbarSlider2.Maximum = (int)EchoEffect.FeedbackMax;
				trackbarSlider2.Value = (int)temp.Feedback;
				trackbarSlider3.Minimum = (int)EchoEffect.LeftDelayMin;
				trackbarSlider3.Maximum = (int)EchoEffect.LeftDelayMax;
				trackbarSlider3.Value = (int)temp.LeftDelay;
				trackbarSlider4.Minimum = (int)EchoEffect.RightDelayMin;
				trackbarSlider4.Maximum = (int)EchoEffect.RightDelayMax;
				trackbarSlider4.Value = (int)temp.RightDelay;
				trackbarSlider5.Minimum = EchoEffect.PanDelayMin;
				trackbarSlider5.Maximum = EchoEffect.PanDelayMax;
				trackbarSlider5.Value = temp.PanDelay;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
				trackbarSlider4.Enabled = trackbarSlider5.Enabled = true;
			}
			labelParamName1.Text = "Wet/Dry Mix (%)";
			labelParamValue1.Text = temp.WetDryMix.ToString();
			
			labelParamName2.Text = "Feedback (%)";
			labelParamValue2.Text = temp.Feedback.ToString();
			
			labelParamName3.Text = "Left Delay (ms)";			
			labelParamValue3.Text = temp.LeftDelay.ToString();
						
			labelParamName4.Text = "Right Delay (ms)";
			labelParamValue4.Text = temp.RightDelay.ToString();
			
			labelParamName5.Text = "Pan Delay (bool)";
			labelParamValue5.Text = temp.PanDelay.ToString();
		}
		else if (typeof(FlangerEffect) == efftype)
		{
			EffectsFlanger temp = ((FlangerEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)FlangerEffect.WetDryMixMin;
				trackbarSlider1.Maximum = (int)FlangerEffect.WetDryMixMax;
				trackbarSlider1.Value = (int)temp.WetDryMix;
				trackbarSlider2.Minimum = (int)FlangerEffect.DepthMin;
				trackbarSlider2.Maximum = (int)FlangerEffect.DepthMax;
				trackbarSlider2.Value = (int)temp.Depth;
				trackbarSlider3.Minimum = (int)FlangerEffect.FeedbackMin;
				trackbarSlider3.Maximum = (int)FlangerEffect.FeedbackMax;
				trackbarSlider3.Value = (int)temp.Feedback;
				trackbarSlider4.Minimum = (int)FlangerEffect.FrequencyMin;
				trackbarSlider4.Maximum = (int)FlangerEffect.FrequencyMax;
				trackbarSlider4.Value = (int)temp.Frequency;
				trackbarSlider5.Minimum = (int)FlangerEffect.DelayMin;
				trackbarSlider5.Maximum = (int)FlangerEffect.DelayMax;
				trackbarSlider5.Value = (int)temp.Delay;

				if (ChorusEffect.WaveSin == temp.Waveform)
					radiobuttonRadioSine.Checked = true;
				else
					radiobuttonTriangle.Checked = true;
			
				if (FlangerEffect.PhaseNeg180 == temp.Phase)
					radiobuttonRadioNeg180.Checked = true;
				else if (FlangerEffect.PhaseNeg90 == temp.Phase)
					radiobuttonRadioNeg90.Checked = true;
				else if (FlangerEffect.PhaseZero == temp.Phase)
					radiobuttonRadioZero.Checked = true;
				else if (FlangerEffect.Phase90 == temp.Phase)
					radiobuttonRadio90.Checked = true;
				else if (FlangerEffect.Phase180 == temp.Phase)
					radiobuttonRadio180.Checked = true;

				groupboxFramePhase.Enabled = radiobuttonRadioNeg180.Enabled = radiobuttonRadioNeg90.Enabled = 
				radiobuttonRadioZero.Enabled = radiobuttonRadio90.Enabled = radiobuttonRadio180.Enabled = 
				groupboxFrameWaveform.Enabled = radiobuttonRadioSine.Enabled = radiobuttonTriangle.Enabled = true;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
				trackbarSlider4.Enabled = trackbarSlider5.Enabled = true;
			}
			labelParamName1.Text = "Wet/Dry Mix (%)";
			labelParamValue1.Text = temp.WetDryMix.ToString();
			
			labelParamName2.Text = "Depth (%)";
			labelParamValue2.Text = temp.Depth.ToString();
			
			labelParamName3.Text = "Feedback (%)";
			labelParamValue3.Text = temp.Feedback.ToString();
			
			labelParamName4.Text = "Frequency (Hz)";
			labelParamValue4.Text = temp.Frequency.ToString();
			
			labelParamName5.Text = "Delay (ms)";
			labelParamValue5.Text = temp.Delay.ToString();			
		}
		else if (typeof(GargleEffect) == efftype)
		{
			EffectsGargle temp = ((GargleEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = GargleEffect.RateHzMin;
				trackbarSlider1.Maximum = GargleEffect.RateHzMax;
				trackbarSlider1.Value = temp.RateHz;

				if (GargleEffect.WaveSquare == temp.WaveShape)
					radiobuttonSquare.Checked = true;
				else
					radiobuttonTriangle.Checked = true;

				groupboxFrameWaveform.Enabled = radiobuttonSquare.Enabled = radiobuttonTriangle.Enabled = true;

				trackbarSlider1.Enabled = true;
			}
			labelParamName1.Text = "Rate (Hz)";
			labelParamValue1.Text = temp.RateHz.ToString();		
		}
		else if (typeof(ParamEqEffect) == efftype)
		{
			EffectsParamEq temp = ((ParamEqEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)ParamEqEffect.CenterMin;
				trackbarSlider1.Maximum = (int)ParamEqEffect.CenterMax;
				trackbarSlider1.Value = (int)temp.Center;
				trackbarSlider2.Minimum = (int)ParamEqEffect.BandwidthMin;
				trackbarSlider2.Maximum = (int)ParamEqEffect.BandwidthMax;
				trackbarSlider2.Value = (int)temp.Bandwidth;
				trackbarSlider3.Minimum = (int)ParamEqEffect.GainMin;
				trackbarSlider3.Maximum = (int)ParamEqEffect.GainMax;
				trackbarSlider3.Value = (int)temp.Gain;

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = true;
			}
			labelParamName1.Text = "Center Freq (Hz)";
			labelParamValue1.Text = temp.Center.ToString();
			
			labelParamName2.Text = "Bandwidth (Hz)";
			labelParamValue2.Text = temp.Bandwidth.ToString();
			
			labelParamName3.Text = "Gain (dB)";
			labelParamValue3.Text = temp.Gain.ToString();
		}
		else if (typeof(WavesReverbEffect) == efftype)
		{
			EffectsWavesReverb temp = ((WavesReverbEffect)eff).AllParameters;
			
			if (MoveControls)
			{
				trackbarSlider1.Minimum = (int)WavesReverbEffect.InGainMin;
				trackbarSlider1.Maximum = (int)WavesReverbEffect.InGainMax;
				trackbarSlider1.Value = (int)temp.InGain;
				trackbarSlider2.Minimum = (int)WavesReverbEffect.ReverbMixMin;
				trackbarSlider2.Maximum = (int)WavesReverbEffect.ReverbMixMax;
				trackbarSlider2.Value = (int)temp.ReverbMix;
				trackbarSlider3.Minimum = (int)(1000 * WavesReverbEffect.ReverbTimeMin);
				trackbarSlider3.Maximum = (int)(1000 * WavesReverbEffect.ReverbTimeMax);
				trackbarSlider3.Value = (int)(1000 * temp.ReverbTime);
				trackbarSlider4.Minimum = (int)(1000 * WavesReverbEffect.HighFrequencyRtRatioMin);
				trackbarSlider4.Maximum = (int)(1000 * WavesReverbEffect.HighFrequencyRtRatioMax);
				trackbarSlider4.Value = (int)(1000 * temp.HighFrequencyRtRatio);

				trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = trackbarSlider4.Enabled = true;
			}
			labelParamName1.Text = "In Gain (dB)";
			labelParamValue1.Text = temp.InGain.ToString();
			
			labelParamName2.Text = "Waves Reverb Mix (dB)";
			labelParamValue2.Text = temp.ReverbMix.ToString();
			
			labelParamName3.Text = "Waves Reverb Time (ms)";
			labelParamValue3.Text = temp.ReverbTime.ToString();
			
			labelParamName4.Text = "HighFreq RT Ratio (x:1)";
			labelParamValue4.Text = temp.HighFrequencyRtRatio.ToString();
		}
	}
	private void ClearUI(bool ClearControls)
	{
		labelParamName1.Text = labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text =  
		labelParamName3.Text = labelParamValue3.Text = labelParamName4.Text = labelParamValue4.Text =
		labelParamName5.Text = labelParamValue5.Text = labelParamName6.Text = labelParamName1.Text = 
		labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text = labelParamName3.Text = 
		labelParamValue3.Text = labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = 
		labelParamValue5.Text =labelParamName6.Text = labelParamValue6.Text = labelParamName1.Text = 
		labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text = labelParamName3.Text = 
		labelParamValue3.Text = labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = 
		labelParamValue5.Text = labelParamName6.Text = labelParamName1.Text = labelParamValue1.Text =
		labelParamName2.Text = labelParamValue2.Text = labelParamName3.Text = labelParamValue3.Text =
		labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = labelParamValue5.Text =
		labelParamName6.Text = labelParamName1.Text = labelParamValue1.Text = labelParamName2.Text = 
		labelParamValue2.Text = labelParamName3.Text = labelParamValue3.Text = labelParamName4.Text = 
		labelParamValue4.Text = labelParamName5.Text = labelParamValue5.Text = labelParamName6.Text = 		
		labelParamName1.Text = labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text =
		labelParamName3.Text = labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = 
		labelParamValue5.Text = labelParamName6.Text = labelParamValue6.Text = labelParamName1.Text = 
		labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text = labelParamName3.Text = 
		labelParamValue3.Text = labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = 
		labelParamValue5.Text = labelParamName6.Text = labelParamValue6.Text = labelParamName1.Text = 
		labelParamValue1.Text = labelParamName2.Text = labelParamValue2.Text = labelParamName3.Text = 
		labelParamValue3.Text = labelParamName4.Text = labelParamValue4.Text = labelParamName5.Text = 
		labelParamValue5.Text = labelParamName6.Text = labelParamValue6.Text = string.Empty;

		if (ClearControls)
		{
			groupboxFrameWaveform.Enabled = radiobuttonTriangle.Enabled = radiobuttonTriangle.Enabled = radiobuttonRadioSine.Enabled =
			groupboxFramePhase.Enabled = radiobuttonRadioNeg180.Enabled = radiobuttonRadioNeg90.Enabled = radiobuttonRadioZero.Enabled =
			radiobuttonRadio90.Enabled = radiobuttonRadio180.Enabled = false;

			trackbarSlider1.Minimum = trackbarSlider2.Minimum = trackbarSlider3.Minimum = 
			trackbarSlider4.Minimum = trackbarSlider5.Minimum = trackbarSlider6.Minimum = 0;
			trackbarSlider1.Value = trackbarSlider2.Value = trackbarSlider3.Value = 
			trackbarSlider4.Value = trackbarSlider5.Value = trackbarSlider6.Value = 0;
			trackbarSlider1.Enabled = trackbarSlider2.Enabled = trackbarSlider3.Enabled = 
			trackbarSlider4.Enabled = trackbarSlider5.Enabled = trackbarSlider6.Enabled = false;
		}
	}

	private void trackbarSliderScroll(object sender, System.EventArgs e)
	{
		EffectInfo eff = (EffectInfo)effectDescription[currentIndex];
		Type efftype = eff.Effect.GetType();

		#region Chorus
		if (typeof(ChorusEffect) == efftype)
		{
			EffectsChorus temp = new EffectsChorus();
			temp.WetDryMix = trackbarSlider1.Value;
			temp.Frequency = trackbarSlider4.Value;
			temp.Feedback = trackbarSlider3.Value;
			temp.Depth = trackbarSlider2.Value;
			temp.Delay = trackbarSlider5.Value;
			
			if (true == radiobuttonRadioSine.Checked)
				temp.Waveform = ChorusEffect.WaveSin;
			else
				temp.Waveform = ChorusEffect.WaveTriangle;
			
			if (true == radiobuttonRadioNeg180.Checked)
				temp.Phase = ChorusEffect.PhaseNegative180;
			else if (true == radiobuttonRadioNeg90.Checked)
				temp.Phase = ChorusEffect.PhaseNegative90;
			else if (true == radiobuttonRadioZero.Checked)
				temp.Phase = ChorusEffect.PhaseZero;
			else if (true == radiobuttonRadio90.Checked)
				temp.Phase = ChorusEffect.Phase90;
			else if (true == radiobuttonRadio180.Checked)
				temp.Phase = ChorusEffect.Phase180;

			eff.EffectSettings = temp;
			((ChorusEffect)eff.Effect).AllParameters = temp;			
		}
		#endregion Chorus	
		else 
		#region Compressor
		if (typeof(CompressorEffect) == efftype)
		{
			EffectsCompressor temp = new EffectsCompressor();
			temp.Gain = trackbarSlider1.Value;
			temp.Attack = trackbarSlider2.Value;
			temp.Release = trackbarSlider3.Value;
			temp.Threshold = trackbarSlider4.Value;
			temp.Ratio = trackbarSlider5.Value;
			temp.Predelay = trackbarSlider6.Value;

			eff.EffectSettings = temp;
			((CompressorEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Compressor	
		else 
		#region Distortion
		if (typeof(DistortionEffect) == efftype)
		{
			EffectsDistortion temp = new EffectsDistortion();
			temp.Gain = trackbarSlider1.Value;
			temp.Edge = trackbarSlider2.Value;
			temp.PostEqCenterFrequency = trackbarSlider3.Value;
			temp.PostEqBandwidth = trackbarSlider4.Value;
			temp.PreLowpassCutoff = trackbarSlider5.Value;

			eff.EffectSettings = temp;
			((DistortionEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Distortion
		else
		#region Echo
		if (typeof(EchoEffect) == efftype)
		{
			EffectsEcho temp = new EffectsEcho();
			temp.WetDryMix = trackbarSlider1.Value;
			temp.Feedback = trackbarSlider2.Value;
			temp.LeftDelay = trackbarSlider3.Value;
			temp.RightDelay = trackbarSlider4.Value;
			temp.PanDelay = trackbarSlider5.Value;

			eff.EffectSettings = temp;
			((EchoEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Echo
		else
		#region Flanger
		if (typeof(FlangerEffect) == efftype)
		{
			EffectsFlanger temp = new EffectsFlanger();
			temp.WetDryMix = trackbarSlider1.Value;
			temp.Depth = trackbarSlider2.Value;
			temp.Feedback = trackbarSlider3.Value;
			temp.Frequency = trackbarSlider4.Value;
			temp.Delay = trackbarSlider5.Value;
		
			if (true == radiobuttonRadioSine.Checked)
				temp.Waveform = FlangerEffect.WaveSin;
			else
				temp.Waveform = FlangerEffect.WaveTriangle;

			if (true == radiobuttonRadioNeg180.Checked)
				temp.Phase = ChorusEffect.PhaseNegative180;
			else if (true == radiobuttonRadioNeg90.Checked)
				temp.Phase = ChorusEffect.PhaseNegative90;
			else if (true == radiobuttonRadioZero.Checked)
				temp.Phase = ChorusEffect.PhaseZero;
			else if (true == radiobuttonRadio90.Checked)
				temp.Phase = ChorusEffect.Phase90;
			else if (true == radiobuttonRadio180.Checked)
				temp.Phase = ChorusEffect.Phase180;

			eff.EffectSettings = temp;
			((FlangerEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Flanger
		else
		#region Gargle
		if (typeof(GargleEffect) == efftype)
		{
			EffectsGargle temp = new EffectsGargle();
			temp.RateHz = trackbarSlider1.Value;
			if (radiobuttonSquare.Checked)
				temp.WaveShape = GargleEffect.WaveSquare;
			else
				temp.WaveShape = GargleEffect.WaveTriangle;

			if (true == radiobuttonSquare.Checked)
				temp.WaveShape = GargleEffect.WaveSquare;
			else
				temp.WaveShape = GargleEffect.WaveTriangle;

			eff.EffectSettings = temp;
			((GargleEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Gargle
		else 		
		#region Param EQ
		if (typeof(ParamEqEffect) == efftype)
		{
			EffectsParamEq temp = new EffectsParamEq();
			temp.Center = trackbarSlider1.Value;
			temp.Bandwidth = trackbarSlider2.Value;
			temp.Gain = trackbarSlider3.Value;

			eff.EffectSettings = temp;
			((ParamEqEffect)eff.Effect).AllParameters = temp;
		}
		#endregion Param EQ
		else 
		#region Reverb
		if (typeof(WavesReverbEffect) == efftype)
		{
			EffectsWavesReverb temp = new EffectsWavesReverb();
			temp.InGain = trackbarSlider1.Value;
			temp.ReverbMix = trackbarSlider2.Value;
			temp.ReverbTime = (float)(.001 * trackbarSlider3.Value);
			temp.HighFrequencyRtRatio = (float)(.001 * trackbarSlider4.Value);

			eff.EffectSettings = temp;
			((WavesReverbEffect)eff.Effect).AllParameters = temp;
		}	
		#endregion Reverb

		effectDescription[currentIndex] = eff;
		UpdateUI(false);
	}

    private void DeleteEffect()
    {
        EffectInfo[] temp = null;

        if (-1 == listboxEffects.SelectedIndex) 
            return;

        effectDescription.RemoveAt(listboxEffects.SelectedIndex);

        if (effectDescription.Count > 0)
        {
            temp = new EffectInfo[effectDescription.Count];
            effectDescription.CopyTo(temp, 0);
            AddEffect(temp);
            listboxEffects.Items.RemoveAt(listboxEffects.SelectedIndex);				
            listboxEffects.SelectedIndex = currentIndex = 0;
        }
        else
        {
            temp = null;
            AddEffect(temp);
            listboxEffects.Items.Clear();
            ClearUI(true);
        }
        effectDescription.Clear();
        if (null != temp)
            effectDescription.AddRange(temp);        
    }

	private void listboxEffects_KeyUp(object sender, System.Windows.Forms.KeyEventArgs e)
	{
        if (e.KeyCode == Keys.Delete)
            DeleteEffect();
	}

	private void buttonOk_Click(object sender, System.EventArgs e)
	{
		this.Close();
	}

    private void buttonDelete_Click(object sender, System.EventArgs e)
    {
        DeleteEffect();
    }

    private void MainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
    {
        if (null != applicationBuffer)
        {
            if(applicationBuffer.Status.Playing)
                applicationBuffer.Stop();
        }
    }

	private void tbarFreq_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
	{
		if (e.Button == System.Windows.Forms.MouseButtons.Right)
		{
			tbarFreq.Value = applicationBuffer.Format.SamplesPerSecond;
			textFreq.Text = tbarFreq.Value.ToString();
			lastGoodFrequency = tbarFreq.Value;
			applicationBuffer.Frequency = tbarFreq.Value;
		}
	}

	private void tbarPan_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
	{
		if (e.Button == System.Windows.Forms.MouseButtons.Right)
		{
			tbarPan.Value = 0;
			tbarPan.Text = tbarPan.Value.ToString();

			textPan.Text = ((TrackBar)sender).Value.ToString();
			applicationBuffer.Pan = ((TrackBar)sender).Value * 500;
		}	
	}


	private void MainForm_Load(object sender, System.EventArgs e)
	{
		pictureBox2.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox2_fill);
		this.Controls.Add(pictureBox2);

		fft = new FFT();

	}


	#endregion hide stuff

	//private ushort[,] FFT(ushort[] fft,long BlockSize)

	private ushort[,] FFT(byte[] fft,long BlockSize)
	{
		//ushort[,] lFFT = new ushort[2048/4,2];
		ushort[,] lFFT = new ushort[2048/4,2];

		//if (buffer == 16)
			{
				int f = 0;
				for (int i = 0; i < BlockSize; i+=4)
				{
					lFFT[f,0] = (ushort)(fft[i+0]*fft[i+1]);
					lFFT[f,1] = (ushort)(fft[i+2]*fft[i+3]);
					f++;
				}
			}
		return lFFT;

	}
	private ushort[,] loadFFTbyte(byte[] fft,long BlockSize)
	{

		ushort[,] lFFT = new ushort[2048/4,2];  // get rid of this

		short[] sFFT = new short[2048];
		for (int x = 0 ; x < BlockSize ; x++)
			sFFT[x] = (short)(fft[x] * 255);

		lFFT = loadFFTshort(sFFT,(short)BlockSize);

			
		return lFFT;
	}

	private ushort[,] loadFFTshort(short[] fft,short BlockSize)
	{
		ushort[,] lFFT = new ushort[2048/4,2];
		return lFFT;

		int m_BitsPerSample	= applicationBuffer.Format.BitsPerSample;
		int m_BufSize		= 2048/4;
		int m_NumChannels	= applicationBuffer.Format.Channels;
		float[] m_Input = new float[2048];

		label1.Text = m_BitsPerSample.ToString();
		label4.Text = m_BufSize.ToString();
		label11.Text = m_NumChannels.ToString();
		
		int m_block = applicationBuffer.Format.BlockAlign;
		int m_avg	= applicationBuffer.Format.AverageBytesPerSecond;
		int m_bits = applicationBuffer.Format.BitsPerSample;

		// convert each data point from 0-255 to floating point -1..1
		if (m_BitsPerSample == 8)
		{
			for (int q = 0; q < m_BufSize; q ++)
			{
				float d = fft[q*m_NumChannels];
				m_Input[q] = (d-127.0f/127.0f);
                
				if (m_Input[q] < -1.0f) 
					m_Input[q] = -1.0f;
				if (m_Input[q] >  1.0f) 
					m_Input[q] =  1.0f;
			}
		}
		else
		if (m_BitsPerSample == 16)
		{
			int step = 0;
			for (int q = 0; q < m_BufSize; q += 2)
			{
				float d = (fft[q*m_NumChannels]*fft[(q*m_NumChannels)+1]);
				m_Input[step] = (d-32767.0f/32767.0f);
                
				if (m_Input[step] < -1.0f) 
					m_Input[step] = -1.0f;
				if (m_Input[step] >  1.0f) 
					m_Input[step] =  1.0f;

				//m_Input[step] =  1.0f;
				step++;
			}
		}
		else
		{
			// not supported
			for (int q = 0; q < m_BufSize; q ++)
			{
				m_Input[q] =  0.0f;
			}
		}

		float[] m_AmpOutput = new float[(m_BufSize/2)+1];

		for (int bin = 0; bin <= m_BufSize/2;bin++)
		{
			float cosAmp = 0.0f;
			float sinAmp = 0.0f;
			for (int k = 0 ; k < m_BufSize; k++)
			{
				float x = 2.0f * (float)Math.PI * (float)bin * (float)k / (float)m_BufSize;
				//float x = 2.0f * (float)3.141592 * (float)bin * (float)k / (float)m_BufSize;
				//float x = (float)0.017453292 * (float)bin * (float)k / (float)m_BufSize;
				sinAmp += (float)(m_Input[k] * Math.Sin(x));
				cosAmp += (float)(m_Input[k] * Math.Sin(x));
			}
			m_AmpOutput[bin] = (float)(Math.Sqrt(sinAmp*sinAmp + cosAmp*cosAmp));
		}

		//DFT paint screen
		Pen pen = new Pen(Color.Purple, 1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.Black);



		int stp = 2;
		pen = new Pen(Color.Purple, stp-1);

		int n = 0;
		float b = 0;
		int r = 0;
		for (float xx = 0 ; xx < pictureBox1.Width ; xx += pictureBox1.Width/((float)(m_BufSize/2.0f)))
		{
			r++;
			n++;			  // x1,                 y1 ,   x2 ,     y2
			b+=m_AmpOutput[n];
			if (r > stp)
			{
				graph1.DrawLine(pen,	xx,	
										//pictureBox1.Height-(m_AmpOutput[n]*3),
										pictureBox1.Height-(b/stp),
										xx,
										pictureBox1.Height);
				b = 0;
                r = 0;
			}
		}
		
		//pictureBox1.Image = bit1;


		//ushort[,] lFFT = new ushort[2048/4,2];
		return lFFT;
	}

	private ushort[,] loadFFTushort(ushort[] fft,int BlockSize)
	{
		int m_BitsPerSample	= applicationBuffer.Format.BitsPerSample;
		int m_BufSize		= 2048/4;
		int m_NumChannels	= applicationBuffer.Format.Channels;
		float[] m_Input = new float[2048];

		label1.Text = m_BitsPerSample.ToString();
		label4.Text = m_BufSize.ToString();
		label11.Text = m_NumChannels.ToString();
		
		int m_block = applicationBuffer.Format.BlockAlign;
		int m_avg	= applicationBuffer.Format.AverageBytesPerSecond;
		int m_bits = applicationBuffer.Format.BitsPerSample;

		// convert each data point from 0-255 to floating point -1..1
		if (m_BitsPerSample == 8)
		{
			for (int q = 0; q < m_BufSize; q ++)
			{
				float d = fft[q*m_NumChannels];
				m_Input[q] = (d-127.0f/127.0f);
                
				if (m_Input[q] < -1.0f) 
					m_Input[q] = -1.0f;
				if (m_Input[q] >  1.0f) 
					m_Input[q] =  1.0f;
			}
		}
		else
			if (m_BitsPerSample == 16)
		{
			int step = 0;
			for (int q = 0; q < m_BufSize; q += 2)
			{
				float d = (fft[q*m_NumChannels]*fft[(q*m_NumChannels)+1]);
				m_Input[step] = (d-32767.0f/32767.0f);
                
				if (m_Input[step] < -1.0f) 
					m_Input[step] = -1.0f;
				if (m_Input[step] >  1.0f) 
					m_Input[step] =  1.0f;

				//m_Input[step] =  1.0f;
				step++;
			}
		}
		else
		{
			// not supported
			for (int q = 0; q < m_BufSize; q ++)
			{
				m_Input[q] =  0.0f;
			}
		}

		float[] m_AmpOutput = new float[(m_BufSize)+1];

		for (int bin = 0; bin <= m_BufSize/2;bin++)
		{
			float cosAmp = 0.0f;
			float sinAmp = 0.0f;
			for (int k = 0 ; k < m_BufSize; k++)			
			{
				//float M_PI = Math.PI;
				float x = 2.0f * (float)Math.PI * (float)bin * (float)k / (float)m_BufSize;
				sinAmp += (float)(m_Input[k] * Math.Sin(x));
				cosAmp += (float)(m_Input[k] * Math.Sin(x));
			}
			m_AmpOutput[bin] = (float)(Math.Sqrt(sinAmp*sinAmp + cosAmp*cosAmp));
		}

		//DFT paint screen
		Pen pen = new Pen(Color.Purple, 1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.Black);



		int stp = 4;
		pen = new Pen(Color.Purple, stp-1);

		int n = 0;
		float b = 0;
		int r = 0;
		//for (float xx = 0 ; xx < pictureBox1.Width ; xx += pictureBox1.Width/((float)(m_BufSize/2.0f)))
		for (float xx = 0 ; xx < m_BufSize/4 ; xx += 1)
		{
			r++;
			n++;			  // x1,                 y1 ,   x2 ,     y2
			b+=m_AmpOutput[n];
			if (r > stp)
			{
				graph1.DrawLine(pen,	xx,	
					//pictureBox1.Height-(m_AmpOutput[n]*3),
					pictureBox1.Height-b,		//(stp),
					xx,
					pictureBox1.Height);
				b = 0;
				r = 0;
			}
		}
		
//		pictureBox1.Image = bit1;


		ushort[,] lFFT = new ushort[2048/4,2];
		return lFFT;
	}

	
	private void pictureBox2_fill(object sender, System.Windows.Forms.PaintEventArgs e)
	{
		Graphics g = e.Graphics;

		int c = 0;
		SolidBrush myBrush = new SolidBrush(Color.LightGray);

		for (int iLp = 0; iLp < 22;iLp++)
		{
			for (int b=0;b<17;b++)
			{
				myBrush.Color = Color.LightGray;
				if (b>=c)
				{
					if (b<2)
						myBrush.Color = Color.Red;
					else
						if (b < 5)
						myBrush.Color = Color.Yellow;
					else
						myBrush.Color = Color.Green;
				}
				g.FillRectangle(myBrush, new Rectangle((iLp*10), (b*7),8,5));
			}
			c++;
		}
	
	}


	private void paint_picture_1_1(double[] StreamDisplayData)
	{
		//DFT paint screen
		Pen pen = new Pen(Color.Purple, 1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.Black);

		int stp = 2;
		pen = new Pen(Color.Red, stp-1);

		int n = 0;
		float b = 0;
		int r = 0;
		for (float xx = 0 ; xx < pictureBox1.Width ; xx++)
		{
			r++;
			n++;			  // x1,                 y1 ,   x2 ,     y2
			//b+=m_AmpOutput[n];
			b += (float)StreamDisplayData[(int)xx];
			if (r > stp)
			{
				graph1.DrawLine(pen,	
					xx,	
					//pictureBox1.Height-(m_AmpOutput[n]*3),
					pictureBox1.Height-(b/stp),
					xx,
					pictureBox1.Height);
				b = 0;
				r = 0;
			}
		}
		
		pictureBox1.Image = bit1;
	}

	private void paint_picture_1_2(double[] m_dArray)
	{
		//FFT paint screen
		int pos = 0;
		double m_nMinValue = 00;
		double m_nMaxValue = 10;

		//int nBars = 36;
		int nBars = 256;
		int m_nLength = fft.FFT_LEN/2;
		int nDiv=m_nLength/(nBars);

		// predictable test results data
		//		double[] m_dArray = {2009.218750, 50.643643, 50.232612, 49.553496, 48.615116, 47.429676, 46.012597, 44.382343, 42.560204, 40.570065, 38.438152, 36.192783, 33.864136, 31.484017, 29.085688, 26.703735, 24.366370, 22.127096, 20.014978, 18.068207, 16.324157, 14.816924, 13.573118, 12.606049, 11.909927, 11.457200, 11.201584, 11.086256, 11.053568, 11.052565, 11.042877, 10.995576, 10.893563, 10.725468, 10.490163, 10.191814, 9.839335, 9.445352, 9.025266, 8.596343, 8.176704, 7.784118, 7.434549, 7.140501, 6.909447, 6.742738, 6.635449, 6.577323, 6.554978, 6.553281, 6.556897, 6.553012, 6.531542, 6.485482, 6.410929, 6.306915, 6.175125, 6.019555, 5.846118, 5.662184, 5.476053, 5.296319, 5.131137, 4.987424, 4.868660, 4.782538, 4.724398, 4.690837, 4.676326, 4.674044, 4.676765, 4.677639, 4.670793, 4.651711, 4.617440, 4.566650, 4.499585, 4.417947, 4.324699, 4.223819, 4.119466, 4.018176, 3.923827, 3.840674, 3.771913, 3.719307, 3.682990, 3.661488, 3.651961, 3.650612, 3.653179, 3.655410, 3.653467, 3.644234, 3.625509, 3.596102, 3.555541, 3.505635, 3.447495, 3.383598, 3.316959, 3.250878, 3.188651, 3.133243, 3.086979, 3.051287, 3.026532, 3.011995, 3.005990, 3.006098, 3.009477, 3.013179, 3.014546, 3.011336, 3.001577, 2.984205, 2.958891, 2.926027, 2.886676, 2.842468, 2.795463, 2.747982, 2.702397, 2.660907, 2.625313, 2.596827, 2.575939, 2.562372, 2.555146, 2.555132, 2.557780, 2.560934, 2.562522, 2.560748, 2.554227, 2.542084, 2.523992, 2.500186, 2.471424, 2.438918, 2.404234, 2.369155, 2.335524, 2.305062, 2.279097, 2.259111, 2.245104, 2.236878, 2.233670, 2.234252, 2.237083, 2.240482, 2.242802, 2.242582, 2.238663, 2.230277, 2.217094, 2.199230, 2.177233, 2.152031, 2.124580, 2.097137, 2.070654, 2.046545, 2.026003, 2.009876, 1.998569, 1.992007, 1.989647, 1.990551, 1.993501, 1.997136, 2.000093, 2.001136, 1.999261, 1.993774, 1.984305, 1.971141, 1.954444, 1.934927, 1.913565, 1.891513, 1.869996, 1.850200, 1.833147, 1.819586, 1.809917, 1.804141, 1.801870, 1.802376, 1.804679, 1.807660, 1.810333, 1.811991, 1.811220, 1.807388, 1.800166, 1.789542, 
		//							    1.775822, 1.759598, 1.741701, 1.723126, 1.704945, 1.688208, 1.673832, 1.662510, 1.654631, 1.650238, 1.649068, 1.650639, 1.653922, 1.657923, 1.661616, 1.664041, 1.664388, 1.662061, 1.656728, 1.648336, 1.637114, 1.623552, 1.608360, 1.592405, 1.576637, 1.562002, 1.549251, 1.539478, 1.532735, 1.529110, 1.528380, 1.530044, 1.533381, 1.537533, 1.541598, 1.544715, 1.546146, 1.545335, 1.541951, 1.535909, 1.527375, 1.516744, 1.504548, 1.491810, 1.479109, 1.467244, 1.456927, 1.448709, 1.442914, 1.439607, 1.438583, 1.439394, 1.441396, 1.443830, 1.445891, 1.446816, 1.445955, 1.442823, 1.436882, 1.431190, 1.423054, 1.412843, 1.401127, 1.388621, 1.376129, 1.364466, 1.354379, 1.346467, 1.341117, 1.338459, 1.338348, 1.340390, 1.343982, 1.348380, 1.352843, 1.356619, 1.358920, 1.359205, 1.357126, 1.352561, 1.345613, 1.336606, 1.326058, 1.314638, 1.303105, 1.292245, 1.282788, 1.275335, 1.270289, 1.267813, 1.267880, 1.270200, 1.274076, 1.278804, 1.283616, 1.287751, 1.290532, 1.291421, 1.290066, 1.286323, 1.280272, 1.272207, 1.262614, 1.252128, 1.241484, 1.231447, 1.222706, 1.216076, 1.211776, 1.209977, 1.210590, 1.213282, 1.217513, 1.222597, 1.227772, 1.232283, 1.235448, 1.236717, 1.235720, 1.232295, 1.226500, 1.218608, 1.208966, 1.198911, 1.188601, 1.178807, 1.170262, 1.163591, 1.159241, 1.157423, 1.158095, 1.160957, 1.165495, 1.171033, 1.176811, 1.182059, 1.186073, 1.188277, 1.188284, 1.185978, 1.181279, 1.174426, 1.165863, 1.156197, 1.146160, 1.136531, 1.128072, 1.121443, 1.117130, 1.115386, 1.116202, 1.119304, 1.124188, 1.130177, 1.136635, 1.142625, 1.147399, 1.150343, 1.151021, 1.149206, 1.144897, 1.138326, 1.129937, 1.120357, 1.110343, 1.100720, 1.092301, 1.085799, 1.081753, 1.080454, 1.081960, 1.086042, 1.092065, 1.099297, 1.106895, 1.113991, 1.119772, 1.123551, 1.124821, 1.123297, 1.118937, 1.111944, 1.102759, 1.092031, 1.080570, 1.069279, 1.058974, 1.051746, 1.047095, 1.045396, 1.046720, 1.050824, 1.057175, 1.065020, 1.073464, 1.081572, 1.088452, 1.093340, 1.095659, 1.095063, 1.091465, 
		//								1.085047, 1.076212, 1.065820, 1.054579, 1.043461, 1.033465, 1.025519, 1.020373, 1.018502, 1.020043, 1.024773, 1.032131, 1.041290, 1.051252, 1.060953, 1.069371, 1.075614, 1.079085, 1.079252, 1.075961, 1.069367, 1.059924, 1.048359, 1.035633, 1.022866, 1.011244, 1.001900, 0.995782, 0.993535, 0.995403, 1.001188, 1.010273, 1.021701, 1.034417, 1.046994, 1.058187, 1.066890, 1.072221, 1.073588, 1.070730, 1.063739, 1.053066, 1.039503, 1.024149, 1.008341, 0.993549, 0.981246, 0.972732, 0.968967, 0.970685, 0.977754, 0.989234, 1.003962, 1.020455, 1.037083, 1.052236, 1.064460, 1.072563, 1.075696, 1.073405, 1.065665, 1.052900, 1.035988, 1.016239, 0.995340, 0.975202, 0.958186, 0.946067, 0.940434, 0.942224, 0.951541, 0.967612, 0.988908, 1.013366, 1.038666, 1.062468, 1.082613, 1.097260, 1.104983, 1.104837, 1.096412, 1.079749, 1.055955, 1.026320, 0.993007, 0.958874, 0.927381, 0.902349, 0.887494, 0.885768, 0.898671, 0.925852, 0.965194, 1.013317, 1.066216, 1.119796, 1.170205, 1.214391, 1.248690, 1.270989, 1.279355, 1.272336, 1.248950, 1.208671, 1.151406};
		double left;
		double top, bottom;

		double dRangePerStep = (m_nMaxValue-m_nMinValue);

		int xRight = pictureBox1.Width / nBars;

		dRangePerStep /= 10;

		Pen pen = new Pen(Color.Purple, 1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.WhiteSmoke);

		//pen = new Pen(Color.Red, 10);
		pen = new Pen(Color.Red, (float)dRangePerStep);

		for (int w = 0 ; w < nBars; w++)
		{
			double tot = 0, nLargest = 0;
			for (int i=pos; i<pos + nDiv; i++)
			{
				tot+=m_dArray[i];
				if (m_dArray[i] > nLargest)
					nLargest = m_dArray[i];
			}
			tot /= m_nMaxValue - m_nMinValue;
			//tot *= 2;
			tot /=512;

			left = xRight*(w+1);//-xRight;
			bottom = pictureBox1.Height;//pictureBox1.Height;
			top = bottom - tot;
			if (top <0)
				top = 0;

			graph1.DrawLine(pen,	
				(float)left,	
				(float)top,
				(float)left,  // no right, the pen has the width
				(float)bottom);

			pos+=nDiv;
		}		
		
		pictureBox1.Image = bit1;
	}

	private void paint_picture_1_3()
	{
		//FFT paint screen
		int pos = 0;
		double m_nMinValue = 00;
		double m_nMaxValue = 10;

		int nBars = 36;
		//int nBars = 288;
		//int nBars = 36*5;
		int m_nLength = fft.FFT_LEN/2;
		int nDiv=m_nLength/(nBars);

		// predictable test results data
		//		double[] m_dArray = {2009.218750, 50.643643, 50.232612, 49.553496, 48.615116, 47.429676, 46.012597, 44.382343, 42.560204, 40.570065, 38.438152, 36.192783, 33.864136, 31.484017, 29.085688, 26.703735, 24.366370, 22.127096, 20.014978, 18.068207, 16.324157, 14.816924, 13.573118, 12.606049, 11.909927, 11.457200, 11.201584, 11.086256, 11.053568, 11.052565, 11.042877, 10.995576, 10.893563, 10.725468, 10.490163, 10.191814, 9.839335, 9.445352, 9.025266, 8.596343, 8.176704, 7.784118, 7.434549, 7.140501, 6.909447, 6.742738, 6.635449, 6.577323, 6.554978, 6.553281, 6.556897, 6.553012, 6.531542, 6.485482, 6.410929, 6.306915, 6.175125, 6.019555, 5.846118, 5.662184, 5.476053, 5.296319, 5.131137, 4.987424, 4.868660, 4.782538, 4.724398, 4.690837, 4.676326, 4.674044, 4.676765, 4.677639, 4.670793, 4.651711, 4.617440, 4.566650, 4.499585, 4.417947, 4.324699, 4.223819, 4.119466, 4.018176, 3.923827, 3.840674, 3.771913, 3.719307, 3.682990, 3.661488, 3.651961, 3.650612, 3.653179, 3.655410, 3.653467, 3.644234, 3.625509, 3.596102, 3.555541, 3.505635, 3.447495, 3.383598, 3.316959, 3.250878, 3.188651, 3.133243, 3.086979, 3.051287, 3.026532, 3.011995, 3.005990, 3.006098, 3.009477, 3.013179, 3.014546, 3.011336, 3.001577, 2.984205, 2.958891, 2.926027, 2.886676, 2.842468, 2.795463, 2.747982, 2.702397, 2.660907, 2.625313, 2.596827, 2.575939, 2.562372, 2.555146, 2.555132, 2.557780, 2.560934, 2.562522, 2.560748, 2.554227, 2.542084, 2.523992, 2.500186, 2.471424, 2.438918, 2.404234, 2.369155, 2.335524, 2.305062, 2.279097, 2.259111, 2.245104, 2.236878, 2.233670, 2.234252, 2.237083, 2.240482, 2.242802, 2.242582, 2.238663, 2.230277, 2.217094, 2.199230, 2.177233, 2.152031, 2.124580, 2.097137, 2.070654, 2.046545, 2.026003, 2.009876, 1.998569, 1.992007, 1.989647, 1.990551, 1.993501, 1.997136, 2.000093, 2.001136, 1.999261, 1.993774, 1.984305, 1.971141, 1.954444, 1.934927, 1.913565, 1.891513, 1.869996, 1.850200, 1.833147, 1.819586, 1.809917, 1.804141, 1.801870, 1.802376, 1.804679, 1.807660, 1.810333, 1.811991, 1.811220, 1.807388, 1.800166, 1.789542, 
		//							    1.775822, 1.759598, 1.741701, 1.723126, 1.704945, 1.688208, 1.673832, 1.662510, 1.654631, 1.650238, 1.649068, 1.650639, 1.653922, 1.657923, 1.661616, 1.664041, 1.664388, 1.662061, 1.656728, 1.648336, 1.637114, 1.623552, 1.608360, 1.592405, 1.576637, 1.562002, 1.549251, 1.539478, 1.532735, 1.529110, 1.528380, 1.530044, 1.533381, 1.537533, 1.541598, 1.544715, 1.546146, 1.545335, 1.541951, 1.535909, 1.527375, 1.516744, 1.504548, 1.491810, 1.479109, 1.467244, 1.456927, 1.448709, 1.442914, 1.439607, 1.438583, 1.439394, 1.441396, 1.443830, 1.445891, 1.446816, 1.445955, 1.442823, 1.436882, 1.431190, 1.423054, 1.412843, 1.401127, 1.388621, 1.376129, 1.364466, 1.354379, 1.346467, 1.341117, 1.338459, 1.338348, 1.340390, 1.343982, 1.348380, 1.352843, 1.356619, 1.358920, 1.359205, 1.357126, 1.352561, 1.345613, 1.336606, 1.326058, 1.314638, 1.303105, 1.292245, 1.282788, 1.275335, 1.270289, 1.267813, 1.267880, 1.270200, 1.274076, 1.278804, 1.283616, 1.287751, 1.290532, 1.291421, 1.290066, 1.286323, 1.280272, 1.272207, 1.262614, 1.252128, 1.241484, 1.231447, 1.222706, 1.216076, 1.211776, 1.209977, 1.210590, 1.213282, 1.217513, 1.222597, 1.227772, 1.232283, 1.235448, 1.236717, 1.235720, 1.232295, 1.226500, 1.218608, 1.208966, 1.198911, 1.188601, 1.178807, 1.170262, 1.163591, 1.159241, 1.157423, 1.158095, 1.160957, 1.165495, 1.171033, 1.176811, 1.182059, 1.186073, 1.188277, 1.188284, 1.185978, 1.181279, 1.174426, 1.165863, 1.156197, 1.146160, 1.136531, 1.128072, 1.121443, 1.117130, 1.115386, 1.116202, 1.119304, 1.124188, 1.130177, 1.136635, 1.142625, 1.147399, 1.150343, 1.151021, 1.149206, 1.144897, 1.138326, 1.129937, 1.120357, 1.110343, 1.100720, 1.092301, 1.085799, 1.081753, 1.080454, 1.081960, 1.086042, 1.092065, 1.099297, 1.106895, 1.113991, 1.119772, 1.123551, 1.124821, 1.123297, 1.118937, 1.111944, 1.102759, 1.092031, 1.080570, 1.069279, 1.058974, 1.051746, 1.047095, 1.045396, 1.046720, 1.050824, 1.057175, 1.065020, 1.073464, 1.081572, 1.088452, 1.093340, 1.095659, 1.095063, 1.091465, 
		//								1.085047, 1.076212, 1.065820, 1.054579, 1.043461, 1.033465, 1.025519, 1.020373, 1.018502, 1.020043, 1.024773, 1.032131, 1.041290, 1.051252, 1.060953, 1.069371, 1.075614, 1.079085, 1.079252, 1.075961, 1.069367, 1.059924, 1.048359, 1.035633, 1.022866, 1.011244, 1.001900, 0.995782, 0.993535, 0.995403, 1.001188, 1.010273, 1.021701, 1.034417, 1.046994, 1.058187, 1.066890, 1.072221, 1.073588, 1.070730, 1.063739, 1.053066, 1.039503, 1.024149, 1.008341, 0.993549, 0.981246, 0.972732, 0.968967, 0.970685, 0.977754, 0.989234, 1.003962, 1.020455, 1.037083, 1.052236, 1.064460, 1.072563, 1.075696, 1.073405, 1.065665, 1.052900, 1.035988, 1.016239, 0.995340, 0.975202, 0.958186, 0.946067, 0.940434, 0.942224, 0.951541, 0.967612, 0.988908, 1.013366, 1.038666, 1.062468, 1.082613, 1.097260, 1.104983, 1.104837, 1.096412, 1.079749, 1.055955, 1.026320, 0.993007, 0.958874, 0.927381, 0.902349, 0.887494, 0.885768, 0.898671, 0.925852, 0.965194, 1.013317, 1.066216, 1.119796, 1.170205, 1.214391, 1.248690, 1.270989, 1.279355, 1.272336, 1.248950, 1.208671, 1.151406};
		double left;
		double top, bottom;

		double dRangePerStep = (m_nMaxValue-m_nMinValue);

		int xRight = pictureBox1.Width / nBars;

		dRangePerStep /= 10;

		Pen pen = new Pen(Color.Purple, nDiv-1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.WhiteSmoke);

		//pen = new Pen(Color.Red, 10);
		pen = new Pen(Color.Blue, nDiv-1);

		for (int w = 0 ; w < nBars; w++)
		{
			double tot = 0, nLargest = 0;
			for (int i=pos; i<pos + nDiv; i++)
			{
				tot+=fft.fdraw[i];
				if (fft.fdraw[i] > nLargest)
					nLargest = fft.fdraw[i];
			}
			tot /= m_nMaxValue - m_nMinValue;
			//tot *= 2;
			//tot = Math.Sqrt(tot)*pictureBox1.Height/2;

			left = xRight*(w+1);//-xRight;
			bottom = pictureBox1.Height;//pictureBox1.Height;
			top = bottom - (tot/(fft.FFT_LEN*2));
			if (top <0)
				top = 0;

			graph1.DrawLine(pen,	
				(float)left,	
				(float)top,
				(float)left,  // no right, the pen has the width
				(float)bottom);

			pos+=nDiv;
		}		
		
		pictureBox1.Image = bit1;


//        For X = 0 To PicVis1.Width
//
//            Y = Sqrt(d(X + 1)) * 3 * PicVis1.Height - 4
//            If Y > PicVis1.Height Then Y = PicVis1.Height
//            graph.DrawLine(PurplePen, X, PicVis1.Height, X, PicVis1.Height - Y)
//
//            'graph.DrawLine(PurplePen, X, PicVis1.Height, X, PicVis1.Height - d(X) * 1000)
//        Next
	}
	private void paint_picture_1_4()
	{
		//FFT paint screen
		int pos = 0;
		double m_nMinValue = 00;
		double m_nMaxValue = 10;

		int nBars = 4;
		nBars = trackBar2.Value;
		//int nBars = 15;
		//int nBars = 30;
		//int nBars = 60;
		//int nBars = 288;
		//int nBars = 36*5;
		int m_nLength = fft.FFT_LEN/2;
		int nDiv=m_nLength/(nBars);

		double left;
		double top, bottom;

		double dRangePerStep = (m_nMaxValue-m_nMinValue);

		int xRight = pictureBox1.Width / nBars;

		dRangePerStep /= 10;

		Pen pen = new Pen(Color.Purple, nDiv-1);

		Graphics graph1 = Graphics.FromImage(bit1);
		graph1.Clear(Color.WhiteSmoke);

		//pen = new Pen(Color.Red, 10);
		pen = new Pen(Color.Blue, nDiv-1);

		for (int w = 1 ; w < nBars+1; w++)
		{	// add comment
			//this should effect pos;
			double vol1;

			int t = w;

            vol1 = (double)t/(double)nBars;
			vol1 = -(Math.Log10(1.0f-vol1));
			nDiv = (int)(vol1*(m_nLength/2));
			if (vol1>1)
				vol1 = 1;

			//nDiv = pos + nDiv;
			if (nDiv > m_nLength)
				nDiv = m_nLength;
			else
				if (nDiv < 0) 
				nDiv = m_nLength;

			Console.WriteLine(w.ToString() + " " +  pos.ToString() + " " + nDiv.ToString());

//			double vol3 = 1024*vol1;
//			Console.WriteLine(vol3.ToString());
			double tot = 0;  
			double nLargest = 0;
			int cnt = 0;
			for (int i=pos; i < nDiv; i++)
			{
				tot+=fft.fdraw[i];
				if (fft.fdraw[i] > nLargest)
					nLargest = fft.fdraw[i];
				cnt++;
			}

			//tot /=20000;
			tot /= cnt;
			uint tot1 = (uint)tot;
			
			tot1 = (tot1 >> 11);
			//tot /= 10000;
			//tot *= (double)w*0.00015f;

			//tot /= m_nMaxValue - m_nMinValue;
			//tot /= (cnt*10)*vol1;
			//tot /= (cnt*2048);//*vol1;
			//tot /= (Math.Sqrt(nLargest)/cnt)*vol1;//*vol1;
			
			//tot *= 2;
			//tot = Math.Sqrt(tot);

			//left = xRight*(w+1);//-xRight;
			left = (xRight*w)-(xRight/2)+2;
			bottom = pictureBox1.Height;//pictureBox1.Height;
			//top = bottom - ((tot*((vol1*vol1)/vol1))/(fft.FFT_LEN/2));
			top = bottom - tot1;
			if (top <0)
				top = 0;

			graph1.DrawLine(pen,	
				(float)left,	
				(float)top,
				(float)left,  // no right, the pen has the width
				(float)bottom);

			pos = nDiv;
		}		
		
		pictureBox1.Image = bit1;


		//        For X = 0 To PicVis1.Width
		//
		//            Y = Sqrt(d(X + 1)) * 3 * PicVis1.Height - 4
		//            If Y > PicVis1.Height Then Y = PicVis1.Height
		//            graph.DrawLine(PurplePen, X, PicVis1.Height, X, PicVis1.Height - Y)
		//
		//            'graph.DrawLine(PurplePen, X, PicVis1.Height, X, PicVis1.Height - d(X) * 1000)
		//        Next
	}


	private void timer1_Tick(object sender, System.EventArgs e)
	{
		if(applicationBuffer.Status.Playing)
			return;
		else
		{
			timer1.Enabled = false;
			labelTextStatus.Text="Sound stopped - Finished.";

			buttonPlay.Enabled=true;
			buttonStop.Enabled=false;
			checkboxLoop.Enabled=true;
		}    
	}

	private void timer2_Tick(object sender, System.EventArgs e)
	{
		if (applicationBuffer == null)
			return;

		int cPos,cWrit;
		applicationBuffer.GetCurrentPosition(out cPos,out cWrit);
		label3.Text = "POS : " + cPos.ToString() + " : " + cWrit.ToString();


		// vb sample
		//' Read the capture buffer. 
		//Dim CaptureData As Byte() = Nothing 
		//CaptureData = CType(applicationBuffer.Read(NextCaptureOffset, GetType(Byte), LockFlag.None, LockSize), Byte()) 
		//
		//C# public Array Read(
		//    int bufferStartingLocation,
		//    Type returnedDataType,
		//    LockFlag flag,
		//    int[] ranks
		//	); 
		/*
		public System.Array Read ( System.Int32 bufferStartingLocation , 
									System.Type returnedDataType , 
									Microsoft.DirectX.DirectSound.LockFlag flag , 
									params int[] ranks )
			Member of Microsoft.DirectX.DirectSound.Buffer

		Summary:
		Reads the current data in the buffer.

		Parameters:
		*/
		//		int[] x = new int[512];
		//
		//		applicationBuffer.Read(0,System.Type.GetType("System.Int32"),Microsoft.DirectX.DirectSound.LockFlag.None,x);
		//		 //applicationBuffer.Read(0,applicationBuffer,512,Microsoft.DirectX.DirectSound.LockFlag.None);
		//		//applicationBuffer.Read(0,x,Microsoft.DirectX.DirectSound.LockFlag.None);
		//		//applicationBuffer.Read(0,x,512,Microsoft.DirectX.DirectSound.LockFlag.None);
		//
		//
		//		? sample code C:\DXSDK9\Samples\C++\DirectSound\FullDuplexFilter
		//		vb sample code http://www.hut.fi/~jwagner/electr/dc-rx/cheddar54-source/Sound.frm
		//
		//		//		where: 

		byte[] StreamCaptureData = null;
		int NextCaptureOffset = cPos;		
		StreamCaptureData = (byte[])applicationBuffer.Read(NextCaptureOffset, typeof(byte), LockFlag.None, 512); 

		//		int[] StreamCaptureData = null;
		//		int NextCaptureOffset = cPos;		
		//		StreamCaptureData = (int[])applicationBuffer.Read(NextCaptureOffset, typeof(int), LockFlag.None, 512); 

		if (applicationBuffer.PlayPosition == 0)
			return;

		short[] StreamCaptureData2 = null;
		StreamCaptureData2 = (short[])applicationBuffer.Read(NextCaptureOffset, typeof(short), LockFlag.None,(int) fft.FFT_LEN); 

		for (int test = 0; test < fft.FFT_LEN; test++)
		{
			// 10 kHz calibration wave
			//StreamCaptureData2[test] = (short)(1600 * Math.Sin (2 * Math.PI * 20000.0 * test / 44100));
		}

		fft = new FFT();
		//double[] StreamCaptureData3 = null;
//		double[] StreamCaptureData3 = fft.fft_double(1024,false);

		//double[] StreamDisplayData = null;
		//StreamDisplayData = fft.displayFreq();
		fft.displayFreq();
		//fft_double(FFT_LEN,0,fin,NULL,fout,foutimg);
		//		float re,im;
		for(int i=0;i<fft.FFT_LEN/2;i++)
		{
			//re = fout[i];
			//im = foutimg[i];
			//get frequency intensity and scale to 0..256 range
			//StreamCaptureData3[i]=(fft.GetFrequencyIntensity(re,im))/256;
//			StreamCaptureData3[i]=(fft.fdraw[i])/512;
		}

//		this.paint_picture_1_2(StreamCaptureData3);

		//		if (StreamCaptureData[0]<0)
		//			StreamCaptureData[0]=0;
	}

	private void timer3_Tick(object sender, System.EventArgs e)
	{
		if ( applicationDevice != null)
		{

			if (applicationBuffer == null)
				return;
			if (applicationBuffer.PlayPosition == 0)
				return;

			int cPos,cWrit;
			applicationBuffer.GetCurrentPosition(out cPos,out cWrit);


			//			if (applicationBuffer.Format.BitsPerSample == 8)
			//			{
			//				byte[] StreamCaptureData = null;
			//				StreamCaptureData = (byte[])applicationBuffer.Read(cPos, typeof(byte), LockFlag.None, 2048); 
			//				ushort[,] buf = null;
			//				buf = loadFFTbyte(StreamCaptureData,2048);
			//			}
			//			else
			//		{
			//			short[] StreamCaptureData = null;
			//			StreamCaptureData = (short[])applicationBuffer.Read(cPos, typeof(short), LockFlag.None, 2048); 
			//			ushort[,] buf = null;
			//			buf = loadFFTshort(StreamCaptureData,(short)2048);
			//		}
		{
			ushort[] StreamCaptureData = null;
			StreamCaptureData = (ushort[])applicationBuffer.Read(cPos, typeof(ushort), LockFlag.None, 2048); 
			ushort[,] buf = null;
			buf = loadFFTushort(StreamCaptureData,2048);
		}

			//////			Pen pen = new Pen(Color.Purple, 1);
			//////
			//////			Graphics graph1 = Graphics.FromImage(bit1);
			//////			graph1.Clear(Color.Black);
			//////
			//////			int y = 0;
			//////
			//////			//for (int x = 0; x < (pictureBox1.Width*2)-1; x++)
			//////			for (int x = 0; x < 1000; x+=2)
			//////			{
			//////				//int m = x % 2;
			//////				int m = x % 4;
			//////
			//////				if (m == 0 || m == 1)
			//////				{
			//////					pen = new Pen(Color.Red, 1);
			//////					y = StreamCaptureData[x]*StreamCaptureData[x+1];
			//////					//progressBar1.Value= y;					
			//////				}
			//////				if (m == 2 || m == 3)
			//////				{
			//////					pen = new Pen(Color.Green, 1);
			//////					y = StreamCaptureData[x+2]*StreamCaptureData[x+3];
			//////					//y = StreamCaptureData[x+1];
			//////					//y = buf[x+1,1];
			//////				}
			//////
			//////
			//////				y/=(255*4);
			//////
			//////				//y = (int)(Math.Sqrt(StreamCaptureData[x]) * 3 * pictureBox1.Height - 4);
			//////				//y = StreamCaptureData[x];
			//////				if (y > pictureBox1.Height)
			//////					y = pictureBox1.Height;
			//////
			//////				pos = y;
			//////				//timer4_Tick(sender,e);
			//////
			//////				if (m == 0 )
			//////				{
			//////					graph1.DrawLine(pen, x/2, pictureBox1.Height/2 +y, x/2, pictureBox1.Height/2);
			//////				}
			//////				else
			//////				{
			//////					graph1.DrawLine(pen, x/2, pictureBox1.Height/2, x/2, pictureBox1.Height/2 - y);
			//////				}
			//////
			//////			}
			//////			pictureBox1.Image = bit1;
		}
	}

	private void timer4_Tick(object sender, System.EventArgs e)
	{
		int pos = 0;

		if ( applicationDevice == null)
			return;
        if (applicationBuffer == null)
			return;
		if (applicationBuffer.PlayPosition == 0)
			return;


		Graphics g = pictureBox2.CreateGraphics();

		SolidBrush myBrush = new SolidBrush(Color.LightGray);

//		pos += dir;
//		if (pos > 15)
//			dir = -1;
//		else
//			if (pos < 1)
//			dir = 1;

		for (int iLp = 0; iLp < 22;iLp++)
		{
			for (int b=0;b<17;b++)
			{
				myBrush.Color = Color.LightGray;
                if (b >= pos)
				{
					if (b<2)
						myBrush.Color = Color.Red;
					else
						if (b < 5)
						myBrush.Color = Color.Yellow;
					else
						myBrush.Color = Color.Green;
				}
				//g.FillRectangle(myBrush, new Rectangle((iLp*10), (b*7),8,5));
				g.FillRectangle(myBrush, new Rectangle((iLp*10), (b*7),5,3));
			}
		}
	}
	// working on
	private void timer5_Tick(object sender, System.EventArgs e)
	{
		if (applicationBuffer == null)
			return;

		label11.Text = applicationBuffer.Caps.PlayCpuOverhead.ToString();
		// moved to be public
		//FFT fft = new FFT();

		//Get cPos,cWrit;
		applicationBuffer.GetCurrentPosition(out fft.cPos,out fft.cWrit);

		//get the data into the class
		fft.StreamCaptureData = (short[])applicationBuffer.Read(fft.cPos, typeof(short), LockFlag.None, fft.FFT_LEN); 

		//label3.Text = "POS : " + fft.cPos.ToString() + " : " + fft.cWrit.ToString();
		label3.Text = fft.Pos2Time();

		double s;
		s = trackBar1.Value/100f;
		label1.Text = s.ToString();
		
		if (fft.cPos == 0)
		{
			fft.FFT_Plug_Hz(s,trackBar3.Value);
		}

		fft.fft_double((uint)fft.FFT_LEN,false,trackBar1.Value);

		fft.displayFreq();

		this.paint_picture_1_4();

	}

	private void trackBar3_Scroll(object sender, System.EventArgs e)
	{
		label4.Text = trackBar3.Value.ToString();
	}

}
