ENABLE_LANGUAGE(Fortran)
SET(OSC2U_SRC osc2u.f pdg2ityp.f vni_procev.f blockres.f dectim.f gnuranf.f)
ADD_EXECUTABLE(osc2u ${OSC2U_SRC})
INSTALL(TARGETS osc2u DESTINATION osc2u)