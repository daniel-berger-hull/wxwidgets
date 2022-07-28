#pragma once
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/sizer.h>

#include <wx/textctrl.h>
#include <wx/button.h>


#define SCREEN_WIDTH   400
#define SCREEN_HEIGHT  400

#define HIDE_BUTTON_ID	50


class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};



class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);


	wxBoxSizer* textfield_sizer;
	wxButton* hideButton;



private:

	wxMenuBar* buildMenuBar();

	void OnExitMenuItemClick(wxCommandEvent& event);
	void OnHideButtonClick(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

