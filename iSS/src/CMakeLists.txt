SET(CMAKE_CXX_COMPILER g++)
FIND_PACKAGE(GSL REQUIRED)

SET (CMAKE_CXX_FLAGS "${GSL_CXX_FLAGS} -O3 -Wall")

SET(INCLUDE_DIRS ${GSL_INCLUDE_DIR})
SET(LIBS ${GSL_LIBRARIES})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})
ADD_EXECUTABLE (iSS  main.cpp   arsenal.cpp  ParameterReader.cpp  RandomVariable1DArray.cpp  RandomVariable2DArray.cpp  RandomVariable.cpp  TableFunction.cpp  Table.cpp  emissionfunction.cpp  readindata.cpp  Poisson.cpp  NBD.cpp  )
TARGET_LINK_LIBRARIES (iSS ${LIBS})

INSTALL(TARGETS iSS DESTINATION ${CMAKE_INSTALL_PREFIX}/iSS)
