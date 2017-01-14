#include "stdafx.h"
#include "ColorGrid.h"


ColorGrid::ColorGrid()
{
	for (size_t i = 0; i < ROWS * COLS; ++i)
	{
		m_buffer[i] = RGB(255,255,255);
	}
}


ColorGrid::~ColorGrid()
{
}

void ColorGrid::Clear()
{
	for (size_t i = 0; i < ROWS * COLS; ++i)
	{
		m_buffer[i] = RGB(255, 255, 255);
	}
}

COLORREF & ColorGrid::Index(int iRow, int iCol)
{
	ASSERT((iRow >= 0) && (iRow < ROWS));
	ASSERT((iCol >= 0) && (iCol < COLS));
	return m_buffer[iRow * COLS + iCol];
}

const COLORREF ColorGrid::Index(int iRow, int iCol) const
{
	ASSERT((iRow >= 0) && (iRow < ROWS));
	ASSERT((iCol >= 0) && (iCol < COLS));
	return m_buffer[iRow * COLS + iCol];
}
