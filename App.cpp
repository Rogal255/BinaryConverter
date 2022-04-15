#include "App.hpp"
#include "Converter.hpp"
#include "Frame.hpp"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    frame = new Frame();
    converter = new Converter(frame);
    frame->setBackend(converter);
    frame->Show();
    return true;
}
