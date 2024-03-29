// wxWidgets specifics
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#pragma ide diagnostic ignored "bugprone-suspicious-enum-usage"

#include "Frame.hpp"
#include "../../Helpers.hpp"
#include "../../IBackend.hpp"
#include "wx/listctrl.h"
#include "wx/wx.h"
#include <algorithm>
#include <string>

Frame::Frame() :
    wxFrame(nullptr,
            wxID_ANY,
            "Binary converter",
            wxDefaultPosition,
            wxDefaultSize,
            wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    this->initUi();
    Bind(wxEVT_RADIOBUTTON, &Frame::onBaseChanged, this, IDRadioButton_Dec, IDRadioButton_Hex);
    Bind(wxEVT_BUTTON, &Frame::onButtonPressed, this, IDButton_0, IDButton_F);
    Bind(wxEVT_BUTTON, &Frame::onClearButtonPressed, this, IDButton_Clear);
    Bind(wxEVT_BUTTON, &Frame::onSaveButtonPressed, this, IDButton_Save);
    Bind(wxEVT_SIZE, &Frame::onResize, this);
    Bind(wxEVT_CHAR_HOOK, &Frame::onKeyPressed, this);
}

void Frame::setBackend(IBackend* backend) { backend_ = backend; }

void Frame::setDec(const std::string& dec) {
    if (RButtonBin_->GetValue() || RButtonHex_->GetValue()) {
        resultStr1_ = dec;
        result1_->Clear();
        result1_->AppendText(resultStr1_);
    }
}

void Frame::setBin(const std::string& bin) {
    if (RButtonDec_->GetValue()) {
        resultStr1_ = bin;
        result1_->Clear();
        result1_->AppendText(resultStr1_);
    }
    if (RButtonHex_->GetValue()) {
        resultStr2_ = bin;
        result2_->Clear();
        result2_->AppendText(resultStr2_);
    }
}

void Frame::setHex(const std::string& hex) {
    if (RButtonDec_->GetValue() || RButtonBin_->GetValue()) {
        resultStr2_ = hex;
        result2_->Clear();
        result2_->AppendText(resultStr2_);
    }
}

void Frame::initUi() {
    auto* inputResultSizer = new wxBoxSizer(wxVERTICAL);
    resultBox_->Add(resultLabel1_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    resultBox_->Add(result1_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    resultBox_->Add(resultLabel2_, 0, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    resultBox_->Add(result2_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    inputResultSizer->Add(inputTextCtrl_, 1, wxEXPAND | wxALL, defaultPadding_);
    inputResultSizer->Add(resultBox_, 1, wxEXPAND | wxALL, defaultPadding_);

    auto* saveClearSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* buttonSave {new wxButton(this, IDButton_Save, "Save")};
    wxButton* buttonClear {new wxButton(this, IDButton_Clear, "Clear")};
    saveClearSizer->Add(buttonSave, 1, wxEXPAND);
    saveClearSizer->Add(buttonClear, 1, wxEXPAND);
    baseSelectionBox_->Add(RButtonDec_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    baseSelectionBox_->Add(RButtonBin_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    baseSelectionBox_->Add(RButtonHex_, 1, wxALIGN_CENTER_VERTICAL | wxALL, defaultPadding_);
    RButtonDec_->SetValue(true);
    decSelected();
    auto* baseSelectionAndButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    baseSelectionAndButtonsSizer->Add(baseSelectionBox_, 1, wxEXPAND | wxALL, defaultPadding_);
    baseSelectionAndButtonsSizer->Add(saveClearSizer, 1, wxEXPAND | wxALL, defaultPadding_);

    auto* buttonSizer = new wxGridSizer(4, 4, 0, 0);
    buttonSizer->Add(buttonC_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(buttonD_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(buttonE_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(buttonF_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button8_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button9_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(buttonA_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(buttonB_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button4_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button5_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button6_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button7_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button0_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button1_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button2_, 0, wxEXPAND | wxALL, defaultPadding_);
    buttonSizer->Add(button3_, 0, wxEXPAND | wxALL, defaultPadding_);

    resultsSizer_->Add(listResult_, 1, wxEXPAND | wxALL, defaultPadding_);

    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(inputResultSizer, 0, wxEXPAND);
    mainSizer->Add(baseSelectionAndButtonsSizer, 0, wxEXPAND);
    mainSizer->Add(buttonSizer, 0, wxEXPAND);
    mainSizer->Add(resultsSizer_, 1, wxEXPAND);
    this->SetSizerAndFit(mainSizer);

    listResult_->AppendColumn("Dec", wxLIST_FORMAT_LEFT);
    listResult_->AppendColumn("Bin", wxLIST_FORMAT_CENTER);
    listResult_->AppendColumn("Hex", wxLIST_FORMAT_RIGHT);

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
    std::string buttonLabel {dynamic_cast<wxButton*>(evt.GetEventObject())->GetLabel()};
    if (buttonLabel.size() == 1) {
        handleInput(buttonLabel[0]);
    }
}

void Frame::onKeyPressed(wxKeyEvent& evt) {
    static constexpr uint32_t asciiZero {48};
    if (evt.GetKeyCode() == WXK_BACK) {
        if (RButtonBin_->GetValue() && inputStr_ == binPrefix) {
            return;
        }
        if (RButtonHex_->GetValue() && inputStr_ == hexPrefix) {
            return;
        }
        if (RButtonDec_->GetValue() && inputStr_ == decPrefix) {
            return;
        }
        if (inputStr_.size() == 1) {
            inputStr_ = "0";
        } else {
            inputStr_.pop_back();
        }
        convert(inputStr_);
        return;
    }
    uint32_t numKey {evt.GetKeyCode() - static_cast<uint32_t>(WXK_NUMPAD0)};
    if (numKey >= 0 && numKey < 10) {
        handleInput(static_cast<char>(numKey + asciiZero));
        return;
    }
    handleInput(static_cast<char>(evt.GetUnicodeKey()));
}

void Frame::onClearButtonPressed(wxCommandEvent& evt) { reset(); }

void Frame::onSaveButtonPressed(wxCommandEvent& evt) {
    std::string dec = getDec();
    std::string bin = getBin();
    std::string hex = getHex();
    if (dec == decPrefix) {
        dec.append("0");
    }
    if (bin == binPrefix) {
        bin.append("0");
    }
    if (hex == hexPrefix) {
        hex.append("0");
    }
    listResult_->InsertItem(0, dec);
    listResult_->SetItem(0, 1, bin);
    listResult_->SetItem(0, 2, hex);
}

void Frame::onResize(wxSizeEvent& evt) {
    int listResultWidth {resultsSizer_->GetSize().GetWidth() - 2 * defaultPadding_};
    listResult_->SetColumnWidth(0, (listResultWidth / 3) - 40);
    listResult_->SetColumnWidth(1, (listResultWidth / 3) + 80);
    listResult_->SetColumnWidth(2, (listResultWidth / 3) - 40);
    evt.Skip();
}

void Frame::handleInput(char input) {
    if (RButtonBin_->GetValue()) {
        if (std::find(binChars.cbegin(), binChars.cend(), input) == binChars.cend()) {
            return;
        }
    }
    if (RButtonDec_->GetValue()) {
        if (std::find(decChars.cbegin(), decChars.cend(), input) == decChars.cend()) {
            return;
        }
    }
    if (RButtonHex_->GetValue()) {
        if (std::find(hexChars.cbegin(), hexChars.cend(), input) == hexChars.cend()) {
            return;
        }
    }
    if (input == '0' && (inputStr_ == decPrefix || inputStr_ == binPrefix || inputStr_ == hexPrefix)) {
        return;
    }
    convert(inputStr_ + input);
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

void Frame::convert(const std::string& toConvert) {
    if (backend_->convert(toConvert)) {
        inputStr_ = toConvert;
        inputTextCtrl_->Clear();
        inputTextCtrl_->AppendText(inputStr_);
    }
}

std::string Frame::getDec() {
    if (RButtonBin_->GetValue() || RButtonHex_->GetValue()) {
        return resultStr1_;
    }
    return inputTextCtrl_->GetLineText(0);
}

std::string Frame::getBin() {
    if (RButtonDec_->GetValue()) {
        return resultStr1_;
    }
    if (RButtonHex_->GetValue()) {
        return resultStr2_;
    }
    return inputTextCtrl_->GetLineText(0);
}

std::string Frame::getHex() {
    if (RButtonDec_->GetValue() || RButtonBin_->GetValue()) {
        return resultStr2_;
    }
    return inputTextCtrl_->GetLineText(0);
}

#pragma clang diagnostic pop
