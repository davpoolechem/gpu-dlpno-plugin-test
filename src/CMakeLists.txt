set(sources
#dlpno_gpu.cpp
test.cpp
cxx_module.cpp
)

include_directories( SYSTEM
                     "."
                     ${psi4_INCLUDE_DIR}
                     ${pybind11_INCLUDE_DIR}/pybind11 # pybind11 suffix is needed to recognize this, apparently
                     /theoryfs2/ds/dpoole34/miniconda3/envs/p4dev/include/python3.9 # hardcorded for now, to fix
                   )

message("Python include dir: ${PYTHON_INCLUDE_DIR}")

add_library(base OBJECT ${sources})
