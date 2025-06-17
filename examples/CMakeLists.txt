cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_POLICY_DEFAULT_CMP0141        NEW      CACHE STRING "" FORCE)

project(JucePluginDevelopmentCourseExamples VERSION 1.0.0)

if(PROJECT_IS_TOP_LEVEL)
  if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
  endif()
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded CACHE STRING "" FORCE)
endif()

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

cpmaddpackage(
  NAME
    JUCE
  GIT_TAG
    8.0.7
  GITHUB_REPOSITORY
    juce-framework/JUCE
  SOURCE_DIR
    ${LIB_DIR}/juce
)

add_subdirectory(Coordinates)