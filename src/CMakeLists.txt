set(sources
#dlpno_gpu.cpp
test.cpp
)

include_directories(".")

add_library(base OBJECT ${sources})
