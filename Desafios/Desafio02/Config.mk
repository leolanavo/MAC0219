# Configuration file for the makefile

###################################################
# BIN -> binaries                                 #
# CFLAGS -> compilation flags                     #
# LDFLAGS -> linker flags                         #
# FINALDIR -> the name of the directory that will #
#             be compressed in .tar.gz            #
# TARF -> the name of the .tar.gz file            #
#                                                 #
###################################################

BIN       := a.out
COMPF     := leonardo.lana.bruno.scholl
COMPEXT   := zip
FINALDIR  := leonardo.lana.bruno.scholl

CFLAGS    := -std=c++1z -O0
LDFLAGS   := -I $(INCDIR) -lpthread
