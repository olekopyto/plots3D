#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"
#include "MyPrinter.h"
#include "perspectivic.h"
#include "map.h"
#include "tinyexpr.h"

//// end generated include

#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/colourdata.h>
#include <wx/print.h>
#include <wx/printdlg.h>

#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
private:
	string function = "x^2 + y^2";
	double xMin = -10;
	double xMax = 10;
	double yMin = -10;
	double yMax = 10;
	double zMin = -10;
	double zMax = 10;
	bool inPerspective = true;
	bool inMap = false;

	int panelWidth;
	int panelHeight;

	bool generateClicked = false;

	vector<vector<double>> zValuesVec;

	Perspectivic objPer;
	Map objMap;

public:
	// Handlers for MyFrame1 events;
	void showInfo(wxMouseEvent& event);
	void perspectiveClick(wxMouseEvent& event);
	void outlineClick(wxMouseEvent& event);
	void printClick(wxMouseEvent& event);
	void saveClick(wxMouseEvent& event);
	void generateClick(wxMouseEvent& event);

	void panelRepaint(wxSizeEvent& event);

	string getFunction() const { return function; }
	bool checkFunction();

	double getxMin() const { return xMin; }
	double getxMax() const { return xMax; }
	double getyMin() const { return yMin; }
	double getyMax() const { return yMax; }
	double getzMin() const { return zMin; }
	double getzMax() const { return zMax; }
	bool checkNumbers();

	bool isPerspective() const { return inPerspective; }
	bool isMap() const { return inMap; }

	void repaint();

public:
	/** Constructor */
	GUIMyFrame1(wxWindow* parent);
	//// end generated class members
	
};

#endif // __GUIMyFrame1__