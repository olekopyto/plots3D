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

	double minZ;
	double maxZ;

public:
	void getZ(double min, double max);

	double shepard(double x, double y);
	void repaint(wxPanel* drawingPanel, int w, int h);
	void prepareData(int num);
};

#endif