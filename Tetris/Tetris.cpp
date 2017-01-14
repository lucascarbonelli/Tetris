
// Tetris.cpp : define los comportamientos de las clases para la aplicaci�n.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"

#include "Square.h"
#include "ColorGrid.h"
#include "Figure.h"

#include "Tetris.h"
#include "MainFrm.h"

#include "TetrisDoc.h"
#include "TetrisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisApp

BEGIN_MESSAGE_MAP(CTetrisApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTetrisApp::OnAppAbout)
	// Comandos de documento est�ndar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Comando de configuraci�n de impresi�n est�ndar
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Construcci�n de CTetrisApp

CTetrisApp::CTetrisApp()
{
	// admite Administrador de reinicio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Si la aplicaci�n se compila para ser compatible con Common Language Runtime (/clr):
	//     1) Esta configuraci�n adicional es necesaria para que la compatibilidad con el Administrador de reinicio funcione correctamente.
	//     2) En el proyecto, debe agregar una referencia a System.Windows.Forms para poder compilarlo.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: reemplace la cadena de identificador de aplicaci�n siguiente por una cadena de identificador �nico; el formato
	// recomendado para la cadena es NombreCompa��a.NombreProducto.Subproducto.Informaci�nDeVersi�n
	SetAppID(_T("Tetris.AppID.NoVersion"));

	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}

// El �nico objeto CTetrisApp

CTetrisApp theApp;


// Inicializaci�n de CTetrisApp

BOOL CTetrisApp::InitInstance()
{
	// Windows XP requiere InitCommonControlsEx() si un manifiesto de
	// aplicaci�n especifica el uso de ComCtl32.dll versi�n 6 o posterior para habilitar
	// estilos visuales.  De lo contrario, se generar� un error al crear ventanas.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Establecer para incluir todas las clases de control comunes que desee utilizar
	// en la aplicaci�n.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Inicializar bibliotecas OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Se necesita AfxInitRichEdit2() para usar el control RichEdit	
	// AfxInitRichEdit2();

	// Inicializaci�n est�ndar
	// Si no utiliza estas funcionalidades y desea reducir el tama�o
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicializaci�n espec�ficas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuraci�n
	// TODO: debe modificar esta cadena para que contenga informaci�n correcta
	// como el nombre de su compa��a u organizaci�n
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI est�ndar (incluidas las de la lista MRU)


	// Registrar las plantillas de documento de la aplicaci�n.  Las plantillas de documento
	//  sirven como conexi�n entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTetrisDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CTetrisView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analizar l�nea de comandos para comandos Shell est�ndar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Habilitar apertura de ejecuci�n DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Enviar comandos especificados en la l�nea de comandos.  Devolver� FALSE si
	// la aplicaci�n se inici� con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//m_pActiveWnd->SetWindowTextW(_T("Tetris"));

	m_pMainWnd->SetWindowPos(NULL, 0, 0, COLS * 2 * g_iColWidth, (ROWS + 3) * g_iRowHeight, SWP_NOMOVE | SWP_NOZORDER);
	// Se ha inicializado la �nica ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOW);

	m_pMainWnd->UpdateWindow();
	// Llamar a DragAcceptFiles s�lo si existe un sufijo
	//  En una aplicaci�n SDI, esto debe ocurrir despu�s de ProcessShellCommand
	// Habilitar apertura de arrastrar y colocar
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

int CTetrisApp::ExitInstance()
{
	//TODO: controlar recursos adicionales que se hayan podido agregar
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Controladores de mensaje de CTetrisApp


// Cuadro de di�logo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de di�logo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementaci�n
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Comando de la aplicaci�n para ejecutar el cuadro de di�logo
void CTetrisApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Controladores de mensaje de CTetrisApp



