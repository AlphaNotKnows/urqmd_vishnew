#!/bin/sh

run=${1-nothing}
exename="urqmd"

export ftn09=input_initial
export ftn13=test.f13
export ftn14=urqmd_result14
export ftn15=test.f15
export ftn16=test.f16
export ftn19=urqmd_result19
export ftn20=test.f20

rm test*

# check if file lhc exists, or if user specifically asked for lhc run:
if [ -e lhc ] && [ "$run" != "all" ] || [ "$run" = "lhc" ]; then
        if [ -x $exename.lhc ]; then
                echo "Running the LHC version of UrQMD"
        	time ./$exename.lhc
        else
                echo "LHC executable not found, please compile with 'make lhc' first"
                exit 1
        fi
else
        if [ -x $exename ]; then
                echo "Running UrQMD"
                time ./$exename
        else
                echo "UrQMD executable not found, please compile with 'make' first"
                exit 1
        fi
fi
