///////////////////////////////////////////////////////////////////////
// BridgeLink - BridgeLink Extensible Application Framework
// Copyright � 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// BridgeLink.h : main header file for the BRIDGELINK application
//

#if !defined(AFX_BRIDGELINK_H__0553A0AE_B8F3_454D_9146_0B973C138288__INCLUDED_)
#define AFX_BRIDGELINK_H__0553A0AE_B8F3_454D_9146_0B973C138288__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <EAF\EAFApp.h>
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBridgeLinkApp:
// See BridgeLink.cpp for the implementation of this class
//

class CBridgeLinkApp : public CEAFPluginApp
{
public:
	CBridgeLinkApp();
   ~CBridgeLinkApp();

// CEAFPluginApp overrides
public:
   virtual OLECHAR* GetAppPluginCategoryName();
   virtual CATID GetAppPluginCategoryID();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBridgeLinkApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBridgeLinkApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpJoinArpList();
	afx_msg void OnHelpInetWsdot();
	afx_msg void OnHelpInetBridgeLink();
   afx_msg void OnHelpInetARP();
   afx_msg void OnScreenSize();
	//}}AFX_MSG
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	DECLARE_MESSAGE_MAP()

protected:
   virtual CEAFSplashScreenInfo GetSplashScreenInfo();
   virtual LPCTSTR GetRegistryKey();
   virtual CMDIFrameWnd* CreateMainFrame();
   virtual CATID GetComponentInfoCategoryID();
   virtual CString GetProductCode();


public:
   CString GetVersion(bool bIncludeBuildNumber) const;
   CString GetVersionString(bool bIncludeBuildNumber) const;

   // URL's
   CString GetWsdotUrl();
   CString GetWsdotBridgeUrl();
   CString GetBridgeLinkUrl();

private:
   virtual void RegistryInit(); // All registry initialization goes here
   virtual void RegistryExit(); // All registry cleanup goes here
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRIDGELINK_H__0553A0AE_B8F3_454D_9146_0B973C138288__INCLUDED_)