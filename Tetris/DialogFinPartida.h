#pragma once
#include "afxwin.h"


// Cuadro de diálogo de DialogFinPartida

class DialogFinPartida : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFinPartida)

public:
	DialogFinPartida(CWnd* pParent = NULL);   // Constructor estándar
	DialogFinPartida(UINT iScore, CWnd * pParent = NULL);
	virtual ~DialogFinPartida();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIN_PARTIDA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClickedScoreMsg();
	CString scoreText;
};
