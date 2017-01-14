
// TetrisView.cpp: implementación de la clase CTetrisView
//

// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#pragma once

#include "stdafx.h"
#include "TetrisView.h"
#include "TetrisDoc.h"
#include "Figure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	// Comandos de impresión estándar
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()

	ON_WM_KEYDOWN()
//	ON_WM_CLOSE()
//ON_COMMAND(ID_NUEVA_PARTIDA, &CTetrisView::OnNuevaPartida)
END_MESSAGE_MAP()

// Construcción o destrucción de CTetrisView

CTetrisView::CTetrisView() : m_iColorStatus(COLOR), m_pTetrisDoc(NULL)
{
	// TODO: agregar aquí el código de construcción
	//m_pTetrisDoc = GetDocument();
	m_pTetrisDoc = (CTetrisDoc*)m_pDocument;
}

CTetrisView::~CTetrisView()
{
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aquí la clase Window o los estilos cambiando
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Dibujo de CTetrisView

void CTetrisView::OnUpdate(CView *, LPARAM lHint, CObject * pHint)
{
	m_iColorStatus = (int)lHint;
	if (pHint != NULL)
	{
		CRect rcArea = *(CRect*)pHint;
		rcArea.left *= g_iColWidth;
		rcArea.right *= g_iColWidth;
		rcArea.top *= g_iRowHeight;
		rcArea.bottom *= g_iRowHeight;
		InvalidateRect(rcArea);
	}
	else
	{
		Invalidate();
	}
	UpdateWindow();
}

void CTetrisView::OnDraw(CDC* pDC)
{
	/*
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	*/
	SetWindowText(_T("Tetris"));

	CPen pen(PS_SOLID, 0, BLACK);
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(COLS * g_iColWidth, 0); // Dibuja una linea vertical en el medio para separar el area
	pDC->LineTo(COLS * g_iColWidth, ROWS * g_iRowHeight); // del juego y el puntaje/next_figure

	m_pTetrisDoc = (CTetrisDoc*)m_pDocument;

	DrawGrid(pDC);
	DrawScoreAndScoreList(pDC);
	DrawActiveAndNextFigure(pDC);
	pDC->SelectObject(&pOldPen);
}

void CTetrisView::DrawGrid(CDC * pDC)
{
	const ColorGrid* pGrid = m_pTetrisDoc->GetColorGrid();
	for (int iRow = 0; iRow < ROWS; ++iRow)
	{
		for (int iCol = 0; iCol < COLS; ++iCol)
		{
			COLORREF rfColor = pGrid->Index(iRow, iCol);
			if (rfColor != WHITE)
			{
				CBrush brush((m_iColorStatus == COLOR) ? rfColor : GrayScale(rfColor));
				CBrush* pOldBrush = pDC->SelectObject(&brush);
				DrawSquare(iRow, iCol, pDC); // ???????????
				pDC->SelectObject(&pOldBrush);
			}
		}
	}
}

void CTetrisView::DrawScoreAndScoreList(CDC * pDC)
{
	CFont font;
	font.CreatePointFont(120, _T("Arial"), pDC);
	CFont* defFont = pDC->SelectObject(&font);
	pDC->TextOutW(COLS * g_iColWidth * 1.2, ROWS * g_iRowHeight * 0.5, _T("Puntaje: "));
	font.DeleteObject();
	
	
	CFont font2;
	font.CreatePointFont(360, _T("Arial"), pDC);
	pDC->SelectObject(&font);
	CString score;
	score.Format(_T("%.4u"), m_pTetrisDoc->GetScore());
	pDC->TextOutW((int)COLS * g_iColWidth * 1.4, (int)ROWS * g_iRowHeight * 0.55, score);
	pDC->SelectObject(defFont);
	font2.DeleteObject();
}

void CTetrisView::DrawActiveAndNextFigure(CDC * pDC)
{
	Figure activeFigure = m_pTetrisDoc->GetActiveFigure();
	activeFigure.Draw(m_iColorStatus, pDC);
	Figure nextFigure = m_pTetrisDoc->GetNextFigure();
	CPoint ptOrigin(-COLS * g_iColWidth, -g_iRowHeight);
	pDC->SetWindowOrg(ptOrigin);
	nextFigure.Draw(m_iColorStatus, pDC);
}


// Impresión de CTetrisView

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Preparación predeterminada
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar inicialización adicional antes de imprimir
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar limpieza después de imprimir
}


// Diagnósticos de CTetrisView

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // La versión de no depuración está alineada
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// Controladores de mensaje de CTetrisView

afx_msg int CTetrisView::OnCreate(LPCREATESTRUCT lpcreatestruct)
{
	if (CView::OnCreate(lpcreatestruct) == -1)
	{
		return -1;
	}

	m_pTetrisDoc = (CTetrisDoc*)m_pDocument;
	ASSERT_VALID((CObject*)m_pTetrisDoc);
	return 0;
}


void CTetrisView::OnSize(UINT nType, int iClientWidth, int iClientHight)
{
	g_iRowHeight = iClientHight / ROWS;
	g_iColWidth = (iClientWidth / 2) / COLS;
}


COLORREF GrayScale(COLORREF rfColor)
{
	int iRed = GetRValue(rfColor);
	int iGreen = GetGValue(rfColor);
	int iBlue = GetBValue(rfColor);
	int iAverage = (iRed + iGreen + iBlue) / 3;
	return RGB(iAverage, iAverage, iAverage);
}


void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	m_pTetrisDoc->Timer();
}


void CTetrisView::OnSetFocus(CWnd* pOldWnd)
{
	SetTimer(TIMER_ID, 200, NULL);
}


void CTetrisView::OnKillFocus(CWnd* pNewWnd)
{
	KillTimer(TIMER_ID);
}


void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_LEFT:
		m_pTetrisDoc->LeftArrowKey();
		break;
	case VK_RIGHT:
		m_pTetrisDoc->RightArrowKey();
		break;
	case VK_UP:
		m_pTetrisDoc->UpArrowKey();
		break;
	case VK_DOWN:
		m_pTetrisDoc->DownArrowKey();
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}