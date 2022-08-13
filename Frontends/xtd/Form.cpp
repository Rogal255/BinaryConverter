#include "Form.hpp"
#include <xtd/xtd>

Form::Form() {
    this->text("Binary converter");
    this->client_size({550, 750});
    this->minimum_client_size({300, 500});
    this->maximize_box(false);
    this->controls().push_back(scene_);

    scene_.back_color(xtd::drawing::colors::aquamarine());
    scene_.dock(xtd::forms::dock_style::fill);
    scene_.padding(xtd::forms::padding(10));
    scene_.controls().push_back_range({inputBox_, resultsBox_});
    scene_.control_layout_style(inputBox_, {75, xtd::forms::size_type::absolute, true});
    scene_.control_layout_style(resultsBox_, {75, xtd::forms::size_type::absolute, true});

    inputBox_.back_color(xtd::drawing::colors::light_green());
    inputBox_.text("Lorem ipsum...");
    inputBox_.font(xtd::drawing::font(inputBox_.font(), 30));

    resultsBox_.back_color(xtd::drawing::colors::blue_violet());
    resultsBox_.text("Results");

};
