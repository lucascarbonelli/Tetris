
// Tetris.h: archivo de encabezado principal para la aplicación Tetris
//
#pragma once

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CTetrisApp:
// Consulte la sección Tetris.cpp para obtener información sobre la implementación de esta clase
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementación
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTetrisApp theApp;
