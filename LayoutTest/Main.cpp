#include "Main.h"



wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyFrame::OnExitMenuItemClick)
	EVT_BUTTON(HIDE_BUTTON_ID, MyFrame::OnHideButtonClick) // Tell the OS to run MainFrame::OnExit when	
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);



bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame("Testing Layout", wxPoint(50, 50), wxSize(SCREEN_WIDTH, SCREEN_HEIGHT));

	frame->Show(true);
	return true;
}





MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	buildMenuBar();




	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
	// create text ctrl with minimal size 100x60
	textfield_sizer = new wxBoxSizer(wxHORIZONTAL);
	textfield_sizer->Add(
		new wxTextCtrl(this, -1, "My text.", wxDefaultPosition, wxSize(100, 60), wxTE_MULTILINE),
		1,            // make vertically stretchable
		wxEXPAND |    // make horizontally stretchable
		wxALL,        //   and make border all around  
		10);         // set border width to 10
	
	

	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
	button_sizer->Add(
		new wxButton(this, wxID_OK, "OK"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);        // set border width to 10
	button_sizer->Add(
		new wxButton(this, wxID_CANCEL, "Cancel"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);        // set border width to 10

	hideButton = new wxButton(this, HIDE_BUTTON_ID, "Hide");


	button_sizer->Add(
		hideButton,
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);        // set border width to 10

	

	/// /////////////////////////////
	//topsizer->Add(
	//		textfield_sizer,
	//		1,                // make vertically unstretchable
	//		wxALIGN_CENTER
	//	); // no border and centre horizontally  

	topsizer->Add(
		textfield_sizer,
		1,            // make vertically stretchable
		wxEXPAND |    // make horizontally stretchable
		wxALL,        //   and make border all around  
		10);         // set border width to 10


 //////////////////////////////////////////////////////


	topsizer->Add(
		button_sizer,
		0,                // make vertically unstretchable
		wxALIGN_CENTER
	); // no border and centre horizontally  
	
	
	SetSizerAndFit(topsizer); // use the sizer for layout and size window
							  // accordingly and prevent it from being resized
							  // to smaller size




	SetStatusText("Change the size of this windows to see!");
}



wxMenuBar* MyFrame::buildMenuBar()
{
	wxMenu* menuFile = new wxMenu;
	wxMenu* menuView = new wxMenu;


	menuFile->Append(wxID_EXIT);


	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuView, "&View");


	SetMenuBar(menuBar);
	CreateStatusBar();

	return menuBar;
}



/************************************************************************
					  Section of the Events Handlers
*************************************************************************/

void MyFrame::OnExitMenuItemClick(wxCommandEvent& event)
{
	Close(true);
}




// Will mask the top section of the screen where the
// Textfiled is located...
void MyFrame::OnHideButtonClick(wxCommandEvent& event)
{
	textfield_sizer->Show(false);
}



