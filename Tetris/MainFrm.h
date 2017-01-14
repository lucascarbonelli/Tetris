
// MainFrm.h: interfaz de la clase CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // Crear s�lo a partir de serializaci�n
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Atributos
public:

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementaci�n
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Miembros incrustados de la barra de control
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Funciones de asignaci�n de mensajes generadas
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
};

