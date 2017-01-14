#pragma once
class Square
{
public:
	Square();
	Square(int iRow, int iCol);
	~Square();

	int Row() const { return m_iRow; }
	int Col() const { return m_iCol; }

private:
	int m_iRow, m_iCol;
};

