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

BIN       := ep1
TARF      := leonardo.lana.joao.daniel
FINALDIR  := leonardo.lana.joao.daniel

CFLAGS    := -std=c++1z -fopenmp
LDFLAGS   := -I $(INCDIR) -lpthread
