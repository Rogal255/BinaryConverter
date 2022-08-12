find_package(xtd REQUIRED)
add_sources(main.cpp Form.cpp ${BACKEND_SRC})
target_type(GUI_APPLICATION)
