#include "App.hpp"
#include "Frame.hpp"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    frame = new Frame();
    frame->Show();
    return true;
}
