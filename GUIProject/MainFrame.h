#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textfile.h>
#include <wx/ffile.h>

class MainFrame: public wxFrame
{

public: 
	MainFrame(const wxString& title);
	
	
private:
	//Main methods
	void onButtonClicked(wxCommandEvent& evt);
	void onTextEntered(wxCommandEvent& evt);
	void onPriorityClicked(wxCommandEvent& evt);
	void onItemSelected(wxListEvent& evt);

	//buttons
	wxButton* setPriority;
	wxButton* removeButton;
	wxButton* removeAll;
	wxButton* removePriority;
	//Selections variables
	wxArrayString choices;
	wxListCtrl* listCtrl;
	wxPanel* panel;
	wxTextCtrl* textEntryPoint;
	

	// More variables used for checking task selections
	int selectCount;
	int itemNum;
	//Extra Variables
	bool hasEnteredTasks = false;

	//Files for saving data
	wxTextFile file;


};

