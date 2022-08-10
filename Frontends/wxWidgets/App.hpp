#pragma once
#include "../../Backend.hpp"
#include "Frame.hpp"
#include "wx/wx.h"
#include <memory>

class App : public wxApp {
public:
    bool OnInit() override;

private:
    Frame* frame {nullptr};
    std::unique_ptr<Backend> converter {nullptr};
};
