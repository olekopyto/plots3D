#ifndef __MAP__
#define __MAP__

#include "GUI.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <array>


using namespace std;

class Map {
private:
	int numberOfPoints;
	vector<vector<double>> functionPoints;

	double countFunction(double x, double y);
	
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double zmin;
	double zmax;

public:
	void getRanges(double xmi, double xma, double ymi, double yma, double zmi, double zma);

	double shepard(double x, double y);
	void repaint(wxPanel* drawingPanel, int w, int h);
	void prepareData(int num);
};

#endif