
// TetrisDoc.h: interfaz de la clase CTetrisDoc
//


#pragma once

#include "stdafx.h"
#include "TetrisView.h"
#include "ColorGrid.h"
#include "Figure.h"

class Figure;

typedef CList<int> IntList;
const int FIGURE_ARRAY_SIZE = 7;

class CTetrisDoc : public CDocument
{
protected: // Crear sólo a partir de serialización
	CTetrisDoc();
	DECLARE_DYNCREATE(CTetrisDoc)

// Atributos
public:
	int GetScore() { return m_iScore; }
	const IntList* GetScoreList() { return &m_scoreList; }
	const ColorGrid* GetColorGrid() { return &m_colorGrid; }
	const Figure& GetActiveFigure() { return *m_activeFigure; }
	const Figure& GetNextFigure() { return *m_nextFigure; }

private:
	BOOL m_activeTimer;
	ColorGrid m_colorGrid;
	Figure* m_activeFigure;
	Figure* m_nextFigure;
	int m_iScore;
	IntList m_scoreList;
	const CRect NEXT_AREA, SCORE_AREA;
	static Figure* m_figureArray[FIGURE_ARRAY_SIZE];

// Operaciones
public:
	void LeftArrowKey();
	void RightArrowKey();
	void UpArrowKey();
	void DownArrowKey();
	BOOL Timer();
	void SpaceKey();
private:
	void GameOver();
	BOOL NewGame();
	int AddScoreToList();
	void DeleteFullRows();
	BOOL IsRowFull(int iRow);
	void FlashRow(int iFlashRow);
	void DeleteRow(int iDeleteRow);

// Reemplazos
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementación
public:
	virtual ~CTetrisDoc();
	void SaveScoreList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
	//DECLARE_DYNCREATE(CTetrisDoc) // Esto que hace??


#ifdef SHARED_HANDLERS
	// Función auxiliar que establece contenido de búsqueda para un controlador de búsqueda
	void SetSearchContent(const CString& value);
#endif 
	// SHARED_HANDLERS
public:
	afx_msg void OnNuevaPartida();
};