
// Tetris.h: archivo de encabezado principal para la aplicaci�n Tetris
//
#pragma once

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // S�mbolos principales


// CTetrisApp:
// Consulte la secci�n Tetris.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementaci�n
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTetrisApp theApp;
