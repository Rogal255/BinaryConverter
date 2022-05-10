#pragma once
#include "Converter.hpp"
#include "Frame.hpp"
#include <memory>
#include <wx/wx.h>

class App : public wxApp {
public:
    bool OnInit() override;

private:
    std::unique_ptr<Frame> frame {std::make_unique<Frame>()};
    std::unique_ptr<Converter> converter {std::make_unique<Converter>()};
};
