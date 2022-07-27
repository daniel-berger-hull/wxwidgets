#include "Main.h"
#include "Events.h"


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnExitMenuItemClick)
	EVT_MENU(ID_ShowSupportLinesMenuItem, MyFrame::OnViewSupportLinesMenuItemClick) // Tell the OS to run MainFrame::OnExit when
	EVT_MENU(ID_ShowBezierMidPointMenuItem, MyFrame::OnViewBezierMidPointMenuItemClick) // Tell the OS to run MainFrame::OnExit when
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Bezier Curve", wxPoint(50, 50), wxSize(SCREEN_WIDTH, SCREEN_HEIGHT));

    frame->Show(true);
    return true;
}





MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    buildMenuBar();


	BasicDrawPane* drawBox = buildDrawPanel();
	drawBox->SetSize({ 300,200 });



	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(drawBox, 1, wxEXPAND);

	this->SetSizer(sizer);
	this->SetAutoLayout(true);


    SetStatusText("Bezier Curve: Click somewhere on the screen!");
}



wxMenuBar* MyFrame::buildMenuBar()
{
	wxMenu* menuFile = new wxMenu;
	wxMenu* menuView = new wxMenu;


	menuFile->Append(wxID_EXIT);

	viewSupportLinesMenuItem = new wxMenuItem(menuView, ID_ShowSupportLinesMenuItem, "Support &Lines\tCtrl-L", "Will display the 2 supporting lines of the bezier curve", wxITEM_CHECK);
	viewBezierMidPointMenuItem = new wxMenuItem(menuView, ID_ShowBezierMidPointMenuItem, "&Mid Point\tCtrl-M", "Will display the current mid point of the curve", wxITEM_CHECK);
	menuView->Append(viewSupportLinesMenuItem);
	menuView->Append(viewBezierMidPointMenuItem);
		

	viewSupportLinesMenuItem->Check(false);
	viewBezierMidPointMenuItem->Check(true);

	
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuView, "&View");


	SetMenuBar(menuBar);
	CreateStatusBar();

	return menuBar;
}

BasicDrawPane* MyFrame::buildDrawPanel()
{
	drawPane = new BasicDrawPane((wxFrame*)this);

	return drawPane;
}



/************************************************************************
                      Section of the Events Handlers 
*************************************************************************/

void MyFrame::OnExitMenuItemClick(wxCommandEvent& event)
{
    Close(true);
}


void MyFrame::OnViewSupportLinesMenuItemClick(wxCommandEvent& event)
{
	drawPane->toggleViewSupportLines();
	drawPane->Refresh();
}

void MyFrame::OnViewBezierMidPointMenuItemClick(wxCommandEvent& event)
{
	drawPane->toggleViewBezierMidPoint();
	drawPane->Refresh();
}








