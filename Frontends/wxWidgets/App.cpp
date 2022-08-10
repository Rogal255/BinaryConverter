#include "App.hpp"
#include "../../Backend.hpp"
#include "Frame.hpp"
#include "wx/wx.h"
#include <memory>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    frame = new Frame;
    converter = std::make_unique<Backend>();
    converter->setFrontend(frame);
    frame->setBackend(converter.get());
    frame->Show();
    return true;
}
