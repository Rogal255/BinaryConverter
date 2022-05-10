#include "App.hpp"
#include "Converter.hpp"
#include "Frame.hpp"
#include <memory>
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    converter->setFrontend(frame.get());
    frame->setBackend(converter.get());
    frame->Show();
    return true;
}
