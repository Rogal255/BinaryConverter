#include "Form.hpp"
#include <xtd/xtd>

Form::Form() {
    this->text("Binary converter");
    this->client_size({550, 750});
    this->minimum_client_size({300, 500});
    this->maximize_box(false);
    this->controls().push_back(scene_);

    scene_.dock(xtd::forms::dock_style::fill);
    scene_.padding(xtd::forms::padding(10));
    scene_.controls().push_back_range({inputBox_, resultsBox_});
    scene_.control_layout_style(inputBox_, {75, xtd::forms::size_type::absolute, true});
    scene_.control_layout_style(resultsBox_, {70, xtd::forms::size_type::absolute, true});

    inputBox_.text("Lorem ipsum...");
    inputBox_.font(xtd::drawing::font(inputBox_.font(), 30));
    resultsBox_.text("Results");
    resultsBox_.controls().push_back(resultsBoxPanel_);
    resultsBox_.padding(xtd::forms::padding(0, 0, 0, 15));
    resultsBoxPanel_.dock(xtd::forms::dock_style::fill);
    resultsBoxPanel_.padding(5);
    resultsBoxPanel_.controls().push_back_range({resultLabel1_, resultBox1_, resultLabel2_, resultBox2_});
    resultsBoxPanel_.control_layout_style(resultLabel1_, {30, xtd::forms::size_type::absolute, true});
    resultsBoxPanel_.control_layout_style(resultBox1_, {xtd::forms::size_type::auto_size, true});
    resultsBoxPanel_.control_layout_style(resultLabel2_, {30, xtd::forms::size_type::absolute, true});
    resultsBoxPanel_.control_layout_style(resultBox2_, {xtd::forms::size_type::auto_size, true});
    resultLabel1_.text("BIN");
    resultLabel2_.text("HEX");
    resultLabel1_.text_align(xtd::forms::content_alignment::middle_right);
    resultLabel2_.text_align(xtd::forms::content_alignment::middle_right);
};
