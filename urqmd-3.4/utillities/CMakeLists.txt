ADD_EXECUTABLE(QGP_energy QGP_energy.cpp)
INSTALL(TARGETS QGP_energy DESTINATION urqmd)
INSTALL(PROGRAMS urqmd_initial.py centrality.py DESTINATION urqmd)