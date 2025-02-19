# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/subtitle-creation_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/subtitle-creation_autogen.dir/ParseCache.txt"
  "subtitle-creation_autogen"
  )
endif()
