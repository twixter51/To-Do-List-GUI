#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>


class MainFrame: public wxFrame
{

public: 
	MainFrame(const wxString& title);

private:
	//Main Variables
	void onButtonClicked(wxCommandEvent& evt);
	void onTextEntered(wxCommandEvent& evt);
	void onPriorityClicked(wxCommandEvent& evt);
	wxArrayString choices;
	wxListCtrl* listCtrl;
	wxPanel* panel;
	wxTextCtrl* textEntryPoint;
	//Variables used for checking task selections
	int selectCount;
	int itemNum;
	//
	
	//Extra Variables
	bool hasEnteredTasks = false;
};
