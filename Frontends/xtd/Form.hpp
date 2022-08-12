#pragma once
#include <xtd/xtd>

class Form: public xtd::forms::form {
public:
    Form();

private:
    xtd::forms::text_box text_box;
    xtd::forms::vertical_layout_panel panel;
};
