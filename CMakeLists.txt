cmake_minimum_required(VERSION 3.20)

project(CppDesignPatterns
  VERSION 0.1.0
  DESCRIPTION "Toy project where to try different implementations of Design Patterns"
  LANGUAGES CXX)

include(cmake/mainSetup.cmake)

add_subdirectory(creational)

include(cmake/printSummary.cmake)
