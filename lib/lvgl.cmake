set(LV_CONF_BUILD_DISABLE_DEMOS 1)
set(LV_CONF_BUILD_DISABLE_EXAMPLES 1)
set(LV_CONF_PATH
    ${PROJECT_SOURCE_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

# v9.1.0
FetchContent_Declare(lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG v9.1.0
)
FetchContent_MakeAvailable(lvgl)

add_library(lib::lvgl ALIAS lvgl)

target_compile_options(lvgl
    PUBLIC
        -Wno-conversion
        -Wno-sign-conversion
        -Wno-type-limits
        -Wno-unused-parameter
)
set_source_files_properties(${LV_CONF_PATH} PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-sign-conversion")

target_include_directories(lvgl
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)
