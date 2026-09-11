file(GLOB_RECURSE UI_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ui/*.c
)

idf_component_register(SRCS "main.c" "ui_app.c" ${UI_SOURCES}
                       INCLUDE_DIRS "." "ui")
