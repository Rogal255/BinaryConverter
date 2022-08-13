#include "Form.hpp"
#include <xtd/xtd>

Form::Form() {
    this->text("Binary converter");
    this->client_size({550, 750});
    this->minimum_client_size({300, 500});
    this->maximize_box(false);
    this->controls().push_back(scene_);

    scene_.controls().push_back_range({inputPanel_, resultsPanel_});
    scene_.back_color(xtd::drawing::colors::aquamarine());
    scene_.dock(xtd::forms::dock_style::fill);
    scene_.padding(xtd::forms::padding(10));
    scene_.control_layout_style(inputPanel_, {95, xtd::forms::size_type::absolute, true});
    scene_.control_layout_style(resultsPanel_, {95, xtd::forms::size_type::absolute, true});

    inputPanel_.back_color(xtd::drawing::colors::light_green());
    inputPanel_.controls().push_back(inputBox_);
    inputPanel_.control_layout_style(inputBox_, {xtd::forms::size_type::auto_size, true});
    inputPanel_.dock(xtd::forms::dock_style::fill);
    inputBox_.text("Lorem ipsum...");
    inputBox_.font(xtd::drawing::font(inputBox_.font(), 30));

    resultsPanel_.back_color(xtd::drawing::colors::blue_violet());
    resultsPanel_.controls().push_back(resultsBox_);
    resultsPanel_.control_layout_style(resultsBox_, {xtd::forms::size_type::auto_size, true});
    resultsPanel_.dock(xtd::forms::dock_style::fill);
    resultsBox_.text("Results");

};
