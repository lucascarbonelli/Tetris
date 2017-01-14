
// Tetris.cpp : define los comportamientos de las clases para la aplicación.
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
	// Comandos de documento estándar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Comando de configuración de impresión estándar
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Construcción de CTetrisApp

CTetrisApp::CTetrisApp()
{
	// admite Administrador de reinicio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Si la aplicación se compila para ser compatible con Common Language Runtime (/clr):
	//     1) Esta configuración adicional es necesaria para que la compatibilidad con el Administrador de reinicio funcione correctamente.
	//     2) En el proyecto, debe agregar una referencia a System.Windows.Forms para poder compilarlo.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: reemplace la cadena de identificador de aplicación siguiente por una cadena de identificador único; el formato
	// recomendado para la cadena es NombreCompañía.NombreProducto.Subproducto.InformaciónDeVersión
	SetAppID(_T("Tetris.AppID.NoVersion"));

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}

// El único objeto CTetrisApp

CTetrisApp theApp;


// Inicialización de CTetrisApp

BOOL CTetrisApp::InitInstance()
{
	// Windows XP requiere InitCommonControlsEx() si un manifiesto de
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales.  De lo contrario, se generará un error al crear ventanas.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Establecer para incluir todas las clases de control comunes que desee utilizar
	// en la aplicación.
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

	// Inicialización estándar
	// Si no utiliza estas funcionalidades y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que contenga información correcta
	// como el nombre de su compañía u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI estándar (incluidas las de la lista MRU)


	// Registrar las plantillas de documento de la aplicación.  Las plantillas de documento
	//  sirven como conexión entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTetrisDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CTetrisView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Analizar línea de comandos para comandos Shell estándar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Habilitar apertura de ejecución DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Enviar comandos especificados en la línea de comandos.  Devolverá FALSE si
	// la aplicación se inició con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//m_pActiveWnd->SetWindowTextW(_T("Tetris"));

	m_pMainWnd->SetWindowPos(NULL, 0, 0, COLS * 2 * g_iColWidth, (ROWS + 3) * g_iRowHeight, SWP_NOMOVE | SWP_NOZORDER);
	// Se ha inicializado la única ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOW);

	m_pMainWnd->UpdateWindow();
	// Llamar a DragAcceptFiles sólo si existe un sufijo
	//  En una aplicación SDI, esto debe ocurrir después de ProcessShellCommand
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


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
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

// Comando de la aplicación para ejecutar el cuadro de diálogo
void CTetrisApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Controladores de mensaje de CTetrisApp



