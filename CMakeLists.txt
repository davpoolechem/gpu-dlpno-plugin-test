#=======================#
#== Base project info ==#
#=======================#
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(gpu-dlpno-plugin-test VERSION 0.1 LANGUAGES CXX) 

set(gpu-dlpno-plugin-test_AUTHORS      "David Poole")
set(gpu-dlpno-plugin-test_DESCRIPTION  "GPU-accelerated DLPNO-CCSD plugin to Psi4")
set(gpu-dlpno-plugin-test_URL          "github.com/davpoolechem/gpu-dlpno-plugin-test")
set(gpu-dlpno-plugin-test_LICENSE      "GPL 2+")

#======================#
#== setup base flags ==# 
#======================#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -fmax-errors=10")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-misleading-indentation -Werror=pedantic -pedantic-errors -fmax-errors=10")
endif()

#=========================================================#
#==               setup psi4-specific opts              ==# 
#== PYMOD_INSTALL_*DIR ultimately controls where plugin ==#
#==     is installed within Psi4 directory structure    ==#
#=========================================================#
find_package(psi4)
include(psi4OptionsTools)

# needs to be here to have correct lib/${PN} name
set(PN ${PROJECT_NAME})

#   install alongside psi4 module by default, but overrideable
get_filename_component(psi4_CMAKE_INSTALL_PREFIX ${psi4_INCLUDE_DIR} DIRECTORY)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${psi4_CMAKE_INSTALL_PREFIX} CACHE PATH "Install path" FORCE)
endif()
message(STATUS "--${PN} plugin install prefix: ${CMAKE_INSTALL_PREFIX}")

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
message(STATUS "-- ${PN} plugin module install: ${PYMOD_INSTALL_FULLDIR}")

#==================#
#== setup python ==# 
#==================#
include_directories(${PYTHON_INCLUDE_DIRS})

#=====================================#
#== setup other include directories ==#
#=====================================#
include_directories( SYSTEM
                     ${PROJECT_SOURCE_DIR}/src/
                   )

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

add_library(gpu-dlpno-plugin-test SHARED
  ${targets}
)

#==============================#
#== install plugin into psi4 ==# 
#==============================#
install (TARGETS gpu-dlpno-plugin-test DESTINATION ${PYMOD_INSTALL_FULLDIR})

install(FILES pymodule.py README.md
              __init__.py
        DESTINATION ${PYMOD_INSTALL_FULLDIR})

#target_link_libraries(gpu_dfcc
#  ${PYTHON_LIBRARIES}
#  cublas
#  cusolver
#  cudart
#  psi4::core    )
#include(CMakePackageConfigHelpers)
#set_target_properties(gpu_dfcc PROPERTIES PREFIX "")

#get_filename_component(psi4_CMAKE_INSTALL_PREFIX ${psi4_INCLUDE_DIR} DIRECTORY)
#if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#    set(CMAKE_INSTALL_PREFIX ${psi4_CMAKE_INSTALL_PREFIX} CACHE PATH "Install path" FORCE)
#endif()
#message(STATUS "Plugin install prefix: ${CMAKE_INSTALL_PREFIX}")

#if(PYMOD_INSTALL_LIBDIR)
#    set(PYMOD_INSTALL_FULLDIR "${CMAKE_INSTALL_LIBDIR}${PYMOD_INSTALL_LIBDIR}/${PN}")
#else()
#    file(RELATIVE_PATH _tmp ${psi4_CMAKE_INSTALL_PREFIX} ${psi4_LIBRARY})
#    #   e.g., _tmp = lib/psi4/core.so
#    get_filename_component(_tmp2 ${_tmp} DIRECTORY)
##    get_filename_component(_tmp3 ${_tmp2} DIRECTORY)
#    set(PYMOD_INSTALL_FULLDIR "${_tmp3}/${PN}")
#endif()
#message(STATUS "Plugin module install: ${PYMOD_INSTALL_FULLDIR}")
#
#configure_file(__init__.py.in __init__.py @ONLY)

# <<<  Install  >>>

#install(TARGETS gpu_dfcc
#        EXPORT "${PN}Targets"
#        LIBRARY DESTINATION ${PYMOD_INSTALL_FULLDIR})

#install(FILES extras.py GPUtil.py pymodule.py LICENSE README.md
#        ${CMAKE_CURRENT_BINARY_DIR}/__init__.py
#        DESTINATION ${PYMOD_INSTALL_FULLDIR})

#install(DIRECTORY tests/
#        DESTINATION ${PYMOD_INSTALL_FULLDIR}/tests
#        FILES_MATCHING PATTERN "gpu_dfcc*/input.dat"
#                       PATTERN "*.py"
#        PATTERN "old-tests" EXCLUDE)

# <<< Export Config >>>

# GNUInstallDirs "DATADIR" wrong here; CMake search path wants "share".
#set(CMAKECONFIG_INSTALL_DIR "share/cmake/${PN}")
#configure_package_config_file(cmake/${PN}Config.cmake.in
#                              "${CMAKE_CURRENT_BINARY_DIR}/${PN}Config.cmake"
#                              INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})
#write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PN}ConfigVersion.cmake
#                                 VERSION ${${PN}_VERSION}
#                                 COMPATIBILITY AnyNewerVersion)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PN}Config.cmake
#              ${CMAKE_CURRENT_BINARY_DIR}/${PN}ConfigVersion.cmake
#        DESTINATION ${CMAKECONFIG_INSTALL_DIR})
#install(EXPORT "${PN}Targets"
#        NAMESPACE "${PN}::"
#DESTINATION ${CMAKECONFIG_INSTALL_DIR})
