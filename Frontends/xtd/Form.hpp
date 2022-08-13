#pragma once
#include <xtd/xtd>

class Form: public xtd::forms::form {
public:
    Form();

private:
    xtd::forms::vertical_layout_panel scene_;

    xtd::forms::text_box inputBox_;
    xtd::forms::group_box resultsBox_;
};
