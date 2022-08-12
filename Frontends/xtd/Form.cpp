#include "Form.hpp"
#include <xtd/xtd>

Form::Form() {
    this->text("Binary converter");
    this->client_size({550, 750});
    this->maximize_box(false);
    this->minimize_box(false);
    panel.parent(*this);
    panel.controls().push_back_range({text_box});
    panel.padding(xtd::forms::padding(10));
    panel.control_layout_style(text_box, {75, xtd::forms::size_type::absolute, true});
    text_box.text("Lorem ipsum...");
    text_box.font(xtd::drawing::font(text_box.font(), 30));
    panel.dock(xtd::forms::dock_style::fill);
};
