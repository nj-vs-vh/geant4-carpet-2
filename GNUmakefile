name := Carpet2
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = /media/timur1606/home/me/Soft/geant4.10.06.p03
endif

G4SYSTEM = Linux-g++

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*
