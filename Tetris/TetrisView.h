
// TetrisView.h: interfaz de la clase CTetrisView
//

#pragma once

#include "stdafx.h"
#include "TetrisDoc.h"
//#include "Figure.h"

const int TIMER_ID = 0;
enum {COLOR = 0, GRAY = 1};
class CTetrisDoc; //¿¿??
COLORREF GrayScale(COLORREF rfColor);

class CTetrisView : public CView
{
protected: // Crear sólo a partir de serialización
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView);

// Atributos
public:
	CTetrisDoc* GetDocument() const;
private:
	CTetrisDoc* m_pTetrisDoc;
	int m_iColorStatus;
// Operaciones
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpcreatestruct);
	afx_msg void OnSize(UINT nType, int iClientWidth, int iClientHight);

	void OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint);
	//void OnDraw(CDC* pDC);
private:
	void DrawGrid(CDC* pDC);
	void DrawScoreAndScoreList(CDC* pDC);
	void DrawActiveAndNextFigure(CDC* pDC);
// Reemplazos
public:
	virtual void OnDraw(CDC* pDC);  // Reemplazado para dibujar esta vista
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementación
public:
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // Versión de depuración en TetrisView.cpp
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

