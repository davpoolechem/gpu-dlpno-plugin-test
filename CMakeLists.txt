#=======================#
#== Base project info ==#
#=======================#
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# note: project name needs to be consistent with library dir/name in Psi4
project(gpu_dlpno_ccsd VERSION 0.1 LANGUAGES CXX) 

set(gpu_dlpno_ccsd_AUTHORS      "David Poole")
set(gpu_dlpno_ccsd_DESCRIPTION  "GPU-accelerated DLPNO-CCSD plugin to Psi4")
set(gpu_dlpno_ccsd_URL          "github.com/davpoolechem/gpu_dlpno_ccsd")
set(gpu_dlpno_ccsd_LICENSE      "GPL 2+")

#======================#
#== setup base flags ==# 
#======================#
set(CMAKE_CXX_STANDARD 17)
set(POSITION_INDEPENDENT_CODE True)
set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS} -fPIC")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -fmax-errors=10")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-misleading-indentation -Werror=pedantic -pedantic-errors -fmax-errors=10")
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#=========================================================#
#==               setup psi4-specific opts              ==# 
#== PYMOD_INSTALL_*DIR ultimately controls where plugin ==#
#==     is installed within Psi4 directory structure    ==#
#=========================================================#
find_package(psi4)
include(psi4OptionsTools)

# note: needs to be here to have correct lib/${PN} name
set(PN ${PROJECT_NAME})

# install alongside psi4 module by default, but overrideable
get_filename_component(psi4_CMAKE_INSTALL_PREFIX ${psi4_INCLUDE_DIR} DIRECTORY)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${psi4_CMAKE_INSTALL_PREFIX} CACHE PATH "Install path" FORCE)
endif()
message(STATUS "${PN} plugin install prefix: ${CMAKE_INSTALL_PREFIX}")

# define install location of plugin within Psi4 directory
if(PYMOD_INSTALL_LIBDIR)
    set(PYMOD_INSTALL_FULLDIR "${CMAKE_INSTALL_LIBDIR}${PYMOD_INSTALL_LIBDIR}/${PN}")
else()
    file(RELATIVE_PATH _tmp ${psi4_CMAKE_INSTALL_PREFIX} ${psi4_LIBRARY})
    #   e.g., _tmp = lib/psi4/core.so
    get_filename_component(_tmp2 ${_tmp} DIRECTORY)
    get_filename_component(_tmp3 ${_tmp2} DIRECTORY)
    set(PYMOD_INSTALL_FULLDIR "${_tmp3}/${PN}")
endif()
message(STATUS "${PN} plugin module install: ${PYMOD_INSTALL_FULLDIR}")

#===============================#
#== setup include directories ==#
#===============================#
#include_directories( SYSTEM
#                     ${PROJECT_SOURCE_DIR}/src/
#                     ${PYTHON_INCLUDE_DIRS} # for python module
#                     ${pybind11_INCLUDE_DIRS} # for python module
#                     ${psi4_INCLUDE_DIR} # for psi4 include files
#                   )
message("Python include dir #1: ${PYTHON_INCLUDE_DIR}")

#===================#
#== step into src ==#
#===================#
add_subdirectory(src)

#===================================#
#== set targets and build library ==#
#===================================#
set(targets
 $<TARGET_OBJECTS:base>
)

add_library(gpu_dlpno_ccsd SHARED
  ${targets}
)

# we need the library name to be gpu_dlpno_ccsd.so, not libgpu_dlpno_ccsd.so
set_target_properties(gpu_dlpno_ccsd PROPERTIES PREFIX "")
target_link_libraries(gpu_dlpno_ccsd PRIVATE ${PYTHON_LIBRARIES})

# seems to be needed to set up __init__.py correctly
configure_file(__init__.py.in __init__.py @ONLY)

#==============================#
#== install plugin into psi4 ==# 
#==============================#
install (TARGETS gpu_dlpno_ccsd DESTINATION ${PYMOD_INSTALL_FULLDIR})

install(FILES pymodule.py README.md
              __init__.py
        DESTINATION ${PYMOD_INSTALL_FULLDIR})
