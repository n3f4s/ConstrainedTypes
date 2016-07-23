# Define and set project agnostic config

set(CMAKE_USE_RELATIVE_PATHS TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.so)

