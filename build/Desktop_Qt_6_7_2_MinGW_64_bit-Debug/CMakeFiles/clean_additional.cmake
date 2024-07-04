# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Generals-io_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Generals-io_autogen.dir\\ParseCache.txt"
  "Generals-io_autogen"
  )
endif()
