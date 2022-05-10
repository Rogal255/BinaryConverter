#include "App.hpp"
#include "Converter.hpp"
#include "Frame.hpp"
#include <memory>
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    frame = new Frame;
    converter = std::make_unique<Converter>();
    converter->setFrontend(frame);
    frame->setBackend(converter.get());
    frame->Show();
    return true;
}
