cmake_minimum_required(VERSION 4.2)

project(Ray_tracer_in_weekend VERSION 1 LANGUAGES CXX)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB HEADER_FILES "*.h")

add_executable(
  raytracer
  main.cpp
  ${HEADER_FILES}
)

add_custom_target(
  run
  COMMAND $<TARGET_FILE:raytracer> > pic.ppm
  DEPENDS raytracer
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running Ray Tracer"
)

add_custom_target(
  view
  COMMAND feh pic.ppm
  DEPENDS run
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Opening Image"
)


