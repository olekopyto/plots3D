#include "GUIMyFrame1.h"



GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	panelWidth = panelNaWykres->GetSize().GetWidth();
	panelHeight = panelNaWykres->GetSize().GetHeight();
}

void GUIMyFrame1::showInfo(wxMouseEvent& event)
{
	//uzupe³niæ o instrukcjê!
	wxMessageDialog* infoDialog = new wxMessageDialog(this, "-> use \"sqrt()\" as aquare root\n->use \"^n\" to raise to the n-th power", 
															"How to plot?", wxOK | wxICON_INFORMATION);
	infoDialog->ShowModal();
	infoDialog->Destroy();
}

bool GUIMyFrame1::checkFunction()
{
	bool errorF = false;
	//sprawdzanie porpawnosci wprowadzonej funkcji!

	//tie(zValuesVec, xValuesVec, yValuesVec) = evaluatePlaneExpression(function, xMin, xMax, yMin, yMax);

	if ( errorF ) {
		textCtrlFunkcja->SetValue("");
		return false;
	}

	return true;
}

bool GUIMyFrame1::checkNumbers()
{
	try {
		xMin = stod(textCtrlXMin->GetValue().ToStdString());
		textCtrlXMin->SetValue(to_string(xMin));
	}
	catch (const std::invalid_argument&) {
		textCtrlXMin->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlXMin->SetValue("");
		return false;
	}

	try {
		xMax = stod(textCtrlXMax->GetValue().ToStdString());
		textCtrlXMax->SetValue(to_string(xMax));
	}
	catch (const std::invalid_argument&) {
		textCtrlXMax->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlXMax->SetValue("");
		return false;
	}

	try {
		yMin = stod(textCtrlYMin->GetValue().ToStdString());
		textCtrlYMin->SetValue(to_string(yMin));
	}
	catch (const std::invalid_argument&) {
		textCtrlYMin->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlYMin->SetValue("");
		return false;
	}

	try {
		yMax = stod(textCtrlYMax->GetValue().ToStdString());
		textCtrlYMax->SetValue(to_string(yMax));
	}
	catch (const std::invalid_argument&) {
		textCtrlYMax->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlYMax->SetValue("");
		return false;
	}

	try {
		zMin = stod(textCtrlZMin->GetValue().ToStdString());
		textCtrlZMin->SetValue(to_string(zMin));
	}
	catch (const std::invalid_argument&) {
		textCtrlZMin->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlZMin->SetValue("");
		return false;
	}

	try {
		zMax = stod(textCtrlZMax->GetValue().ToStdString());
		textCtrlZMax->SetValue(to_string(zMax));
	}
	catch (const std::invalid_argument&) {
		textCtrlZMax->SetValue("");
		return false;
	}
	catch (const std::out_of_range&) {
		textCtrlZMax->SetValue("");
		return false;
	}

	if (xMax <= xMin) {
		textCtrlXMax->SetValue("");
		textCtrlXMin->SetValue("");
		return false;
	}
	if (yMax <= yMin) {
		textCtrlYMax->SetValue("");
		textCtrlYMin->SetValue("");
		return false;
	}
	if (zMax <= zMin) {
		textCtrlZMax->SetValue("");
		textCtrlZMin->SetValue("");
		return false;
	}

	return true;
}

void GUIMyFrame1::perspectiveClick(wxMouseEvent& event)
{
	inPerspective = true;
	inMap = false;

	if (radioRzut->GetValue()) {
		radioMapa->SetValue(false);
		
		//generujemy wykres!
		if (generateClicked) repaint();
	}
	else {
		radioRzut->SetValue(true);
	}
}

void GUIMyFrame1::outlineClick(wxMouseEvent& event)
{
	inPerspective = false;
	inMap = true;

	if (radioMapa->GetValue()) {
		radioRzut->SetValue(false);

		//generujemy wykres!
		if (generateClicked) repaint();
	}
	else {
		radioMapa->SetValue(true);
	}
}

void GUIMyFrame1::printClick(wxMouseEvent& event)
{
	wxClientDC dc(panelNaWykres);
	wxSize size = panelNaWykres->GetSize();
	wxBitmap bitmap(size);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, size.GetWidth(), size.GetHeight(), &dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);
	wxImage printPicture = bitmap.ConvertToImage();
	printPicture.AddHandler(new wxJPEGHandler);
	printPicture.AddHandler(new wxPNGHandler);

	wxPrinter printer;
	ImagePrintout printout("Image Printout", printPicture);

	if (!printer.Print(this, &printout, true)) {
		if (wxPrinter::GetLastError() == wxPRINTER_ERROR) {
			wxMessageBox("There was a problem with printing.", "Error", wxOK);
		}
		else {
			wxMessageBox("The printing was cancelled.", "Info", wxOK);
		}
	}
}

void GUIMyFrame1::saveClick(wxMouseEvent& event)
{
	wxFileDialog saveFileDialog(this, "Choose a file", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

	wxClientDC dc(panelNaWykres);
	wxSize size = panelNaWykres->GetSize();
	wxBitmap bitmap(size);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, size.GetWidth(), size.GetHeight(), &dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);
	wxImage savePicture = bitmap.ConvertToImage();
	savePicture.AddHandler(new wxJPEGHandler);
	savePicture.AddHandler(new wxPNGHandler);
	savePicture.SaveFile(saveFileDialog.GetPath());
}

void GUIMyFrame1::generateClick(wxMouseEvent& event)
{
	if (!checkFunction() || !checkNumbers()) return;
	repaint();
	generateClicked = true;
}

void GUIMyFrame1::panelRepaint(wxSizeEvent& event)
{
	if ( ( panelWidth != panelNaWykres->GetSize().GetWidth() || panelHeight != panelNaWykres->GetSize().GetHeight() ) && generateClicked ) {

		panelWidth = panelNaWykres->GetSize().GetWidth();
		panelHeight = panelNaWykres->GetSize().GetHeight();

		repaint();
	}
	panelWidth = panelNaWykres->GetSize().GetWidth();
	panelHeight = panelNaWykres->GetSize().GetHeight();
}

void GUIMyFrame1::repaint()
{
	//gerneruj wykres
	if (isPerspective()) {
		//generuj rzut perspektywiczny
		objPer.getAxis(xMin, xMax, yMin, yMax, zMin, zMax);
		vector<vector<double>> vec{ 5 };
		objPer.RecountFunctionIntoData(vec);
		objPer.Repaint(panelNaWykres, panelWidth, panelHeight);
	}
	else {
		//generuj mape konturowa
		objMap.getZ( zMin, zMax );
		objMap.repaint(panelNaWykres, panelWidth, panelHeight);
		
	}
}
