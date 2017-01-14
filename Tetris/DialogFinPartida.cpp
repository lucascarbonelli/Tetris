// DialogFinPartida.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Tetris.h"
#include "DialogFinPartida.h"
#include "afxdialogex.h"


// Cuadro de diálogo de DialogFinPartida

IMPLEMENT_DYNAMIC(DialogFinPartida, CDialogEx)

DialogFinPartida::DialogFinPartida(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FIN_PARTIDA, pParent)
	, scoreText(_T("Puntaje no disponible"))
{
}

DialogFinPartida::DialogFinPartida(UINT iScore, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FIN_PARTIDA, pParent)
{
	scoreText.Format(_T("Puntaje: %u"), iScore);
}

DialogFinPartida::~DialogFinPartida()
{
}

void DialogFinPartida::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCORE, scoreText);
}


BEGIN_MESSAGE_MAP(DialogFinPartida, CDialogEx)
//	ON_STN_CLICKED(IDC_SCORE_MSG, &DialogFinPartida::OnStnClickedScoreMsg)
END_MESSAGE_MAP()


// Controladores de mensajes de DialogFinPartida
