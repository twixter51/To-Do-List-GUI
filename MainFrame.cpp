#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <algorithm>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	 panel = new wxPanel(this);

	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "ToDo-List", wxPoint(345, 10), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	staticText->SetBackgroundColour(*wxLIGHT_GREY);
	wxStaticText* yourListText = new wxStaticText(panel, wxID_ANY, "Your List", wxPoint(25, 120), wxDefaultSize);
	yourListText->SetBackgroundColour(*wxLIGHT_GREY);

	wxButton* removeButton = new wxButton(panel, wxID_ANY, "Remove Item", wxPoint(25, 350), wxSize(200, 50));
	wxButton* setPriority = new wxButton(panel, wxID_ANY, "Prioritize", wxPoint(550, 500), wxSize(200, 50));
	wxStaticText* tempPriorityText = new wxStaticText(panel, wxID_ANY, "Set the priority of any task, ones you would love to finish quick!", wxPoint(450, 550), wxDefaultSize);
	wxStaticText* legendText = new wxStaticText(panel, wxID_ANY, "Legend: Highlighted/Blue = #1 Priority, Red = Subsequent Tasks", wxPoint(220, 570), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);


	wxStaticText* barText = new wxStaticText(panel, wxID_ANY, "Enter Tasks: ", wxPoint(25, 430), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	textEntryPoint = new wxTextCtrl(panel, wxID_ANY,"", wxPoint(25, 450), wxSize(350, 25), wxTE_PROCESS_ENTER);


	removeButton->Bind(wxEVT_BUTTON, &MainFrame::onButtonClicked, this);
	textEntryPoint->Bind(wxEVT_TEXT_ENTER, &MainFrame::onTextEntered, this);
	setPriority->Bind(wxEVT_BUTTON, &MainFrame::onPriorityClicked, this);
	CreateStatusBar();

	
	

	
	
	listCtrl = new wxListCtrl(panel, wxID_ANY, wxPoint(25, 150), wxSize(400, 200), wxLC_REPORT | wxLC_NO_HEADER);
	listCtrl->InsertColumn(0, "");
	listCtrl->SetColumnWidth(0, 1000);
	listCtrl->EnableSystemTheme(false);
	listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::onItemSelected, this); 

	//Setting Font Sizes
	wxFont font = staticText->GetFont();
	font.SetPointSize(20);  // Set the desired font size
	staticText->SetFont(font);
	

	wxFont font2 = yourListText->GetFont();
	font2.SetPointSize(15);  // Set the desired font size
	yourListText->SetFont(font2);
	

	 wxFont font3 = listCtrl->GetFont();
	font3.SetPointSize(15);// Set the desired font size
	font3.SetFamily(wxFONTFAMILY_SCRIPT);
	listCtrl ->SetFont(font3);
	legendText->SetFont(font3);


}



void MainFrame::onButtonClicked(wxCommandEvent& evt) {
	// Get selected items
	wxArrayInt selections;

	int item = -1;
	while ((item = listCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
		selections.Add(item);
	}

	wxString removedItems;
	if (listCtrl->GetItemCount() != 0 && !selections.IsEmpty()) {
		// Sort selections in descending order
		std::sort(selections.begin(), selections.end(), std::greater<int>());

		// Collect removed items' text
		for (size_t i = 0; i < selections.GetCount(); ++i) {
			if (!removedItems.IsEmpty()) {
				removedItems += ", ";
			}
			removedItems += listCtrl->GetItemText(selections[i]);
		}

		// Remove selected items
		for (int j : selections) {
			listCtrl->DeleteItem(j);
		}

		wxLogStatus("Removed " + removedItems);
	}
	else if (listCtrl->GetItemCount() == 0 && hasEnteredTasks == false) {
		wxLogMessage("Type in tasks in the search bar below to get started!");
	}
	else if (listCtrl->GetItemCount() == 0 && hasEnteredTasks == true) {
		wxLogMessage("Congratulations! you have finished all your tasks for the day!");
	}
	else {
		wxLogMessage("Please select a task!");
	}
	
}



void MainFrame::onTextEntered(wxCommandEvent& evt) {
	wxString getText = textEntryPoint->GetValue();
	
	listCtrl->InsertItem(listCtrl->GetItemCount(), getText + std::to_string(itemNum));
	for (int i = 0; i < listCtrl->GetItemCount(); ++i) {
		itemNum = i;
	}
	listCtrl->SetItemText(itemNum, std::to_string(itemNum + 1) + ". " + getText);
	hasEnteredTasks = true;

	
}



void MainFrame::onItemSelected(wxListEvent& evt) {

//to be added in future update


}

void MainFrame::onPriorityClicked(wxCommandEvent& evt) {
	wxArrayInt selections;
	int item = -1;
	while ((item = listCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
		selections.Add(item + 1);	
	}

	wxString str;
	wxColour highlightColor(252, 169, 3);
	wxColour priorityColor(204, 207, 186);
	wxString num1Priority;
	if (selections.GetCount() <= 0) {
		wxLogMessage("Please select tasks you would like to prioritize");
		return;
	}
	for (int i = 0; i < selections.GetCount(); ++i) {
		if (i > 0){
			str += ", ";
		}
		
		str += "Prioritized: " + wxString::Format("%d", selections[i]);

		//if we already have prioritized
		if (listCtrl->GetItemTextColour((selections[i]) - 1) == wxColour("orange")) {
			listCtrl->SetItemTextColour((selections[i]) - 1, wxColour("blue"));
			num1Priority +=  "( #1 PRIORITY: "  + wxString::Format("%d", selections[i]) + " )";
			listCtrl->SetItemBackgroundColour((selections[i]) - 1, priorityColor);
		}
		else {
			listCtrl->SetItemTextColour((selections[i]) - 1, wxColour("orange"));
		}
		

	}
	


	//remove selections
	listCtrl->SetItemState(-1, 0, wxLIST_STATE_SELECTED);
	wxLogMessage(str + " "  + num1Priority);
}
