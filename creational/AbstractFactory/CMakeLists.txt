add_executable(creational_abstract_factory
  abstract_factory.cpp)

if (WIN32)
    # Example from LinkedIn course "C++ Design Patterns: Creational"
    # This example is using the Windows API to change the backgroun & text color in the terminal
    add_executable(creational_abstract_factory_challenge
      challengeTerminalColors.cpp)
endif()
