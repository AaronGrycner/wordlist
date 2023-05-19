# CMakeList.txt : CMake project for wordlist, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (wordlist "Wordlist.cpp" "Driver.cpp" "Cmd.cpp" "Iterators.cpp" "Reader.cpp" "WordGen.cpp"
"Wordlist.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET wordlist PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
