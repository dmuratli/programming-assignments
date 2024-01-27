
// denizm_Muratli_Deniz_hw6Dlg.h : header file
//

#pragma once
#include "afxwin.h"

// Cdenizm_Muratli_Deniz_hw6Dlg dialog
class Cdenizm_Muratli_Deniz_hw6Dlg : public CDialogEx
{
// Construction
public:
	Cdenizm_Muratli_Deniz_hw6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DENIZM_MURATLI_DENIZ_HW6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	int operationChoice;
	afx_msg void OnEnChangeEdit2();
	CEdit operand1;
	CEdit operand2;
	CButton shiftCheck;
	CEdit bitsToShift;
	CListBox list;
	afx_msg void OnBnClickedButton1();
	CComboBox shiftDirection;
	afx_msg void OnBnClickedCheck1();
};
