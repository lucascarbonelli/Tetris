
// TetrisDoc.cpp: implementación de la clase CTetrisDoc
//

#include "stdafx.h"
// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "DialogFinPartida.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTetrisDoc

IMPLEMENT_DYNCREATE(CTetrisDoc, CDocument)

BEGIN_MESSAGE_MAP(CTetrisDoc, CDocument)
	ON_COMMAND(ID_NUEVA_PARTIDA, &CTetrisDoc::OnNuevaPartida)
END_MESSAGE_MAP()

// Figures
Figure redFigure(NORTH, RED, RedInfo);
Figure brownFigure(NORTH, BROWN, BrownInfo);
Figure turquoiseFigure(NORTH, TURQUOISE, TurquoiseInfo);
Figure greenFigure(NORTH, GREEN, GreenInfo);
Figure blueFigure(NORTH, BLUE, BlueInfo);
Figure purpleFigure(NORTH, PURPLE, PurpleInfo);
Figure yellowFigure(NORTH, YELLOW, YellowInfo);
Figure *CTetrisDoc::m_figureArray[] = { &redFigure, &brownFigure, &turquoiseFigure, &greenFigure, &blueFigure, &purpleFigure, &yellowFigure };

// Construcción o destrucción de CTetrisDoc

CTetrisDoc::CTetrisDoc() : 
	m_activeTimer(TRUE),
	m_colorGrid(ColorGrid()), 
	m_iScore(0),
	NEXT_AREA(CRect(COLS, 0, COLS * 2, ROWS / 2)),
	SCORE_AREA(CRect(COLS, ROWS / 2, COLS * 2, ROWS))
{
	m_activeFigure = new Figure;
	m_nextFigure = new Figure;
	m_activeFigure->SetColorGrid(&m_colorGrid);

	srand(time(NULL));

	*m_activeFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
	*m_nextFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
}

CTetrisDoc::~CTetrisDoc()
{
	delete m_activeFigure;
	delete m_nextFigure;
}

void CTetrisDoc::SaveScoreList()
{
}

BOOL CTetrisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//m_colorGrid.Clear();
	// TODO: agregar aquí código de reinicio
	// (los documentos SDI volverán a utilizar este documento)

	return TRUE;
}




// Serialización de CTetrisDoc

void CTetrisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aquí el código de almacenamiento
	}
	else
	{
		// TODO: agregar aquí el código de carga
	}
}

#ifdef SHARED_HANDLERS

// Compatibilidad con miniaturas
void CTetrisDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modifique este código para dibujar los datos del documento
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Compatibilidad con controladores de búsqueda
void CTetrisDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Establezca contenido de búsqueda a partir de los datos del documento. 
	// Las partes de contenido deben ir separadas por ";"

	// Por ejemplo:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTetrisDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Diagnósticos de CTetrisDoc

#ifdef _DEBUG
void CTetrisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTetrisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandos de CTetrisDoc

void CTetrisDoc::LeftArrowKey()
{
	CRect crOldArea = m_activeFigure->GetArea();
	if (m_activeFigure->MoveLeft())
	{
		CRect crNewArea = m_activeFigure->GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&crOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&crNewArea);
		SetModifiedFlag(); // por que es necesario??
	}
}

void CTetrisDoc::RightArrowKey()
{
	CRect crOldArea = m_activeFigure->GetArea();
	if (m_activeFigure->MoveRigth())
	{
		CRect crNewArea = m_activeFigure->GetArea();
		UpdateAllViews(NULL, COLOR, (CObject*)&crOldArea);
		UpdateAllViews(NULL, COLOR, (CObject*)&crNewArea);
		SetModifiedFlag(); // por que es necesario??
	}
}

void CTetrisDoc::UpArrowKey()
{
	CRect crOldArea = m_activeFigure->GetArea();
	m_activeFigure->RotateClockwise();
	CRect crNewArea = m_activeFigure->GetArea();
	UpdateAllViews(NULL, COLOR, (CObject*)&crOldArea);
	UpdateAllViews(NULL, COLOR, (CObject*)&crNewArea);
	SetModifiedFlag(); // por que es necesario??
}

void CTetrisDoc::DownArrowKey()
{
	CRect crOldArea = m_activeFigure->GetArea();
	m_activeFigure->RotateCounterclockwise();
	CRect crNewArea = m_activeFigure->GetArea();
	UpdateAllViews(NULL, COLOR, (CObject*)&crOldArea);
	UpdateAllViews(NULL, COLOR, (CObject*)&crNewArea);
	SetModifiedFlag(); // por que es necesario??
}

BOOL CTetrisDoc::Timer()
{
	if (m_activeTimer)
	{
		SetModifiedFlag(); // ??
		CRect crOldArea = m_activeFigure->GetArea();
		if (m_activeFigure->MoveDown())
		{
			CRect crNewArea = m_activeFigure->GetArea();
			UpdateAllViews(NULL, COLOR, (CObject*)&crOldArea);
			UpdateAllViews(NULL, COLOR, (CObject*)&crNewArea);
			return TRUE;
		}
		else
		{
			m_activeFigure->AddToGrid();
			*m_activeFigure = *m_nextFigure;
			CRect crActiveArea = m_activeFigure->GetArea();
			UpdateAllViews(NULL, COLOR, (CObject*)&crActiveArea);
			*m_nextFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
			UpdateAllViews(NULL, COLOR, (CObject*)&NEXT_AREA); // como solucionarlo!?
			DeleteFullRows();
			if (!m_activeFigure->IsFigureValid())
			{
				GameOver();
			}
		}
		return FALSE;
	}
}

void CTetrisDoc::SpaceKey()
{
	while (Timer())
	{
		Sleep(20);
	}
}

void CTetrisDoc::GameOver()
{
	UpdateAllViews(NULL, GRAY);
	if (NewGame())
	{
		m_iScore = 0;
		m_colorGrid.Clear();
		*m_activeFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		*m_nextFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		UpdateAllViews(NULL, COLOR);
	}
	else
	{
		SaveScoreList();
		m_activeTimer = FALSE;
	}
}

BOOL CTetrisDoc::NewGame()
{
	DialogFinPartida Dialog(m_iScore);
	if (Dialog.DoModal() == IDOK)
	{
		m_activeTimer = TRUE;
		return TRUE;
	}
	return FALSE;
}

void CTetrisDoc::DeleteFullRows()
{
	int iRow = ROWS - 1;
	while (iRow >= 0) 
	{
		if (IsRowFull(iRow))
		{
			FlashRow(iRow);
			DeleteRow(iRow);
			++m_iScore;
			UpdateAllViews(NULL, COLOR, (CObject*) &SCORE_AREA);
		}
		else
		{
			--iRow;
		}
	}
}

BOOL CTetrisDoc::IsRowFull(int iRow)
{
	for (size_t iCol = 0; iCol < COLS; ++iCol)
	{
		if (m_colorGrid.Index(iRow, iCol) == DEFAULT_COLOR)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CTetrisDoc::FlashRow(int iFlashRow)
{
	for (int iCount = 0; iCount < 3; iCount++)
	{
		CRect rcRowArea(0, iFlashRow, COLS, iFlashRow + 1);
		UpdateAllViews(NULL, GRAY, (CObject*)&rcRowArea);
		Sleep(50);
		CRect rcRowArea2(0, iFlashRow, COLS, iFlashRow + 1);
		UpdateAllViews(NULL, COLOR, (CObject*)&rcRowArea2);
		Sleep(50);
	}
}

void CTetrisDoc::DeleteRow(int iDeleteRow)
{
	for (int iRow = iDeleteRow; iRow > 0; --iRow)
	{
		for (int iCol = 0; iCol < COLS; ++iCol)
		{
			m_colorGrid.Index(iRow, iCol) = m_colorGrid.Index(iRow - 1, iCol);
		}
	}
	for (int iCol = 0; iCol < COLS; ++iCol)
	{
		m_colorGrid.Index(0, iCol) = WHITE;
	}
	CRect rcArea(0, 0, COLS, iDeleteRow + 1); // por que????
	UpdateAllViews(NULL, COLOR, (CObject*)&rcArea);
}


void CTetrisDoc::OnNuevaPartida()
{
	UpdateAllViews(NULL, GRAY);
	if (NewGame())
	{
		m_iScore = 0;
		m_colorGrid.Clear();
		*m_activeFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		*m_nextFigure = *m_figureArray[rand() % FIGURE_ARRAY_SIZE];
		UpdateAllViews(NULL, COLOR);
	}
}
