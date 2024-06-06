#include "map.h"
#include < time.h>

void Map::getRanges(double xmi, double xma, double ymi, double yma, double zmi, double zma)
{
	xmin = xmi;
	xmax = xma;
	ymin = ymi;
	ymax = yma;
	zmin = zmi;
	zmax = zma;
}

double Map::shepard(double x, double y)
{
	double sumUpper = 0, sumLower = 0, wk = 0, xk, yk;
	for (int i = 0; i < numberOfPoints; i++) {
		xk = functionPoints[i][0];
		yk = functionPoints[i][1];
		wk = 1.0 / abs((x - xk) * (x - xk) + (y - yk) * (y - yk));
		sumUpper += wk * functionPoints[i][2];
		sumLower += wk;
	}
	return sumUpper / sumLower;
}

void Map::repaint(wxPanel* drawingPanel, int w, int h)
{
	wxClientDC DC(drawingPanel);
	wxBufferedDC BufferedDC(&DC);
	int width = w;
	int height = h;
	BufferedDC.SetBackground(wxBrush(wxColour("white")));
	BufferedDC.Clear();

	for (int i = 0; i < 100; i++) {
		vector<double> v = { 0., 0., 0. };
		functionPoints.push_back(v);
	}

	prepareData(1);

	BufferedDC.SetPen(*wxBLACK_PEN);
	BufferedDC.SetBrush(*wxTRANSPARENT_BRUSH);

	vector<vector<double>> values;

	for (int i = 0; i < width; i++) {
		vector<double> v;
		for (int j = 0; j < height; j++) v.push_back(0.);
		values.push_back(v);
	}


	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			values[x][y] = shepard(x / 100.0 - 2.5, -y / 100.0 + 2.5);

	double min = functionPoints[0][2], max = functionPoints[0][2];
	for (int i = 0; i < numberOfPoints; i++) {
		if (functionPoints[i][2] < min)
			min = functionPoints[i][2];
		if (functionPoints[i][2] > max)
			max = functionPoints[i][2];
	}

	//tu mozna dodac shepard tylko bez skalowania wtedy!!!

	std::vector<std::array<wxPoint, 2>> contours;
	for (int i = 1; i <= 9; i++) {
		double threshold = min + i * (max - min) / (double)(9 + 1);
		for (int x = 1; x < width - 1; x++) {
			for (int y = 1; y < height - 1; y++) {
				int code = (values[x - 1][y + 1] > threshold ? 1 : 0) +
					(values[x + 1][y + 1] > threshold ? 1 : 0) * 2 +
					(values[x + 1][y - 1] > threshold ? 1 : 0) * 4 +
					(values[x - 1][y - 1] > threshold ? 1 : 0) * 8;

				if (values[x][y] < threshold) {
					if (code == 5) code = 10;
					if (code == 10) code = 5;
				}

				switch (code) {
				case 1:
				case 14:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x - 1, y), wxPoint(x, y + 1) });
					break;
				case 2:
				case 13:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x + 1, y), wxPoint(x, y + 1) });
					break;
				case 3:
				case 12:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x - 1, y), wxPoint(x + 1, y) });
					break;
				case 4:
				case 11:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x, y - 1), wxPoint(x + 1, y) });
					break;
				case 5:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x + 1, y), wxPoint(x, y + 1) });
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x - 1, y), wxPoint(x, y - 1) });
					break;
				case 10:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x - 1, y), wxPoint(x, y + 1) });
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x + 1, y), wxPoint(x, y - 1) });
					break;
				case 6:
				case 9:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x, y - 1), wxPoint(x, y + 1) });
					break;
				case 7:
				case 8:
					contours.push_back(std::array<wxPoint, 2> { wxPoint(x - 1, y), wxPoint(x, y - 1) });
					break;
				}
			}
		}
		for (auto& item : contours)
			BufferedDC.DrawLine(item[0], item[1]);
	}
}
/////////// temp fun
double Map::countFunction(double x, double y) {
	return sin(x) + x + y;
}

////


void Map::prepareData(int num)
{
	//srand(time(NULL));
	int i=0;
	double x, y;
	///// temp
	int sample = 10;
	double move = std::max(((xmax - xmin) / sample), (ymax - ymin) / sample);
	double movex = std::min((xmax - xmin), move);
	double movey = std::min((ymax - ymin), move);
	/////

	numberOfPoints = 100;

	//temp fun

	for (double x = xmin; x < (xmax); x += movex) {

		for (double y = ymin; y < (ymax); y += movey) {

			functionPoints[i][0] = x;
			functionPoints[i][1] = y;
			functionPoints[i][2] = std::min(std::max(countFunction(x, y), zmin), zmax);
			i++;
		}
	}

	////////////

}
