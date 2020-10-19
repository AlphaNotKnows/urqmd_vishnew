# ===========================================================================
#  Makefile UrQMD                                    Henning Weber 10.09.1996
#                                                  Bjoern Baeuchle 21.08.2008
#                                                  Bjoern Baeuchle 18.10.2013
#                                                  Bjoern Baeuchle 09.01.2014
# ===========================================================================
#
#?  Usage: (g)make [all]      compile the whole project
#?                 install    make all and copy binary to $INSTPATH
#?                 clean      remove objectfiles in obj_$TYPE
#?                 distclean  remove all objectfiles and binaries
#?                 help       Prints this message.
#?                 lhc        compile executable suitable for calculations at
#?  			      high energies
#?
#? Define the following variables in your shell to change the behaviour of
#? compilation:
#?       TYPE = Architecture. Effects the name of object files.  [`uname -m`]
#?       OS   = Operating System. Make sure there is a file named mk/$(OS).mk
#?              containing OS-specific definitions for compiling.   [`uname`]
#?
#? If you want to compile UrQMD using the Intel Fortran Compiler ifort,
#? specify
#?       OS = Intel
#?
#? The following variables only need to be defined, their value is ignored:
#?       DEBUG          Create debuggable objects
#?       PROFILER       Create profilable objects
#?       WARN           Produce warnings when compiling
#?
#? For explanations on how to extend this Makefile, please refer to its
#? source code (all lines starting with "#++")

# -------------------------------- STRUCTURE --------------------------------

# This Makefile is structured as follows:
#    First, important variables are defined
#    Second, the files involved are listed
#    Third come the rules for compiling
#    At last, dependencies are listed.

# If you need to add local changes that you will not publish, you are
# encouraged to put them between the 1st and 2nd section.
# The sections are seperated by one line like this:

# -------------------------- VARIABLE DEFINITIONS ---------------------------

# Define variables with OS-name and Architecture if they are not defined
# already
OS   ?= $(shell uname)
TYPE ?= $(lastword $(shell uname -m))
# Your make doesn't know lastword? Shame, really. Oh well:
ifeq "$(TYPE)" ""
 TYPE = $(shell uname -m)
endif


#++ if you want to add support for a different Operating System (OS), please
#++ create a new file in directory "mk/". The name should correspond to what
#++ the command 'uname' returns on that system and end with ".mk" (so, for
#++ linux, the file is called "mk/Linux.mk").
#++
#++ The file should define the variables FC, LD and possibly also FFLAGS,
#++ LDFLAGS and SYSTEMFILES.
include mk/$(OS).mk

# other variables:
# this is the directory in which the object files are stored
OBJDIR   = obj_$(TYPE)
TARGET   = $(MAIN).$(TYPE)
LHCTARGET= $(TARGET).lhc
INSTPATH = $(HOME)/.local/bin.$(TYPE)

# ------------------- PLEASE PUT YOUR LOCAL CHANGES HERE --------------------

# -------------------------------- FILE LIST --------------------------------

# $(SYSTEMFILES) is defined in mk/*.mk
MAIN = urqmd

#++ These are the source files that contain executable code, i.e., all those
#++ that will be compiled into object files. If you add a file here, be sure
#++ to include the right dependencies of that file in the list under
#++ "Dependencies" at the end of the file (see explanations there).
#++ Please try to keep this list alphabetically sorted.
SRC = 1fluid.f addpart.f angdis.f anndec.f bessel.f blockres.f boxprg.f \
      cascinit.f CFmax.f90 coload.f cornelius.f90 dectim.f delpart.f detbal.f dwidth.f error.f \
      getmass.f getspin.f hepnam.f hepchg.f hepcmp.f init.f input.f iso.f \
      ityp2pdg.f jdecay2.f make22.f numrec.f output.f paulibl.f proppot.f \
      pythia6409.f quadri.f90 saveinfo.f scatter.f siglookup.f string.f tabinit.f \
      uhmerge.f upmerge.f whichres.f $(MAIN).f $(SYSTEMFILES)

# This turns e.g. urqmd.f into $(OBJDIR)/urqmd.o
OBJECTS  = $(addprefix $(OBJDIR)/, $(addsuffix .o, \
           $(basename $(SRC))))

# name of the spline tables
TABLE = tables.dat

# ---------------------------------- RULES ----------------------------------

# This tells make how to compile the object files.
# First, we check if $(OBJDIR) is a directory, and create it if it isn't.
# Then comes the actual compiling.
$(OBJDIR)/%.o: %.f $(OBJDIR)/dir
	$(FC) $(FFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.f90 $(OBJDIR)/dir
	$(FC) $(FFLAGS) -c $< -o $@

# Those targets do not produce a file with its name
.PHONY: all clean distclean install jalhc nolhc

all: nolhc $(TARGET)    $(TABLE) inputfile
	@echo "UrQMD executable $(TARGET) created, please do not use for calculations at LHC energies (instead, compile with make lhc)"
lhc: jalhc $(LHCTARGET) $(TABLE) inputfile
	@echo "LHC-abled executable $(LHCTARGET) created"

inputfile: inputfile.example
	cp -i $^ $@

# $(OBJDIR)/dir is a dummy file that we can use to check whether the
# directory exists. (Before, for each object we checked again. Now, we
# only check once and then only implicitly in make's rules).
#
# If $(OBJDIR) is created and $(OBJDIR)/dir does not exist, there will
# be no objects in that directory either, because, well, make creates
# the file during compilation.
$(OBJDIR)/dir:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@touch $@

#++ Here the target is made. If you want other object-files to be linked,
#++ please include the corresponding source-code file in the "SRC =" list.
$(TARGET) $(LHCTARGET): $(OBJECTS)
	$(LD) $^ $(LDFLAGS) -o $@
#++ Applies lhc-patch and saves file lhc. Then, runqmd.bash is adapted.
jalhc:
	if [ ! -e lhc ]; then patch -p0 < lhc.patch || true; fi
	touch lhc
nolhc:
	if [ -e lhc ]; then patch -R -p0 < lhc.patch || true; fi
	rm -f lhc

# create tables with helper script maketables:
$(TABLE): $(SRC)
	./maketables $(TABLE)

# other targets:
help:
	@grep -h "^#?" $(MAKEFILE_LIST)
clean:
	@for i in $(OBJECTS) loadmap.out $(TABLE); do if [ -e $$i ]; then echo "rm $$i"; rm $$i; else true; fi; done
distclean: clean
	@for i in $(TARGET) $(LHCTARGET) obj_* *~; do if [ -e $$i ]; then echo "rm $$i"; rm -r $$i; else true; fi; done
install: $(TARGET)
	cp $< $(INSTPATH)/$(basename $<)
	strip $(INSTPATH)/$(basename $<)

# ------------------------------ DEPENDENCIES -------------------------------

#++ Dependencies of a file are all those files that are *included* by the
#++ corresponding source file.
#++ To reference the object files, please prepend "$(OBJDIR)/" to the
#++ source file name and replace the ".f" by ".o".
$(OBJDIR)/1fluid.o:    options.f defs.f cornelius.f90 quadri.f90
$(OBJDIR)/addpart.o:   coms.f freezeout.f newpart.f
$(OBJDIR)/angdis.o:    coms.f
$(OBJDIR)/anndec.o:    comres.f comwid.f options.f newpart.f
$(OBJDIR)/blockres.o:  comres.f
$(OBJDIR)/boxprg.o:    boxinc.f coms.f comres.f options.f
$(OBJDIR)/cascinit.o:  coms.f inputs.f options.f
$(OBJDIR)/coload.o:    boxinc.f colltab.f coms.f comres.f newpart.f options.f
$(OBJDIR)/dectim.o:    coms.f colltab.f options.f
$(OBJDIR)/delpart.o:   coms.f comres.f freezeout.f options.f newpart.f
$(OBJDIR)/detbal.o:    coms.f comres.f comwid.f newpart.f options.f
$(OBJDIR)/dwidth.o:    coms.f comres.f comwid.f options.f
$(OBJDIR)/getmass.o:   comnorm.f comres.f
$(OBJDIR)/getspin.o:   comres.f
$(OBJDIR)/init.o:      boxinc.f colltab.f coms.f comres.f freezeout.f inputs.f \
                       newpart.f options.f
$(OBJDIR)/input.o:     boxinc.f coms.f comres.f inputs.f options.f
$(OBJDIR)/ityp2pdg.o:  comres.f
$(OBJDIR)/iso.o:       comres.f newpart.f
$(OBJDIR)/jdecay2.o:   newpart.f
$(OBJDIR)/make22.o:    comres.f coms.f comwid.f newpart.f options.f
$(OBJDIR)/output.o:    boxinc.f coms.f comres.f freezeout.f inputs.f newpart.f \
                       options.f
$(OBJDIR)/paulibl.o:   coms.f comres.f options.f
$(OBJDIR)/proppot.o:   boxinc.f coms.f options.f
$(OBJDIR)/saveinfo.o:  coms.f
$(OBJDIR)/scatter.o:   boxinc.f coms.f comres.f freezeout.f newpart.f options.f
$(OBJDIR)/siglookup.o: comres.f
$(OBJDIR)/string.o:    comres.f comstr.f options.f
$(OBJDIR)/tabinit.o:   comres.f comwid.f
$(OBJDIR)/uhmerge.o:   boxinc.f colltab.f coms.f comres.f inputs.f itypdata.f \
                       freezeout.f newpart.f options.f defs.f CFmax.f90
$(OBJDIR)/upmerge.o:   newpart.f options.f
$(OBJDIR)/$(MAIN).o:   boxinc.f colltab.f coms.f comres.f inputs.f newpart.f \
                       options.f
$(OBJDIR)/whichres.o:  comres.f options.f
