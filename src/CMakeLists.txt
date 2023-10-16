set(sources
#dlpno_gpu.cpp
test.cpp
cxx_module.cpp
)

include_directories("."
                   )

add_library(base OBJECT ${sources})
