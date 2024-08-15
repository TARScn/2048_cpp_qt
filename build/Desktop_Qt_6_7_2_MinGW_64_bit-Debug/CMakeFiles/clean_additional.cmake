# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\samp_3_1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\samp_3_1_autogen.dir\\ParseCache.txt"
  "samp_3_1_autogen"
  )
endif()
