#pragma once
#include <xtd/xtd>

class Form: public xtd::forms::form {
public:
    Form();

private:
    xtd::forms::vertical_layout_panel scene_;
    xtd::forms::horizontal_layout_panel resultsBoxPanel_;
    xtd::forms::horizontal_layout_panel optionsPanel_;
    xtd::forms::horizontal_layout_panel inputBaseBoxPanel_;
    xtd::forms::vertical_layout_panel optionsButtonsPanel_;
    xtd::forms::panel optionsSpacerPanel_;

    xtd::forms::text_box inputBox_;
    xtd::forms::group_box resultsBox_;
    xtd::forms::group_box inputBaseBox_;
    xtd::forms::button saveButton_;
    xtd::forms::button clearButton_;
    xtd::forms::label resultLabel1_;
    xtd::forms::label resultLabel2_;
    xtd::forms::text_box resultBox1_;
    xtd::forms::text_box resultBox2_;

    xtd::forms::radio_button decRadioButton_;
    xtd::forms::radio_button binRadioButton_;
    xtd::forms::radio_button hexRadioButton_;
    xtd::forms::horizontal_layout_panel radioButtonsPanel_;
};
