#ifndef __MY_P__
#define __MY_P__

#include <wx/wx.h>
#include <wx/print.h>
#include <wx/printdlg.h>

#include <memory>

class ImagePrintout : public wxPrintout {
public:
    ImagePrintout(const wxString& title, const wxImage& image)
        : wxPrintout(title), pImage(image) {}

    bool OnPrintPage(int pageNum) override {
        wxDC* dc = GetDC();
        if (dc) {
            FitThisSizeToPage(wxSize(pImage.GetWidth()*2, pImage.GetHeight()*2));
            wxBitmap bitmap(pImage);
            dc->DrawBitmap(bitmap, 100, 100, false);

            return true;
        }
        return false;
    }

    bool HasPage(int pageNum) override {
        return pageNum == 1;
    }

private:
    wxImage pImage;
};

#endif
