
// MainFrm.cpp : implementación de la clase CMainFrame
//

#include "stdafx.h"
#include "Tetris.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // indicador de la línea de estado
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// Construcción y destrucción de CMainFrame

CMainFrame::CMainFrame()
{
	// TODO: agregar aquí el código de inicialización de miembros
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("No se pudo crear la barra de herramientas\n");
		return -1;      // no se pudo crear
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("No se pudo crear la barra de estado\n");
		return -1;      // no se pudo crear
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: eliminar estas tres líneas si no desea que la barra de herramientas se pueda acoplar
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: modificar aquí la clase Window o los estilos cambiando
	//  CREATESTRUCT cs
	
	//cs.dwExStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	cs.style &= (0xFFFFFFFF ^ WS_SIZEBOX);
	cs.style |= WS_BORDER;
	cs.style &= (0xFFFFFFFF ^ WS_MAXIMIZEBOX);

	return TRUE;
}

// Diagnósticos de CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// Controladores de mensajes de CMainFrame



void CMainFrame::OnClose()
{
	if (MessageBox(_T("Está por abandonar el juego. ¿Desea continuar?"), _T("Confirmar cierre"), MB_YESNO) == IDYES)
	{
		exit(0);
	}
}


void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	AfxSetWindowText(m_hWnd ,_T("El Tetris"));

	//CFrameWnd::OnUpdateFrameTitle(bAddToTitle);
}
