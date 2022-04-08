// wxWidgets specifics
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#pragma ide diagnostic ignored "bugprone-suspicious-enum-usage"

#include "Frame.hpp"
#include <string>
#include <wx/listctrl.h>
#include <wx/wx.h>

Frame::Frame() :
    wxFrame(nullptr,
            wxID_ANY,
            "Binary converter",
            wxDefaultPosition,
            wxDefaultSize,
            wxDEFAULT_FRAME_STYLE /*& ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)*/) {
    this->initUi();
    Bind(wxEVT_RADIOBUTTON, &Frame::onBaseChanged, this, IDRadioButton_Dec, IDRadioButton_Hex);
}

void Frame::initUi() {
    constexpr int defaultPadding {10};

    auto* inputResultSizer = new wxBoxSizer(wxVERTICAL);
    auto* inputText = new wxTextCtrl(this, wxID_ANY);
    resultBox_->Add(resultLabel1_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(result1_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(resultLabel2_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(result2_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    inputResultSizer->Add(inputText, 1, wxEXPAND | wxALL, defaultPadding);
    inputResultSizer->Add(resultBox_, 1, wxEXPAND | wxALL, defaultPadding);

    auto* saveClearSizer = new wxBoxSizer(wxVERTICAL);
    saveClearSizer->Add(buttonSave_, 1, wxEXPAND);
    saveClearSizer->Add(buttonClear_, 1, wxEXPAND);
    baseSelectionBox_->Add(RButtonDec_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    baseSelectionBox_->Add(RButtonBin_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    baseSelectionBox_->Add(RButtonHex_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    RButtonDec_->SetValue(true);
    decSelected();
    auto* baseSelectionAndButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    baseSelectionAndButtonsSizer->Add(baseSelectionBox_, 1, wxEXPAND | wxALL, defaultPadding);
    baseSelectionAndButtonsSizer->Add(saveClearSizer, 1, wxEXPAND | wxALL, defaultPadding);

    auto* buttonSizer = new wxGridSizer(4, 4, 0, 0);
    buttonSizer->Add(buttonC_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(buttonD_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(buttonE_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(buttonF_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button8_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button9_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(buttonA_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(buttonB_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button4_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button5_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button6_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button7_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button0_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button1_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button2_, 0, wxEXPAND | wxALL, defaultPadding);
    buttonSizer->Add(button3_, 0, wxEXPAND | wxALL, defaultPadding);

    auto* resultsSizer = new wxBoxSizer(wxHORIZONTAL);
    resultsSizer->Add(listResult_, 1, wxEXPAND | wxALL, defaultPadding);

    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(inputResultSizer, 0, wxEXPAND);
    mainSizer->Add(baseSelectionAndButtonsSizer, 0, wxEXPAND);
    mainSizer->Add(buttonSizer, 0, wxEXPAND);
    mainSizer->Add(resultsSizer, 1, wxEXPAND);
    this->SetSizerAndFit(mainSizer);

    int listResultWidth {resultsSizer->GetSize().GetWidth() - 2 * defaultPadding};
    listResult_->AppendColumn("Dec", wxLIST_FORMAT_LEFT, (listResultWidth / 3) - 40);
    listResult_->AppendColumn("Bin", wxLIST_FORMAT_CENTER, (listResultWidth / 3) + 80);
    listResult_->AppendColumn("Hex", wxLIST_FORMAT_RIGHT, (listResultWidth / 3) - 40);
    listResult_->InsertItem(0, "123");
    listResult_->SetItem(0, 1, "0b1111011");
    listResult_->SetItem(0, 2, "0x7B");
}

void Frame::onBaseChanged(wxCommandEvent& evt) {
    switch (evt.GetId()) {
    case IDRadioButton_Dec:
        decSelected();
        break;
    case IDRadioButton_Bin:
        binSelected();
        break;
    case IDRadioButton_Hex:
        hexSelected();
        break;
    default:
        wxMessageBox("Radio button error");
        break;
    }
}

void Frame::decSelected() {
    button0_->Enable();
    button1_->Enable();
    button2_->Enable();
    button3_->Enable();
    button4_->Enable();
    button5_->Enable();
    button6_->Enable();
    button7_->Enable();
    button8_->Enable();
    button9_->Enable();
    buttonA_->Enable(false);
    buttonB_->Enable(false);
    buttonC_->Enable(false);
    buttonD_->Enable(false);
    buttonE_->Enable(false);
    buttonF_->Enable(false);
    resultLabel1_->SetLabel("BIN");
    resultLabel2_->SetLabel("HEX");
}

void Frame::binSelected() {
    button0_->Enable();
    button1_->Enable();
    button2_->Enable(false);
    button3_->Enable(false);
    button4_->Enable(false);
    button5_->Enable(false);
    button6_->Enable(false);
    button7_->Enable(false);
    button8_->Enable(false);
    button9_->Enable(false);
    buttonA_->Enable(false);
    buttonB_->Enable(false);
    buttonC_->Enable(false);
    buttonD_->Enable(false);
    buttonE_->Enable(false);
    buttonF_->Enable(false);
    resultLabel1_->SetLabel("DEC");
    resultLabel2_->SetLabel("HEX");
}
void Frame::hexSelected() {
    button0_->Enable();
    button1_->Enable();
    button2_->Enable();
    button3_->Enable();
    button4_->Enable();
    button5_->Enable();
    button6_->Enable();
    button7_->Enable();
    button8_->Enable();
    button9_->Enable();
    buttonA_->Enable();
    buttonB_->Enable();
    buttonC_->Enable();
    buttonD_->Enable();
    buttonE_->Enable();
    buttonF_->Enable();
    resultLabel1_->SetLabel("DEC");
    resultLabel2_->SetLabel("BIN");
}

#pragma clang diagnostic pop
