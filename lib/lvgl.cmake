# v9.1.0
FetchContent_Declare(lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG v9.1.0
)
FetchContent_MakeAvailable(lvgl)

add_library(lib::lvgl ALIAS lvgl)
