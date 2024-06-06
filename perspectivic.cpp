#include "perspectivic.h"

void Perspectivic::getAxis(double xmi, double xma, double ymi, double yma, double zmi, double zma) {
	xmin = xmi; xmax = xma; ymin = ymi; ymax = yma; zmin = zmi; zmax = zma;
}

double Perspectivic::countFunction(double x, double y) {
	return sin(x) + x + y;
}

void Perspectivic::RecountFunctionIntoData(vector<vector<double>> funValues) {

	data.clear();
	int sample = 50;

	scale = 2. / std::max(xmax - xmin, std::max(ymax - ymin, zmax - zmin)) / 2;

	double move = std::max(((xmax - xmin) / sample), (ymax - ymin) / sample);
	double movex = std::min((xmax - xmin), move);
	double movey = std::min((ymax - ymin), move);

	for (double x = xmin; x <= (xmax); x += movex) {

		for (double y = ymin; y <= (ymax); y += movey) {

			double z = countFunction(x, y);
			double z1 = countFunction(x, y + movey);
			double z2 = countFunction(x + movex, y);

			Color c1(255, 0, 255);
			Color c2(255, 0, 255);

			if (z > zmax && z1 > zmax) {

				c1 = Color(255, 255, 255);
			}

			/*if (z >= zmax && z1 <= zmax) {

				c1 = Color(255, 255, 255);
			}

			if (z <= zmax && z1 >= zmax) {

				c1 = Color(255, 255, 255);
			}*/

			if (z > zmax && z2 > zmax) {

				c2 = Color(255, 255, 255);
			}

			/*if (z >= zmax && z2 <= zmax) {

				c2 = Color(255, 255, 255);
			}

			if (z <= zmax && z2 >= zmax) {

				c2 = Color(255, 255, 255);
			}*/

			if (z > zmax) {

				z = zmax;
			}

			if (z1 > zmax) {

				z1 = zmax;
			}

			if (z2 > zmax) {

				z2 = zmax;
			}

			if (z < zmin && z1 < zmin) {

				c1 = Color(255, 255, 255);
			}

			if (z < zmin && z1 < zmin) {

				c2 = Color(255, 255, 255);
			}

			if (z < zmin) {

				z = zmin;
			}

			if (z1 < zmin) {

				z1 = zmin;
			}

			if (z2 < zmin) {

				z2 = zmin;
			}

			/*if (z < zmin) {

				z = zmin;
				c1 = c2 = Color(255, 255, 255);
			}

			if (z1 > zmax) {

				z1 = zmax;
				c1 = Color(255, 255, 255);
			}

			if (z1 < zmin) {

				z1 = zmin;
				c1 = Color(255, 255, 255);
			}

			if (z2 > zmax) {

				z2 = zmax;
				c2 = Color(255, 255, 255);
			}

			if (z2 < zmin) {

				z2 = zmin;
				c2 = Color(255, 255, 255);
			}*/

			data.push_back(Segment(Point(x, y, z), Point(x, y + movey, z1), c1));
			data.push_back(Segment(Point(x, y, z), Point(x + movex, y, z2), c2));
		}
		double z = countFunction(x, ymax);
		double z3 = countFunction(x + movex, ymax);

		Color c3(255, 0, 255);

		if (z > zmax && z3 > zmax) {

			c3 = Color(255, 255, 255);
		}

		/*if (z >= zmax && z3 <= zmax) {

			c3 = Color(255, 255, 255);
		}

		if (z <= zmax && z3 >= zmax) {

			c3 = Color(255, 255, 255);
		}*/

		if (z > zmax) {

			z = zmax;
		}

		if (z3 > zmax) {

			z3 = zmax;
		}

		if (z < zmin && z3 < zmin) {

			c3 = Color(255, 255, 255);
		}

		if (z < zmin) {

			z = zmin;
		}

		if (z3 < zmin) {

			z3 = zmin;
		}

		/*if (z > zmax) {

			z = zmax;
			c3 = Color(255, 255, 255);
		}

		if (z < zmin) {

			z = zmin;
			c3 = Color(255, 255, 255);
		}

		if (z3 > zmax) {

			z3 = zmax;
			c3 = Color(255, 255, 255);
		}

		if (z3 < zmin) {

			z3 = zmin;
			c3 = Color(255, 255, 255);
		}*/

		data.push_back(Segment(Point(x, ymax, z), Point(x + movex, ymax, z3), c3));
	}

	for (double y = ymin; y <= ymax; y += movey) {

		double z = countFunction(xmax, y);
		double z3 = countFunction(xmax, y + movey);
		Color c3(255, 0, 255);

		if (z > zmax && z3 > zmax) {

			c3 = Color(255, 255, 255);
		}

		if (z > zmax) {

			z = zmax;
		}

		if (z3 > zmax) {

			z3 = zmax;
		}

		if (z < zmin && z3 < zmin) {

			c3 = Color(255, 255, 255);
		}

		/*if (z >= zmax && z3 <= zmax) {

			c3 = Color(255, 255, 255);
		}

		if (z <= zmax && z3 >= zmax) {

			c3 = Color(255, 255, 255);
		}*/


		if (z < zmin) {

			z = zmin;
		}

		if (z3 < zmin) {

			z3 = zmin;
		}

		/*if (z > zmax) {

			z = zmax;
			c3 = Color(255, 255, 255);
		}

		if (z < zmin) {

			z = zmin;
			c3 = Color(255, 255, 255);
		}

		if (z3 > zmax) {

			z3 = zmax;
			c3 = Color(255, 255, 255);
		}

		if (z3 < zmin) {

			z3 = zmin;
			c3 = Color(255, 255, 255);
		}*/

		data.push_back(Segment(Point(xmax, y, z), Point(xmax, y + movey, z3), c3));
	}

	double grid = std::max(xmax - xmin, std::max(ymax - ymin, zmax - zmin)) / 20;

	//  AXIS draw

	data.push_back(Segment(Point(xmin, (ymax + ymin) / 2, (zmax + zmin) / 2), Point(xmax, (ymax + ymin) / 2, (zmax + zmin) / 2), Color(255, 0, 0)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(xmax - grid / 2, grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point(xmax, (ymax + ymin) / 2, (zmax + zmin) / 2), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, -grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, -grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point(xmax, (ymax + ymin) / 2, (zmax + zmin) / 2), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, -grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point(xmax, (ymax + ymin) / 2, (zmax + zmin) / 2), Color(255, 0, 0)));
		data.push_back(Segment(Point(xmax - grid / 2, -grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point(xmax, (ymax + ymin) / 2, (zmax + zmin) / 2), Color(255, 0, 0)));
	}

	data.push_back(Segment(Point((xmax + xmin) / 2, ymin, (zmax + zmin) / 2), Point((xmax + xmin) / 2, ymax, (zmax + zmin) / 2), Color(0, 255, 0)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(grid / 16 * sqrt(1 - pow(sin(i), 2)) + (xmax + xmin) / 2, ymax - grid / 2, grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point((xmax + xmin) / 2, ymax, (zmax + zmin) / 2), Color(0, 255, 0)));
		data.push_back(Segment(Point(-grid / 16 * sqrt(1 - pow(sin(i), 2)) + (xmax + xmin) / 2, ymax - grid / 2, grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point((xmax + xmin) / 2, ymax, (zmax + zmin) / 2), Color(0, 255, 0)));
		data.push_back(Segment(Point(-grid / 16 * sqrt(1 - pow(sin(i), 2)) + (xmax + xmin) / 2, ymax - grid / 2, -grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point((xmax + xmin) / 2, ymax, (zmax + zmin) / 2), Color(0, 255, 0)));
		data.push_back(Segment(Point(grid / 16 * sqrt(1 - pow(sin(i), 2)) + (xmax + xmin) / 2, ymax - grid / 2, -grid / 16 * sqrt(1 - pow(cos(i), 2)) + (zmax + zmin) / 2), Point((xmax + xmin) / 2, ymax, (zmax + zmin) / 2), Color(0, 255, 0)));
	}

	data.push_back(Segment(Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmin), Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmax), Color(0, 0, 255)));
	for (double i = 0; i < M_PI / 2; i += 0.3) {
		data.push_back(Segment(Point(grid / 16 * sqrt(1 - pow(cos(i), 2)) + (xmax + xmin) / 2, grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, zmax - grid / 2), Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmax), Color(0, 0, 255)));
		data.push_back(Segment(Point(-grid / 16 * sqrt(1 - pow(cos(i), 2)) + (xmax + xmin) / 2, grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, zmax - grid / 2), Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmax), Color(0, 0, 255)));
		data.push_back(Segment(Point(-grid / 16 * sqrt(1 - pow(cos(i), 2)) + (xmax + xmin) / 2, -grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, zmax - grid / 2), Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmax), Color(0, 0, 255)));
		data.push_back(Segment(Point(grid / 16 * sqrt(1 - pow(cos(i), 2)) + (xmax + xmin) / 2, -grid / 16 * sqrt(1 - pow(sin(i), 2)) + (ymax + ymin) / 2, zmax - grid / 2), Point((xmax + xmin) / 2, (ymax + ymin) / 2, zmax), Color(0, 0, 255)));
	}
}

Matrix4 Perspectivic::XRotation(double alpha) {

	Matrix4 matrix;
	alpha = ((alpha + 252) * M_PI) / 180.0;

	matrix.data[0][0] = 1;
	matrix.data[1][1] = cos(alpha);
	matrix.data[1][2] = -sin(alpha);
	matrix.data[2][1] = sin(alpha);
	matrix.data[2][2] = cos(alpha);
	matrix.data[3][3] = 1.0;

	return matrix;
}

Matrix4 Perspectivic::YRotation(double alpha) {

	Matrix4 matrix;
	alpha = (alpha * M_PI) / 180.0;

	matrix.data[0][0] = cos(alpha);
	matrix.data[0][2] = -sin(alpha);
	matrix.data[1][1] = 1.0;
	matrix.data[2][0] = sin(alpha);
	matrix.data[2][2] = cos(alpha);
	matrix.data[3][3] = 1.0;

	return matrix;
}

Matrix4 Perspectivic::ZRotation(double alpha) {

	Matrix4 matrix;
	alpha = ((alpha + 44) * M_PI) / 180.0;

	matrix.data[0][0] = cos(alpha);
	matrix.data[0][1] = -sin(alpha);
	matrix.data[1][0] = sin(alpha);
	matrix.data[1][1] = cos(alpha);
	matrix.data[2][2] = 1.0;
	matrix.data[3][3] = 1.0;

	return matrix;
}

void Perspectivic::GenerateTransformMatrix(int width, int height) {

	Matrix4 m1;
	m1.data[0][0] = 1;
	m1.data[1][1] = 1;
	m1.data[3][2] = 1.0 / 2.0;

	Matrix4 m2;
	m2.data[0][0] = width / 2;
	m2.data[1][1] = -height / 2.;
	m2.data[0][3] = width / 2.;
	m2.data[1][3] = height / 2.;

	Matrix4 matrix; // transformata skalowania
	matrix.data[0][0] = scale;
	matrix.data[1][1] = scale;
	matrix.data[2][2] = scale;

	Matrix4 matrix2; // transformata przesuniecia
	matrix2.data[0][0] = matrix2.data[1][1] = matrix2.data[2][2] = 1;
	matrix2.data[0][3] = -((xmax + xmin) / 2);
	matrix2.data[1][3] = -((ymax + ymin) / 2);
	matrix2.data[2][3] = -(zmax + zmin) / 2;
	//matrix2.data[2][3] = 4;

	Matrix4 matrix3; // transformata obrotu
	matrix3 = XRotation(0) * YRotation(0) * ZRotation(0);

	t = matrix3 * matrix * matrix2;
	t1 = m2 * m1;
}

void Perspectivic::getMinYMaxY() {

	if (!(maxY == -1.0e30 && minY == 1.0e30)) {

		return;
	}

	for (int i = 0; i < data.size(); i++) {

		maxY = ((double)data[i].begin.z > maxY ? (double)data[i].begin.z : maxY);
		minY = ((double)data[i].begin.z < minY ? (double)data[i].begin.z : minY);
	}
}

void Perspectivic::Repaint(wxPanel* drawingPanel, int w, int h)
{
	// tu rysowac
	wxClientDC DC(drawingPanel);
	wxBufferedDC BufferedDC(&DC);
	int width = w;
	int height = h;
	BufferedDC.SetBackground(wxBrush(wxColour("white")));
	BufferedDC.Clear();

	GenerateTransformMatrix(width, height);

	getMinYMaxY();

	//double colorR = 255;
	//double colorB = 0;

	for (int i = 0; i < data.size(); i++) {

		Vector4 begin, end;

		//colorR = 255 * ((maxY - data[i].begin.z) * 10000 / (maxY - minY)) / 10000;
		//colorB = 255 * ((data[i].begin.z - minY) * 10000 / (maxY - minY)) / 10000;
		//BufferedDC.SetPen(wxPen(wxColour(colorR, 0, colorB)));

		if (data[i].color.R == 255 && data[i].color.G == 255 && data[i].color.B == 255)continue;

		BufferedDC.SetPen(wxPen(wxColour(data[i].color.R, data[i].color.G, data[i].color.B)));

		begin.Set(data[i].begin.x, data[i].begin.y, data[i].begin.z);
		end.Set(data[i].end.x, data[i].end.y, data[i].end.z);

		begin = t * begin;
		end = t * end;

		begin.data[0] /= begin.data[3];
		begin.data[1] /= begin.data[3];
		begin.data[2] /= begin.data[3];

		end.data[0] /= end.data[3];
		end.data[1] /= end.data[3];
		end.data[2] /= end.data[3];

		if ((begin.GetZ() > -2.0 && end.GetZ() <= -2.0) || (end.GetZ() > -2.0 && begin.GetZ() <= -2.0)) {

			Vector4 temp1 = end.GetZ() <= -2.0 ? end : begin;
			Vector4 temp2 = end.GetZ() <= -2.0 ? begin : end;
			double r = abs((-2.0 - temp1.data[2]) / (temp2.data[2] - temp1.data[2]));
			temp1.data[0] = (temp2.data[0] - temp1.data[0]) * r + temp1.data[0];
			temp1.data[1] = (temp2.data[1] - temp1.data[1]) * r + temp1.data[1];
			temp1.data[2] = -2.0;

			begin = t1 * temp1;
			end = t1 * temp2;

			begin.data[0] /= begin.data[3];
			begin.data[1] /= begin.data[3];
			begin.data[2] /= begin.data[3];

			end.data[0] /= end.data[3];
			end.data[1] /= end.data[3];
			end.data[2] /= end.data[3];

		}
		else if (begin.GetZ() <= -2.0 && end.GetZ() <= -2.0) {
			continue;
		}
		else {
			begin = t1 * begin;
			end = t1 * end;

			begin.data[0] /= begin.data[3];
			begin.data[1] /= begin.data[3];
			begin.data[2] /= begin.data[3];

			end.data[0] /= end.data[3];
			end.data[1] /= end.data[3];
			end.data[2] /= end.data[3];
		}

		BufferedDC.DrawLine(width - begin.GetX(), begin.GetY(), width - end.GetX(), end.GetY());
	}
}