#include "Form.hpp"
#include <xtd/xtd>

Form::Form() {
    this->text("Hello World");
    this->client_size({640, 480});
    test_button.parent(*this);
    test_button.location({10, 10});
    test_button.text("&Click Me!");
    test_button.click += []() { xtd::forms::message_box::show("Msq box"); };
}

int main() { xtd::forms::application::run(Form()); }
