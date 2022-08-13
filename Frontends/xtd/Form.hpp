#pragma once
#include <xtd/xtd>

class Form: public xtd::forms::form {
public:
    Form();

private:
    xtd::forms::vertical_layout_panel scene_;
    xtd::forms::horizontal_layout_panel resultsBoxPanel_;

    xtd::forms::text_box inputBox_;
    xtd::forms::group_box resultsBox_;
    xtd::forms::label resultLabel1_;
    xtd::forms::label resultLabel2_;
    xtd::forms::text_box resultBox1_;
    xtd::forms::text_box resultBox2_;
};
