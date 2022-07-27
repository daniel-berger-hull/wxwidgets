#include "BasicDrawPane.h"


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

 // catch paint events
	EVT_PAINT(BasicDrawPane::paintEvent)
	EVT_LEFT_DOWN(BasicDrawPane::mouseDown)

	END_EVENT_TABLE()


	// some useful events
	/*
	 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
	 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
	 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
	 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
	 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
	 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
	 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
	 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
	 */

	BasicDrawPane::BasicDrawPane(wxFrame* parent) :
	wxPanel(parent)
{
	StartPoint = wxPoint(50,175);
	currentMidPoint = wxPoint(200,25);
	EndPoint = wxPoint(350,175);

	calculateBezierPoints();
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC& dc)
{


	wxPoint midOne, midTwo;

	// draw some text
	//dc.DrawText(wxT("Testing"), 40, 60);

	if (viewSupportLines)
	{
		// Draw the 2 supporting lines (AB & BC)
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1)); // black line, 1 pixels thick
		dc.DrawLine(StartPoint.x, StartPoint.y, currentMidPoint.x, currentMidPoint.y);
		dc.DrawLine(currentMidPoint.x, currentMidPoint.y, EndPoint.x, EndPoint.y);
	}
	

	for (int i = 0; i < BEZIER_NUM_VERTEX; i++)
	{
		dc.DrawCircle(bezierPoints[i], 2 /* radius */);
	}



	if (viewBezierMidPoint)
	{
		dc.SetPen(wxPen(wxColor(255, 0, 0), 3)); // 5-pixels-thick red outline
		dc.SetBrush(*wxRED_BRUSH); // blue filling); // blue filling
		dc.DrawCircle(currentMidPoint, 3 /* radius */);
	}

	dc.SetPen(wxPen(wxColor(0, 255, 0), 2)); // 5-pixels-thick red outline
	dc.SetBrush(*wxGREEN_BRUSH); // blue filling); // blue filling
	dc.DrawCircle(StartPoint, 3 /* radius */);
	dc.DrawCircle(EndPoint, 3 /* radius */);

}



void BasicDrawPane::mouseDown(wxMouseEvent& event) 
{
	currentMidPoint = { event.GetX() , event.GetY() };
	calculateBezierPoints();
	Refresh();
}

wxPoint BasicDrawPane::getMidPoint(wxPoint start, wxPoint end, float t)
{
	float Xpos, Ypos;

	Xpos = (float)start.x * (1.0f - t);
	Ypos = (float)start.y * (1.0f - t);
	wxPoint APrime = { (int)Xpos ,(int)Ypos };

	Xpos = (float)end.x * t;
	Ypos = (float)end.y * t;
	wxPoint BPrime = { (int)Xpos ,(int)Ypos };

	return  APrime + BPrime;
}


void  BasicDrawPane::calculateBezierPoints()
{
	float currentT = 0.0f;
	float deltaT = 1.0f / BEZIER_NUM_VERTEX;

	bezierPoints[0] = StartPoint;

	for (int i = 1; i < BEZIER_NUM_VERTEX; i++)
	{
		// Get and highligh the mid points on both starting lines...
		wxPoint midPointOne = getMidPoint(StartPoint, currentMidPoint, currentT);
 		wxPoint midPointTwo = getMidPoint(currentMidPoint, EndPoint, currentT);
		// And find the Bezier point between the line between the midPoints...
		wxPoint bezierPoint = getMidPoint(midPointOne, midPointTwo, currentT);

		bezierPoints[i] = bezierPoint;
		currentT += deltaT;
	}

}




