#pragma once
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/menu.h>
#include <wx/textctrl.h>

#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/button.h>

#include "BasicDrawPane.h"


#define SCREEN_WIDTH   400
#define SCREEN_HEIGHT  400


/*
    This is a basic example using wxWidgets to calculate and display a Bezier curve
*/



class MyApp : public wxApp
{
	public:
		virtual bool OnInit();

};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    

	BasicDrawPane* drawPane = NULL;
	wxMenuItem* viewSupportLinesMenuItem;
	wxMenuItem* viewBezierMidPointMenuItem;

	
	  
private:

    wxMenuBar*       buildMenuBar();
	BasicDrawPane*   buildDrawPanel();

	void OnViewSupportLinesMenuItemClick(wxCommandEvent& event);
	void OnViewBezierMidPointMenuItemClick(wxCommandEvent& event);
	void OnExitMenuItemClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};




