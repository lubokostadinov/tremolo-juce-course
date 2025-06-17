juce_add_gui_app(Coordinates
  PRODUCT_NAME "CoordinatesExample"
)
target_compile_definitions(Coordinates
    PRIVATE
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Coordinates,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Coordinates,JUCE_VERSION>")
target_sources(Coordinates PRIVATE ../Main.cpp)

target_link_libraries(Coordinates PRIVATE juce::juce_gui_basics)

target_include_directories(Coordinates PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})