// waveInFFTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "waveInFFT.h"
#include "waveInFFTDlg.h"
#include "fourier.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveInFFTDlg dialog

CWaveInFFTDlg::CWaveInFFTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveInFFTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaveInFFTDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaveInFFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveInFFTDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaveInFFTDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveInFFTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EQ_MODE, OnEqMode)
	ON_BN_CLICKED(IDC_MICRO_EQ, OnMicroEq)
	ON_BN_CLICKED(IDC_OSCILLOSCOPE, OnOscilloscope)
	ON_BN_CLICKED(IDC_PEAK, OnPeak)
	ON_BN_CLICKED(IDC_PEAK_ALT, OnPeakAlt)
	ON_BN_CLICKED(IDC_PIXELGRAM, OnPixelgram)
	ON_BN_CLICKED(IDC_SPECTRUM, OnSpectrum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveInFFTDlg message handlers
inline double GetFrequencyIntensity(double re, double im)
{
	return sqrt((re*re)+(im*im));
}

BOOL Process(void* lpData, LPWAVEHDR pwh)
{
#define FFT_LEN 1024
	double fin[FFT_LEN],fout[FFT_LEN],foutimg[FFT_LEN],fdraw[FFT_LEN/2];
	static int sweep = 0;

	//int up = 0;
	//sweep +=10;
	//if (sweep > 20000)
	//	sweep = 20;

	for (DWORD dw = 0; dw < FFT_LEN; dw++)
	{
		//copy audio signal to fft real component.
		fin[dw] = (double)((short*)pwh->lpData)[dw];

		// 1 kHz calibration wave
		//fin[dw] = 1600 * sin (2 * PI * (1000.0 + sweep) * dw / 44100);

		// 1 kHz calibration wave
		//fin[dw] = 1600 * sin (2 * PI * 1000.0 * dw / 44100);
		// 10 kHz calibration wave
		fin[dw] = 1600 * sin (2 * PI * 20000.0 * dw / 44100);
	}



	fft_double(FFT_LEN,0,fin,NULL,fout,foutimg);
	float re,im;
	for(int i=0;i<FFT_LEN/2;i++)
	{
		re = fout[i];
		im = foutimg[i];
		//get frequency intensity and scale to 0..256 range
		fdraw[i]=(GetFrequencyIntensity(re,im))/256;
	}
////// create output for c#
//	TRACE("\n re = \n");
//TRACE("{");
//	for(int i=0;i<FFT_LEN/2;i++)
//	{
//		re = fout[i];
//		TRACE("%f, " , re);
//	}
//TRACE("}");
//TRACE("\n im = \n");
//TRACE("{");
//	for(int i=0;i<FFT_LEN/2;i++)
//	{
//		im = foutimg[i];
//		TRACE("%f, " , im);
//	}
//TRACE("}");
//TRACE("\n fdraw = \n");
//TRACE("{");
//	for(int i=0;i<FFT_LEN/2;i++)
//	{
//		fdraw[i]=(GetFrequencyIntensity(re,im))/256;
//		TRACE("%f, " , fdraw[i]);
//	}
//TRACE("}");

	CFrequencyGraph* pPeak = (CFrequencyGraph*)lpData;
	if (::IsWindow(pPeak->GetSafeHwnd()))
		pPeak->Update(FFT_LEN/2,fdraw);
	return TRUE;
}

BOOL CWaveInFFTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	CRect rct(0,0,375,300);
	m_graph.Create("STATIC","",WS_VISIBLE|WS_CHILD,rct,this,1001);
	m_rec.Open();
	m_rec.SetBufferFunction((void*)&m_graph,Process);
	m_rec.Start();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWaveInFFTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWaveInFFTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWaveInFFTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWaveInFFTDlg::OnEqMode() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_EQ_CHANNEL);
}

void CWaveInFFTDlg::OnMicroEq() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_MICRO_EQ);
}

void CWaveInFFTDlg::OnOscilloscope() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_OSCILLOSCOPE);
}

void CWaveInFFTDlg::OnPeak() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PEAK);
}

void CWaveInFFTDlg::OnPeakAlt() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PEAK2);
}

void CWaveInFFTDlg::OnPixelgram() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PIXELGRAM);
}

void CWaveInFFTDlg::OnSpectrum() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_SPECTRUM);
}
