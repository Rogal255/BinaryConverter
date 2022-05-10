#pragma once
#include "Converter.hpp"
#include "Frame.hpp"
#include <memory>
#include <wx/wx.h>

class App : public wxApp {
public:
    bool OnInit() override;

private:
    Frame* frame {nullptr};
    std::unique_ptr<Converter> converter {nullptr};
};
