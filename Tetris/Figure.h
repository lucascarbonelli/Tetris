#pragma once

#include "TetrisView.h"
#include "Square.h"
#include "ColorGrid.h"

const COLORREF BLACK = RGB(0, 0, 0);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF DEFAULT_COLOR = WHITE;
class ColorGrid;
class Square;
extern int g_iRowHeight, g_iColWidth;
enum{NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

const int SQUARE_ARRAY_SIZE = 4;
const int SQUARE_INFO_SIZE = 4;
typedef Square SquareArray[SQUARE_ARRAY_SIZE];
typedef SquareArray SquareInfo[SQUARE_INFO_SIZE];



// FigureInfo
const COLORREF RED = RGB(255, 0, 0);
const COLORREF BROWN = RGB(256, 128, 0);
const COLORREF TURQUOISE = RGB(0, 255, 255);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF BLUE = RGB(0, 0, 255);
const COLORREF PURPLE = RGB(255, 0, 255);
const COLORREF YELLOW = RGB(255, 255, 0);

// The RED Figure
//SquareArray RedGeneric = { Square(0, 0), Square(0, 1), Square(1, 1), Square(1, 0) };

extern SquareInfo RedInfo;
extern SquareInfo BrownInfo;
extern SquareInfo TurquoiseInfo;
extern SquareInfo GreenInfo;
extern SquareInfo BlueInfo;
extern SquareInfo PurpleInfo;
extern SquareInfo YellowInfo;

// Figure
class Figure
{
public:
	Figure();
	Figure(int iDirection, COLORREF rfColor, const SquareInfo& squareInfo);
	~Figure();

	Figure operator=(const Figure& figure);
	void SetColorGrid(ColorGrid* pColorGrid) { m_pColorGrid = pColorGrid; };

private:
	BOOL IsSquareValid(int iRow, int iCol) const;

public:
	BOOL IsFigureValid() const;
	BOOL MoveLeft();
	BOOL MoveRigth();

private:
	void RotateClockwiseOneQuarter();
	void RotateCounterclockwiseOneQuarter();

public:
	void RotateClockwise();
	void RotateCounterclockwise();
	BOOL MoveDown();
	void AddToGrid();
	CRect GetArea() const;

public:
	void Draw(int iColorStatus, CDC *pDC);
	friend void DrawSquare(int iRow, int iCol, CDC *pDC);

public:
	void Serialize(CArchive& archive);

private:
	COLORREF m_rfColor;
	ColorGrid* m_pColorGrid;
	int m_iRow, m_iCol, m_iDirection;
	SquareInfo m_squareInfo;
};

typedef CArray<const Figure> FigurePtrArray;