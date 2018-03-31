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
TARF      := leonardo.lana.bruno.scholl
FINALDIR  := leonardo.lana.bruno.scholl

CFLAGS    := -std=c++1z
LDFLAGS   := -I $(INCDIR) -lpthread
