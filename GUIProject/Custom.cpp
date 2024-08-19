#include <wx/wx.h>
#include <wx/vlbox.h>
#include <wx/tokenzr.h>

class MultiLineListBox : public wxVListBox
{
public:
    MultiLineListBox(wxWindow* parent, const wxArrayString& items)
        : wxVListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_SINGLE),
        m_items(items)
    {
        SetItemCount(items.size());
    }

protected:
    virtual void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const override
    {
        dc.SetTextForeground(*wxBLACK);
        dc.SetFont(GetFont());

        wxString text = m_items[n];
        wxArrayString lines = WrapText(dc, text, rect.GetWidth());

        int lineHeight = dc.GetCharHeight();
        int y = rect.GetY();

        for (const wxString& line : lines)
        {
            dc.DrawText(line, rect.GetX(), y);
            y += lineHeight;
        }
    }

    virtual wxCoord OnMeasureItem(size_t n) const override
    {
        wxClientDC dc((wxWindow*)this);
        dc.SetFont(GetFont());

        wxString text = m_items[n];
        wxArrayString lines = WrapText(dc, text, GetClientSize().GetWidth());

        return dc.GetCharHeight() * lines.size();
    }

private:
    wxArrayString WrapText(wxDC& dc, const wxString& text, int width) const
    {
        wxArrayString lines;
        wxString currentLine;
        wxStringTokenizer tokenizer(text, " ");

        while (tokenizer.HasMoreTokens())
        {
            wxString token = tokenizer.GetNextToken();
            wxString testLine = currentLine.empty() ? token : currentLine + " " + token;

            if (dc.GetTextExtent(testLine).GetWidth() > width)
            {
                lines.Add(currentLine);
                currentLine = token;
            }
            else
            {
                currentLine = testLine;
            }
        }

        if (!currentLine.empty())
        {
            lines.Add(currentLine);
        }

        return lines;
    }

    wxArrayString m_items;
};