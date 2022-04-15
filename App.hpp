#pragma once
#include <wx/wx.h>

class Frame;
class Converter;

class App : public wxApp {
public:
    bool OnInit() override;

private:
    Frame* frame {nullptr};
    Converter* converter {nullptr};
};
