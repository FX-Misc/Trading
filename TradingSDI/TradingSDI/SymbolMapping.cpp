
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SymbolMapping.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SymbolMapping::SymbolMapping(CWnd* pParent /*=NULL*/)
	: CDialogEx(SymbolMapping::IDD, pParent),
	m_bShowGripper(true),
      m_szMinimum(0, 0),
      m_hGripper(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void SymbolMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
	//CListCtrl m_list;
	//DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(SymbolMapping, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
		
	ON_BN_CLICKED(IDC_BUTTON1, &SymbolMapping::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &SymbolMapping::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTradingDlg message handlers

BOOL SymbolMapping::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	
// use the initial dialog size as the default minimum
    if ((m_szMinimum.cx == 0) && (m_szMinimum.cy == 0))
    {
        CRect rcWindow;
        GetWindowRect(rcWindow);
        m_szMinimum = rcWindow.Size();
    }

    // keep the initial size of the client area as a baseline for moving/sizing controls
    CRect rcClient;
    GetClientRect(rcClient);
    m_szInitial = rcClient.Size();

    // create a gripper in the bottom-right corner
    if (m_bShowGripper && ((GetStyle() & WS_THICKFRAME) != 0))
    {
        SMovingChild s;
        s.m_rcInitial.SetRect(-GetSystemMetrics(SM_CXVSCROLL), -GetSystemMetrics(SM_CYHSCROLL), 0, 0);
        s.m_rcInitial.OffsetRect(rcClient.BottomRight());
        m_hGripper = CreateWindow(_T("Scrollbar"), _T("size"), WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP,
                                  s.m_rcInitial.left, s.m_rcInitial.top, s.m_rcInitial.Width(), s.m_rcInitial.Height(),
                                  m_hWnd, NULL, AfxGetInstanceHandle(), NULL);
        ASSERT(m_hGripper != NULL);
        if (m_hGripper != NULL)
        {
            s.m_hWnd = m_hGripper;
            s.m_dXMoveFrac = 1.0;
            s.m_dYMoveFrac = 1.0;
            s.m_dXSizeFrac = 0.0;
            s.m_dYSizeFrac = 0.0;
            m_MovingChildren.push_back(s);

            // put the gripper first in the z-order so it paints first and doesn't obscure other controls
            ::SetWindowPos(m_hGripper, HWND_TOP,0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
    }

	
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	
	
	e_grid.AttachGrid(this ,IDC_STATIC);
	e_grid.SetColWidth(0,150);
	e_grid.SetColWidth(1,150);
	e_grid.QuickSetText(0,-1,L"SYMBOL");
	e_grid.QuickSetText(1,-1,L"MAPPING SYMBOL");

	getSymbolData();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void SymbolMapping::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void SymbolMapping::OnBnClickedButton1()
{
		_bstr_t valField1("");
		_bstr_t valField2("");
		_bstr_t cmd("");
		CString  strsqlcommand;				 	
		HRESULT hr = S_OK;		 
		CoInitialize(NULL);
          // Define string variables.		 
		_bstr_t strCnn("Provider=SQLOLEDB;SERVER=68.168.101.187;Database=tradedatabase;uid=sa;pwd=ok@12345;");
		 //_bstr_t strCnn("Provider=SQLOLEDB;SERVER=.;Database=checkdata;uid=sa;pwd=ok;");
        _RecordsetPtr pRstAuthors = NULL;
 
      // Call Create instance to instantiate the Record set
      hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
      if(FAILED(hr))
      {           
      }		
	 
	int noofrows=e_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows-1;f_count++)
	{
		CString strf=L"";
		valField1=e_grid.QuickGetText(0,f_count);
		strf=e_grid.QuickGetText(0,f_count);
		valField2=e_grid.QuickGetText(1,f_count);
		if (strf!=L"")
		{
			cmd=cmd+"insert into symbol_mapping values('" + valField1 + "','" + valField2 + "')";
		}
	}	
	cmd=" delete from symbol_mapping   delete from last_tick  "+cmd;
	pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			

	AfxMessageBox(L"Symbol has been updated");
}


void SymbolMapping::OnBnClickedButton2()
{
		
	CDialog::OnCancel();
}


void SymbolMapping::getSymbolData()
{
	
		
		CString  strsqlcommand;				 	
		HRESULT hr = S_OK;		 
		CoInitialize(NULL);
          // Define string variables.		 
		_bstr_t strCnn("Provider=SQLOLEDB;SERVER=68.168.101.187;Database=tradedatabase;uid=sa;pwd=ok@12345;");
		 //_bstr_t strCnn("Provider=SQLOLEDB;SERVER=.;Database=checkdata;uid=sa;pwd=ok;");
        _RecordsetPtr pRstAuthors = NULL;
 
      // Call Create instance to instantiate the Record set
      hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
      if(FAILED(hr))
      {           
      }
		//_bstr_t strShort(" cast(DT_SetupTime as datetime) desc");
	  _bstr_t valField1("");
	  _bstr_t valField2("");
	 pRstAuthors->Open("select symbol,mapping_symbol from symbol_mapping",strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			
	 int rows_count=0;
	 while(!pRstAuthors->EndOfFile)
	 {
		valField1 = pRstAuthors->Fields->GetItem("symbol")->Value;
		valField2 = pRstAuthors->Fields->GetItem("mapping_symbol")->Value;
		e_grid.QuickSetText(0,rows_count,valField1); 
		e_grid.QuickSetText(1,rows_count,valField2);
		rows_count=rows_count+1;
		pRstAuthors->MoveNext();
	 }
	 pRstAuthors->Close();
}