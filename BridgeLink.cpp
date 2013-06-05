// BridgeLink.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <initguid.h>

#include "BridgeLink.h"
#include "AboutDlg.h"

#include "BridgeLinkCATID.h"

#include "BridgeLinkCommandIDs.h"
#include "ScreenSizeDlg.h"
#include "MainFrm.h"


// This is the range of command IDs for all plug-in commands... all means all commands added
// to the menus of the BridgeLink executable program, the AppPlugin document and view menus, 
// and plugin supplied menus, toolbars, and accelerator tables
#define BRIDGELINK_FIRST_PLUGIN_COMMAND 0x8200
#define BRIDGELINK_LAST_PLUGIN_COMMAND  (BRIDGELINK_FIRST_PLUGIN_COMMAND+0x0100)
#define BRIDGELINK_PLUGIN_COMMAND_COUNT (BRIDGELINK_LAST_PLUGIN_COMMAND-BRIDGELINK_FIRST_PLUGIN_COMMAND)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp

BEGIN_MESSAGE_MAP(CBridgeLinkApp, CEAFPluginApp)
	//{{AFX_MSG_MAP(CBridgeLinkApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_JOINARPLIST, OnHelpJoinArpList)
	ON_COMMAND(ID_HELP_INET_WSDOT, OnHelpInetWsdot)
	ON_COMMAND(ID_HELP_INET_BRIDGELINK, OnHelpInetBridgeLink)
   ON_COMMAND(ID_HELP_INET_ARP, OnHelpInetARP)
   ON_COMMAND(ID_SCREEN_SIZE,OnScreenSize)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp construction

CBridgeLinkApp::CBridgeLinkApp()
{
   SetHelpMode(afxHTMLHelp);
}

CBridgeLinkApp::~CBridgeLinkApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBridgeLinkApp object

CBridgeLinkApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp initialization
CString CBridgeLinkApp::GetProductCode()
{
#pragma Reminder("UPDATE") // see CPGSuperApp for what goes here
   return "Unknown";
}

LPCTSTR CBridgeLinkApp::GetRegistryKey()
{
   return _T("Washington State Department of Transportation");
}

OLECHAR* CBridgeLinkApp::GetAppPluginCategoryName()
{
   return _T("BridgeLink Application Plugin");
}

CATID CBridgeLinkApp::GetAppPluginCategoryID()
{
   return CATID_BridgeLinkAppPlugin;
}

CEAFSplashScreenInfo CBridgeLinkApp::GetSplashScreenInfo()
{
   CBitmap bmp;
   CEAFSplashScreenInfo info;

   info.m_bShow = GetCommandLineInfo().m_bShowSplash;

   VERIFY(bmp.LoadBitmap(IDB_SPLASH));
   info.m_hBitmap = bmp;
   info.m_TransparencyColor = RGB(255,0,0);
   info.m_TextColor = RGB(0,0,0); // color of the information text drawn onto the splash screen
   info.m_BgColor = RGB(255,255,255); // text background color
   info.m_Rect = CRect(5,300,515,315); // rectangle on the splash screen bitmap where text is written

   bmp.Detach();

   return info;
}

CMDIFrameWnd* CBridgeLinkApp::CreateMainFrame()
{
   // don't call base class, the functionality is being replaced
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
   {
      delete pMainFrame;
		return NULL;
   }

   // files can be opened with drag and drop
   pMainFrame->DragAcceptFiles(TRUE);

   return pMainFrame;
}

CATID CBridgeLinkApp::GetComponentInfoCategoryID()
{
   return CATID_BridgeLinkComponents;
}


BOOL CBridgeLinkApp::InitInstance()
{
   // Initialize OLE libraries
	if (!SUCCEEDED(OleInitialize(NULL)))
	{
		AfxMessageBox(_T("OLE initialization failed. Make sure that the OLE libraries are the correct version."));
		return FALSE;
	}

   sysComCatMgr::CreateCategory(_T("BridgeLink Components"),CATID_BridgeLinkComponents);
   sysComCatMgr::CreateCategory(_T("BridgeLink Application Plugin"),CATID_BridgeLinkAppPlugin);

//   CREATE_LOGFILE("BridgeLinkApp"); 

   // Tip of the Day
   CString strTipFile = GetAppLocation() + CString(_T("BridgeLink.tip"));
#if defined _DEBUG
   strTipFile.Replace(_T("RegFreeCOM\\Debug\\"),_T(""));
#else
   // in a real release, the path doesn't contain RegFreeCOM\\Release, but that's
   // ok... the replace will fail and the string wont be altered.
   strTipFile.Replace(_T("RegFreeCOM\\Release\\"),_T(""));
#endif
   EnableTipOfTheDay(strTipFile); // must be enabled before InitInstance

   // Do this before InitInstance on base class
   
   // Reserve the total range of command IDs that can be used for ALL BridgeLink App Plugins.
   // ALL means all commands added to the menus of the main executable, the 
   // EAFAppPlugin document and view menus, and plugin supplied menus,
   // toolbars, and accelerator tables
   CEAFPluginCommandManager::ReserveTotalCommandIDRange(BRIDGELINK_FIRST_PLUGIN_COMMAND,BRIDGELINK_LAST_PLUGIN_COMMAND);

   // Reserve BRIDGELINK_PLUGIN_COMMAND_COUNT command IDs for commands that get added
   // to the main application
   GetPluginCommandManager()->ReserveCommandIDRange(BRIDGELINK_PLUGIN_COMMAND_COUNT);

   // user can dbl-click on a file to open
   EnableShellOpen();

   // Help file defaults to the location of the application
   // In our development environment, it is in the \ARP\BridgeLink folder
   //
   // Change help file name
   CString strHelpFile(m_pszHelpFilePath);
#if defined _DEBUG
#if defined _WIN64
   strHelpFile.Replace(_T("RegFreeCOM\\x64\\Debug\\"),_T(""));
#else
   strHelpFile.Replace(_T("RegFreeCOM\\Win32\\Debug\\"),_T(""));
#endif
#else
   // in a real release, the path doesn't contain RegFreeCOM\\Release, but that's
   // ok... the replace will fail and the string wont be altered.
#if defined _WIN64
   strHelpFile.Replace(_T("RegFreeCOM\\x64\\Release\\"),_T(""));
#else
   strHelpFile.Replace(_T("RegFreeCOM\\Win32\\Release\\"),_T(""));
#endif
#endif
   free((void*)m_pszHelpFilePath);
   m_pszHelpFilePath = _tcsdup(strHelpFile);

   if ( !CEAFPluginApp::InitInstance() )
      return FALSE;

	return TRUE;
}

int CBridgeLinkApp::ExitInstance() 
{
//   CLOSE_LOGFILE;

   ::OleUninitialize();

   return CEAFApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp message handlers

/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp commands

CString CBridgeLinkApp::GetVersion(bool bIncludeBuildNumber) const
{
   CString strExe( m_pszExeName );
   strExe += _T(".exe");

   CVersionInfo verInfo;
   verInfo.Load(strExe);
   
   CString strVersion = verInfo.GetProductVersionAsString();

#if defined _DEBUG || defined _BETA_VERSION
   // always include the build number in debug and beta versions
   bIncludeBuildNumber = true;
#endif

   if (!bIncludeBuildNumber)
   {
      // remove the build number
      int pos = strVersion.ReverseFind(_T('.')); // find the last '.'
      strVersion = strVersion.Left(pos);
   }

   return strVersion;
}

CString CBridgeLinkApp::GetVersionString(bool bIncludeBuildNumber) const
{
   CString str(_T("Version "));
   str += GetVersion(bIncludeBuildNumber);
#if defined _BETA_VERSION
   str += CString(_T(" BETA"));
#endif

   str += CString(_T(" - Built on "));
   str += CString(__DATE__);
   return str;
}

void CBridgeLinkApp::RegistryInit()
{
   // Application wide settings go under BridgeLink
   // Each application plug in will create it's own hive in the registry
   // We need to tweek the name here because this is actually the BridgeLink.exe
   free((void*)m_pszProfileName);
   m_pszProfileName = _tcsdup(_T("BridgeLink"));

   CEAFPluginApp::RegistryInit();
}

void CBridgeLinkApp::RegistryExit()
{
   CEAFPluginApp::RegistryExit();
}

void CBridgeLinkApp::OnScreenSize()
{
   CEAFMainFrame* pFrame = EAFGetMainFrame();
   CScreenSizeDlg dlg;
   CRect rClient;
   pFrame->GetWindowRect(&rClient);
   dlg.m_Height = rClient.Height();
   dlg.m_Width  = rClient.Width();

   if ( dlg.DoModal() == IDOK )
   {
      int cx = dlg.m_Width;
      int cy = dlg.m_Height;
      pFrame->SetWindowPos(NULL,0,0,cx,cy,SWP_NOMOVE | SWP_NOZORDER);
   }
}

CString CBridgeLinkApp::GetWsdotUrl()
{
//   CString url = GetProfileString(_T("Settings"), _T("WsdotUrl"), _T("http://www.wsdot.wa.gov"));

   CString strDefault(_T("http://www.wsdot.wa.gov"));

   HKEY key;
   LONG result = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Washington State Department of Transportation\\BridgeLink\\Settings"),0,KEY_QUERY_VALUE,&key);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   TCHAR url[MAX_PATH];
   DWORD size = MAX_PATH;
   DWORD type;
   result = ::RegQueryValueEx(key,_T("WsdotUrl"),0,&type,(LPBYTE)&url[0],&size);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   ::RegCloseKey(key);

   return url;
}

CString CBridgeLinkApp::GetWsdotBridgeUrl()
{
//   CString url = GetProfileString(_T("Settings"), _T("WsdotBridgeUrl"), _T("http://www.wsdot.wa.gov/eesc/bridge"));

   CString strDefault(_T("http://www.wsdot.wa.gov/eesc/bridge"));

   HKEY key;
   LONG result = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Washington State Department of Transportation\\BridgeLink\\Settings"),0,KEY_QUERY_VALUE,&key);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   TCHAR url[MAX_PATH];
   DWORD size = MAX_PATH;
   DWORD type;
   result = ::RegQueryValueEx(key,_T("WsdotBridgeUrl"),0,&type,(LPBYTE)&url[0],&size);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   ::RegCloseKey(key);

   return url;
}

CString CBridgeLinkApp::GetBridgeLinkUrl()
{
   // NOTE: If URL isn't found in the registry, just go to the main software page.
//   CString url = GetProfileString(_T("Settings"), _T("BridgeLinkUrl"), _T("http://www.wsdot.wa.gov/eesc/bridge"));
#pragma Reminder("UPDATE: make this link go to the BridgeLink page")
   CString strDefault(_T("http://www.wsdot.wa.gov/eesc/bridge/software/index.cfm?fuseaction=software_detail&software_id=47"));

   HKEY key;
   LONG result = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Washington State Department of Transportation\\BridgeLink\\Settings"),0,KEY_QUERY_VALUE,&key);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   TCHAR url[MAX_PATH];
   DWORD size = MAX_PATH;
   DWORD type;
   result = ::RegQueryValueEx(key,_T("BridgeLinkUrl"),0,&type,(LPBYTE)&url[0],&size);
   if ( result != ERROR_SUCCESS )
      return strDefault;

   ::RegCloseKey(key);

   return url;
}

void CBridgeLinkApp::OnHelpInetWsdot() 
{
   HINSTANCE hInstance = ::ShellExecute(m_pMainWnd->GetSafeHwnd(),
                                        _T("open"),
                                        GetWsdotUrl(),
                                         0,0,SW_SHOWDEFAULT);

   if ( (INT)hInstance < 32 )
   {
      AfxMessageBox(IDS_E_ONLINERESOURCES);
   }
}

void CBridgeLinkApp::OnHelpJoinArpList()
{
   HINSTANCE hInstance = ::ShellExecute(m_pMainWnd->GetSafeHwnd(),
                                        _T("open"),
										_T("http://www.pgsuper.com/drupal/forum"),
                                         0,0,SW_SHOWDEFAULT);

   if ( (INT)hInstance < 32 )
   {
      AfxMessageBox(IDS_E_ONLINERESOURCES);
   }
}

void CBridgeLinkApp::OnHelpInetARP()
{
   HINSTANCE hInstance = ::ShellExecute(m_pMainWnd->GetSafeHwnd(),
                                        _T("open"),
                                        _T("http://wsdot.wa.gov/eesc/bridge/alternateroute"),
                                         0,0,SW_SHOWDEFAULT);

   if ( (INT)hInstance < 32 )
   {
      AfxMessageBox(IDS_E_ONLINERESOURCES);
   }
}

void CBridgeLinkApp::OnHelpInetBridgeLink() 
{
   HINSTANCE hInstance = ::ShellExecute(m_pMainWnd->GetSafeHwnd(),
                                        _T("open"),
                                        GetBridgeLinkUrl(),
                                        0,0,SW_SHOWDEFAULT);

   if ( (INT)hInstance < 32 )
   {
      AfxMessageBox(IDS_E_ONLINERESOURCES);
   }
}

// App command to run the dialog
void CBridgeLinkApp::OnAppAbout()
{
   CAboutDlg dlg;
   dlg.DoModal();
}

BOOL CBridgeLinkApp::OnCmdMsg(UINT nID,int nCode,void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
   // For some reason, this method is needed otherwise the base class version
   // doesn't get called... even though the base class method is virtual
   return CEAFPluginApp::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}
