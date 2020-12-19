# ENABLE_LANGUAGE(Fortran)
# SET(CMAKE_Fortran_FLAGS "-O3 -cpp -lm -lz -fno-align-commons")
# SET(VISHNEW_SRC VISH2p1V1.10.0.for PhyBdary-1.10.for InputEOS-1.3.for OSCARoutput.for Arsenal-0.8.for Initialization-1.03.for InputFun-1.29RC6.for  cornelius2.f90 )
# SET (JETSRC Jetoutputh5.for)
# ADD_LIBRARY (JET ${JETSRC})
# ADD_EXECUTABLE(VISHNew ${VISHNEW_SRC} )
# FIND_PACKAGE(HDF5 REQUIRED)
# TARGET_INCLUDE_DIRECTORIES(VISHNew  PRIVATE ${HDF5_INCLUDE_DIRS})
# TARGET_LINK_LIBRARIES(VISHNew ${HDF5_Fortran_LIBRARIES} ${HDF5_Fortran_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} JET)
# INSTALL(TARGETS VISHNew DESTINATION VISHNew)
# INSTALL(FILES extraParas.inp Vishydro.inp DESTINATION VISHNew)
# INSTALL(DIRECTORY EOS DESTINATION VISHNew)


message("Looking for HDF5 ...")
find_package(HDF5)
if(${HDF5_FOUND})
    include_directories(${HDF5_INCLUDE_DIRS})
    set(_hdf5_libs ${HDF5_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_HL_LIBRARIES})
endif(${HDF5_FOUND})

# FFLAGS depend on the compiler
if (${HDF5_FOUND})
  set (CMAKE_Fortran_COMPILER "h5fc")
endif (${HDF5_FOUND})
get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)

if (Fortran_COMPILER_NAME MATCHES "gfortran.*")
  # gfortran
  set (CMAKE_Fortran_FLAGS_RELEASE "-O3 -cpp -fno-align-commons")
  set (CMAKE_Fortran_FLAGS_DEBUG   "-O0 -g -cpp")
elseif (Fortran_COMPILER_NAME MATCHES "ifort.*")
  # ifort (untested)
  set (CMAKE_Fortran_FLAGS_RELEASE "-O3 -cpp -heap-arrays")
  set (CMAKE_Fortran_FLAGS_DEBUG   "-O0 -g -cpp -heap-arrays")
elseif (Fortran_COMPILER_NAME MATCHES "h5fc")
  set (CMAKE_Fortran_FLAGS_RELEASE "-O3 -cpp -lm -lz -fno-align-commons")
  set (CMAKE_Fortran_FLAGS_DEBUG   "-O0 -g -cpp")
else (Fortran_COMPILER_NAME MATCHES "gfortran.*")
  message ("CMAKE_Fortran_COMPILER full path: " ${CMAKE_Fortran_COMPILER})
  set (CMAKE_Fortran_FLAGS_RELEASE "-O3 -cpp -fno-align-commons")
  set (CMAKE_Fortran_FLAGS_DEBUG   "-O0 -g -cpp")
endif (Fortran_COMPILER_NAME MATCHES "gfortran.*")
set (LIBSRC Jetoutputh5.for)
add_library (hdf5 ${LIBSRC})
add_executable(VISHNew
  VISH2p1V1.10.0.for 
  PhyBdary-1.10.for 
  InputEOS-1.3.for 
  OSCARoutput.for 
  Arsenal-0.8.for 
  Initialization-1.03.for
  InputFun-1.29RC6.for 
  cornelius2.f90
  )
target_link_libraries (VISHNew hdf5)
set_target_properties (VISHNew PROPERTIES COMPILE_FLAGS "-DUSE_HDF5")
INSTALL(TARGETS VISHNew DESTINATION VISHNew)
INSTALL(FILES extraParas.inp Vishydro.inp DESTINATION VISHNew)
INSTALL(DIRECTORY EOS DESTINATION VISHNew)