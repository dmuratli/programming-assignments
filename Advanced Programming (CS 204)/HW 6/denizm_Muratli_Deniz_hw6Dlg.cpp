
// denizm_Muratli_Deniz_hw6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "denizm_Muratli_Deniz_hw6.h"
#include "denizm_Muratli_Deniz_hw6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cdenizm_Muratli_Deniz_hw6Dlg dialog

Cdenizm_Muratli_Deniz_hw6Dlg::Cdenizm_Muratli_Deniz_hw6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cdenizm_Muratli_Deniz_hw6Dlg::IDD, pParent)
	, operationChoice(0)
	, operand1()
	, operand2()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cdenizm_Muratli_Deniz_hw6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, operationChoice);
	//  DDX_Text(pDX, IDC_EDIT1, operand1);
	//  DDX_Text(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_EDIT1, operand1);
	DDX_Control(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_CHECK1, shiftCheck);
	DDX_Control(pDX, IDC_EDIT3, bitsToShift);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_COMBO1, shiftDirection);
}

BEGIN_MESSAGE_MAP(Cdenizm_Muratli_Deniz_hw6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &Cdenizm_Muratli_Deniz_hw6Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Cdenizm_Muratli_Deniz_hw6Dlg message handlers

BOOL Cdenizm_Muratli_Deniz_hw6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

void Cdenizm_Muratli_Deniz_hw6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cdenizm_Muratli_Deniz_hw6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cdenizm_Muratli_Deniz_hw6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void Cdenizm_Muratli_Deniz_hw6Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  Add your control notification handler code here
}

int maxSize=0;

void Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedButton1()
{
	CString operandOne, operandTwo, nFOperand, nSOperand, result, operationResult, operationType, shiftD, shiftBy;
	CDC *pDC=GetDC();
	CSize cz;
	operand1.GetWindowTextW(operandOne);
	operand2.GetWindowTextW(operandTwo);
	if (operandOne.GetLength()>0 && operandTwo.GetLength()>0){ //Checks whether both operands are entered
		unsigned int fOperand=_tcstoul(operandOne, nullptr, 10), sOperand=_tcstoul(operandTwo, nullptr, 10); //Converts the operands to unsigned integers
		if (shiftCheck.GetCheck()==1){ //Checks whether the user wants to shift the operands before applying an operation on them and handles shifting
			bitsToShift.GetWindowTextW(shiftBy);
			if (shiftBy.GetLength()>0){ //Checks whether the user entered how many bits to shift and takes the necessary action according to it
				int selectedIdx=shiftDirection.GetCurSel();
				shiftDirection.GetLBText(selectedIdx, shiftD);
				unsigned int noBits=_tcstoul(shiftBy, nullptr, 10);
				if (shiftD=="Left"){
					fOperand=fOperand<<noBits;
					sOperand=sOperand<<noBits;
				}else if (shiftD=="Right"){
					fOperand=fOperand>>noBits;
					sOperand=sOperand>>noBits;
				}else{
					;
				}
				nFOperand.Format(_T("%u"), fOperand);
				nSOperand.Format(_T("%u"), sOperand);
			}else{
				result=_T("Specify how many bits you want to shift.");
				list.AddString(result);
				cz=pDC->GetTextExtent(result);
				if (cz.cx>maxSize){
					maxSize=cz.cx;
				}
				list.SetHorizontalExtent(maxSize);
				return;
			}
		}else{
			nFOperand.Format(_T("%u"), fOperand);
			nSOperand.Format(_T("%u"), sOperand);
		}
		UpdateData(TRUE);
		if (operationChoice==0){ //Checks which operation the user wants to perform on the operands and handles the operation
			operationType=_T("AND");
			unsigned int res=(fOperand & sOperand);
			operationResult.Format(_T("%u"), res);
			result=nFOperand+_T(" ")+operationType+_T(" ")+nSOperand+_T(" = ")+operationResult;
		}else if (operationChoice==1){
			operationType=_T("OR");
			unsigned int res=(fOperand | sOperand);
			operationResult.Format(_T("%u"), res);
			result=nFOperand+_T(" ")+operationType+_T(" ")+nSOperand+_T(" = ")+operationResult;
		}else if (operationChoice==2){
			operationType=_T("XOR");
			unsigned int res=(fOperand ^ sOperand);
			operationResult.Format(_T("%u"), res);
			result=nFOperand+_T(" ")+operationType+_T(" ")+nSOperand+_T(" = ")+operationResult;
		}else{
			;
		}
		list.AddString(result);
		cz=pDC->GetTextExtent(result);
		if (cz.cx>maxSize){
			maxSize=cz.cx;
		}
		list.SetHorizontalExtent(maxSize);
	}else{
		result=_T("At least 1 operand was not entered.");
		list.AddString(result);
		cz=pDC->GetTextExtent(result);
		if (cz.cx>maxSize){
			maxSize=cz.cx;
		}
		list.SetHorizontalExtent(maxSize);
	}
	return;
}

void Cdenizm_Muratli_Deniz_hw6Dlg::OnBnClickedCheck1()
{
	if (shiftCheck.GetCheck()==1){
		shiftDirection.EnableWindow(TRUE);
		bitsToShift.EnableWindow(TRUE);
	}else{
		shiftDirection.EnableWindow(FALSE);
		bitsToShift.EnableWindow(FALSE);
	}
}
