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
    Bind(wxEVT_BUTTON, &Frame::onButtonPressed, this, IDButton_0, IDButton_F);
    Bind(wxEVT_BUTTON, &Frame::onClearButtonPressed, this, IDButton_Clear);
}

void Frame::initUi() {
    constexpr int defaultPadding {10};

    auto* inputResultSizer = new wxBoxSizer(wxVERTICAL);
    resultBox_->Add(resultLabel1_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(result1_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(resultLabel2_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    resultBox_->Add(result2_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding);
    inputResultSizer->Add(inputTextCtrl_, 1, wxEXPAND | wxALL, defaultPadding);
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

    wxFont myFont = inputTextCtrl_->GetFont();
    myFont.SetPointSize(30);
    inputTextCtrl_->SetFont(myFont);
    reset();
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
        return;
    }
    reset();
}

void Frame::onButtonPressed(wxCommandEvent& evt) {
    int buttonID {evt.GetId() - IDButton_0};
    if (buttonID == 0 && (inputStr_ == decPrefix || inputStr_ == binPrefix || inputStr_ == hexPrefix)) {
        return;
    }
    if (buttonID < 10) {
        inputStr_.append(std::to_string(buttonID));
    } else {
        switch (buttonID) {
        case 10:
            inputStr_.append("A");
            break;
        case 11:
            inputStr_.append("B");
            break;
        case 12:
            inputStr_.append("C");
            break;
        case 13:
            inputStr_.append("D");
            break;
        case 14:
            inputStr_.append("E");
            break;
        case 15:
            inputStr_.append("F");
            break;
        default:
            wxMessageBox("Main buttons error");
            return;
        }
    }
    inputTextCtrl_->Clear();
    inputTextCtrl_->AppendText(inputStr_);
}

void Frame::onClearButtonPressed(wxCommandEvent& evt) { reset(); }

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
}

void Frame::reset() {
    if (RButtonDec_->GetValue()) {
        resultLabel1_->SetLabel("BIN");
        resultLabel2_->SetLabel("HEX");
        inputStr_ = decPrefix;
        resultStr1_ = binPrefix;
        resultStr2_ = hexPrefix;
    } else if (RButtonBin_->GetValue()) {
        resultLabel1_->SetLabel("DEC");
        resultLabel2_->SetLabel("HEX");
        inputStr_ = binPrefix;
        resultStr1_ = decPrefix;
        resultStr2_ = hexPrefix;
    } else if (RButtonHex_->GetValue()) {
        resultLabel1_->SetLabel("DEC");
        resultLabel2_->SetLabel("BIN");
        inputStr_ = hexPrefix;
        resultStr1_ = decPrefix;
        resultStr2_ = binPrefix;
    }
    inputTextCtrl_->Clear();
    inputTextCtrl_->AppendText(inputStr_);
    result1_->Clear();
    result1_->AppendText(resultStr1_);
    result2_->Clear();
    result2_->AppendText(resultStr2_);
}

#pragma clang diagnostic pop
