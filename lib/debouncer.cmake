# No version
FetchContent_Declare(Button_Debouncer
    GIT_REPOSITORY https://github.com/tcleg/Button_Debouncer.git
    GIT_TAG 7d99c450bc85608358b8492a361fad4289831d2c
)
FetchContent_MakeAvailable(Button_Debouncer)

add_library(Button_Debouncer
    ${button_debouncer_SOURCE_DIR}/C++/button_debounce.cpp
)
add_library(lib::debouncer ALIAS Button_Debouncer)

target_compile_options(Button_Debouncer
    PUBLIC
        -Wno-conversion
)

target_include_directories(Button_Debouncer
    PUBLIC
    ${button_debouncer_SOURCE_DIR}/C++
)
