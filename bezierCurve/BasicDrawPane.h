#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"

#define BEZIER_NUM_VERTEX  20

class BasicDrawPane : public wxPanel
{
public:
	BasicDrawPane(wxFrame* parent);


	void paintEvent(wxPaintEvent& evt);
	void paintNow();

	void render(wxDC& dc);

	// some useful events
	/*
	 void mouseMoved(wxMouseEvent& event); */
	 void mouseDown(wxMouseEvent& event);
/*	 void mouseWheelMoved(wxMouseEvent& event);
	 void mouseReleased(wxMouseEvent& event);
	 void rightClick(wxMouseEvent& event);
	 void mouseLeftWindow(wxMouseEvent& event);
	 void keyPressed(wxKeyEvent& event);
	 void keyReleased(wxKeyEvent& event);
	 */

	 void toggleViewSupportLines()             { viewSupportLines = !viewSupportLines; }
	 void toggleViewBezierMidPoint()           { viewBezierMidPoint = !viewBezierMidPoint; }

	 void setViewSupportLines(bool newValue)   { viewSupportLines = newValue;  }
	 void setViewBezierMidPoint(bool newValue) { viewBezierMidPoint = newValue; }

private:
	
	wxPoint StartPoint, EndPoint, currentMidPoint;
	wxPoint bezierPoints[BEZIER_NUM_VERTEX];

	bool viewSupportLines = false;
	bool viewBezierMidPoint = true;

	wxPoint getMidPoint(wxPoint start, wxPoint end, float t);

	void  calculateBezierPoints();

	DECLARE_EVENT_TABLE()

};

