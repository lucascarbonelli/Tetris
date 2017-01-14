#include "stdafx.h"
#include "Figure.h"

int g_iRowHeight = 30;
int g_iColWidth = 30;

SquareInfo RedInfo = { 
	{ Square(0, 0), Square(0, 1), Square(1, 1), Square(1, 0) },
	{ Square(0, 0), Square(0, 1), Square(1, 1), Square(1, 0) },
	{ Square(0, 0), Square(0, 1), Square(1, 1), Square(1, 0) },
	{ Square(0, 0), Square(0, 1), Square(1, 1), Square(1, 0) } 
};

SquareInfo BrownInfo = { 
	{ Square(0,0), Square(-1,0), Square(1,0), Square(2,0) },
	{ Square(0,0), Square(0,-1), Square(0,1), Square(0,2) },
	{ Square(0,0), Square(-1,0), Square(1,0), Square(2,0) },
	{ Square(0,0), Square(0,-1), Square(0,1), Square(0,2) } 
};

SquareInfo TurquoiseInfo = {
	{ Square(0,0), Square(-1,0), Square(0,1), Square(1,1) },
	{ Square(0,0), Square(1,-1), Square(1,0), Square(0,1) },
	{ Square(0,0), Square(-1,0), Square(0,1), Square(1,1) },
	{ Square(0,0), Square(1,-1), Square(1,0), Square(0,1) }
};

SquareInfo GreenInfo = {
	{ Square(0,0), Square(1,-1), Square(0,-1), Square(-1,0) },
	{ Square(0,0), Square(0,-1), Square(1,0), Square(1,1) },
	{ Square(0,0), Square(1,-1), Square(0,-1), Square(-1,0) },
	{ Square(0,0), Square(0,-1), Square(1,0), Square(1,1) }
};

SquareInfo BlueInfo = {
	{ Square(0,0), Square(0,-2), Square(0,-1), Square(-1,0) },
	{ Square(0,0), Square(-2,0), Square(-1,0), Square(0,1) },
	{ Square(0,0), Square(1,0), Square(0,1), Square(0,2) },
	{ Square(0,0), Square(0,-1), Square(1,0), Square(2,0) }
};

SquareInfo PurpleInfo = {
	{ Square(0,0), Square(-1,0), Square(0,1), Square(0,2) },
	{ Square(0,0), Square(1,0), Square(2,0), Square(0,1) },
	{ Square(0,0), Square(0,-2), Square(0,-1), Square(1,0) },
	{ Square(0,0), Square(0,-1), Square(-2,0), Square(-1,0) }
};

SquareInfo YellowInfo = {
	{ Square(0,0), Square(0,-1), Square(-1,0), Square(0,1) },
	{ Square(0,0), Square(-1,0), Square(0,1), Square(1,0) },
	{ Square(0,0), Square(0,-1), Square(1,0), Square(0,1) },
	{ Square(0,0), Square(-1,0), Square(0,-1), Square(1,0) }
};

Figure::Figure()
{
}

Figure::Figure(int iDirection, COLORREF rfColor, const SquareInfo & squareInfo) :
	m_iRow(1),
	m_iCol(COLS / 2),
	m_iDirection(iDirection),
	m_rfColor(rfColor),
	m_pColorGrid(NULL)
{
	::memcpy(&m_squareInfo, &squareInfo, sizeof(m_squareInfo));
}


Figure::~Figure()
{
	m_pColorGrid = NULL;
}

Figure Figure::operator=(const Figure & figure)
{
	m_rfColor = figure.m_rfColor;
	m_iRow = figure.m_iRow;
	m_iCol = figure.m_iCol;
	m_iDirection = figure.m_iDirection;

	for (size_t i = 0; i < SQUARE_INFO_SIZE; ++i)
	{
		for (size_t j = 0; j < SQUARE_ARRAY_SIZE; ++j)
		{
			m_squareInfo[i][j] = Square(figure.m_squareInfo[i][j].Row(), figure.m_squareInfo[i][j].Col());
		}
	}
	
	return *this;
	//return Figure();
}

BOOL Figure::IsSquareValid(int iRow, int iCol) const
{
	return	(iRow >= 0) && (iRow < ROWS) &&
		(iCol >= 0) && (iCol < COLS) &&
		(m_pColorGrid->Index(iRow, iCol) == DEFAULT_COLOR);
}

BOOL Figure::IsFigureValid() const
{
	//SquareArray* pSquareArray = m_squareInfo[m_iDirection];
	for (int iIndex = 0; iIndex < SQUARE_ARRAY_SIZE; ++iIndex)
	{
		const Square& square = (m_squareInfo[m_iDirection])[iIndex];
		if (!IsSquareValid(m_iRow + square.Row(), m_iCol + square.Col()))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Figure::MoveLeft()
{
	--m_iCol;
	if (IsFigureValid())
	{
		return TRUE;
	}
	else
	{
		++m_iCol;
		return FALSE;
	}
}

BOOL Figure::MoveRigth()
{
	++m_iCol;
	if (IsFigureValid())
	{
		return TRUE;
	}
	else
	{
		--m_iCol;
		return FALSE;
	}
}

void Figure::RotateClockwiseOneQuarter()
{
	switch (m_iDirection)
	{
	case NORTH:
		m_iDirection = EAST;
		break;
	case EAST:
		m_iDirection = SOUTH;
		break;
	case SOUTH:
		m_iDirection = WEST;
		break;
	case WEST:
		m_iDirection = NORTH;
		break;
	}
}

void Figure::RotateCounterclockwiseOneQuarter()
{
	switch (m_iDirection)
	{
	case NORTH:
		m_iDirection = WEST;
		break;
	case WEST:
		m_iDirection = SOUTH;
		break;
	case SOUTH:
		m_iDirection = EAST;
		break;
	case EAST:
		m_iDirection = NORTH;
		break;
	}
}

void Figure::RotateClockwise()
{
	RotateClockwiseOneQuarter();
	if (!IsFigureValid()) 
	{
		RotateCounterclockwiseOneQuarter();
	}
}

void Figure::RotateCounterclockwise()
{
	RotateCounterclockwiseOneQuarter();
	if (!IsFigureValid())
	{
		RotateClockwiseOneQuarter();
	}
}

BOOL Figure::MoveDown()
{
	++m_iRow;
	if (IsFigureValid())
	{
		return TRUE;
	}
	else
	{
		--m_iRow;
		return FALSE;
	}
}

void Figure::AddToGrid()
{
	//SquareArray* pSquareArray = m_squareInfo[m_iDirection];
	for (int iIndex = 0; iIndex < SQUARE_ARRAY_SIZE; ++iIndex)
	{
		Square& square = (m_squareInfo[m_iDirection])[iIndex];
		m_pColorGrid->Index(m_iRow + square.Row(), m_iCol + square.Col()) = m_rfColor;
	}
}

CRect Figure::GetArea() const
{
	int iMinRow = 0, iMaxRow = 0, iMinCol = 0, iMaxCol = 0;
	//SquareArray* pSquareArray = m_squareInfo[m_iDirection];
	for (int iIndex = 0; iIndex < SQUARE_ARRAY_SIZE; ++iIndex)
	{
		const Square& square = (m_squareInfo[m_iDirection])[iIndex];
		int iRow = square.Row();
		iMinRow = (iRow < iMinRow) ? iRow : iMinRow;
		iMaxRow = (iRow > iMaxRow) ? iRow : iMaxRow;
		int iCol = square.Col();
		iMinCol = (iCol < iMinCol) ? iCol : iMinCol;
		iMaxCol = (iCol > iMaxCol) ? iCol : iMaxCol;
	}
	return CRect(m_iCol + iMinCol, m_iRow + iMinRow, m_iCol + iMaxCol + 1, m_iRow + iMaxRow + 1);
}

void Figure::Draw(int iColorStatus, CDC * pDC)
{
	CPen pen(PS_SOLID, 0, BLACK);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush((iColorStatus == COLOR) ? m_rfColor : GrayScale(m_rfColor));
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	//SquareArray* pSquareArray = m_squareInfo[m_iDirection];
	for (int iIndex = 0; iIndex < SQUARE_ARRAY_SIZE; ++iIndex)
	{
		Square& square = (m_squareInfo[m_iDirection])[iIndex];
		DrawSquare(m_iRow + square.Row(), m_iCol + square.Col(), pDC);
	}
	pDC->SelectObject(&pOldPen);
	pDC->SelectObject(&pOldBrush);
}

void DrawSquare(int iRow, int iCol, CDC * pDC)
{
	pDC->Rectangle(iCol * g_iRowHeight, (iRow + 1) * g_iRowHeight, (iCol + 1) * g_iColWidth, iRow * g_iRowHeight);
}
