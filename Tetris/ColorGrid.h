#pragma once

const int COLS = 20;
const int ROWS = 20;

class ColorGrid
{
public:
	ColorGrid();
	~ColorGrid();

	void Clear();

	COLORREF& Index(int iRow, int iCol);
	const COLORREF Index(int iRow, int iCol) const;

	void Serialize(CArchive& archive);

private:
	COLORREF m_buffer[ROWS * COLS];
};

