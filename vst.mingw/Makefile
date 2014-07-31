#========================================
# S e t t i n g s
#========================================
CROSS = wine
CC = $(CROSS) g++.exe
DYN = .dll
EXT = 
SRC = ../vst.src/
VST = /usr/local/lib/vstsdk2.4/
SDK = $(VST)public.sdk/source/vst2.x/
FFLAGS = -fmessage-length=0 -finline-functions -fno-exceptions -fno-rtti
MFLAGS = -mmmx
CFLAGS = -Wall -Os -s -c $(MFLAGS) $(FFLAGS) -I$(VST) -I$(SDK)
LFLAGS = -Wall -s -shared -static exports.def

#========================================
# O b j e c t s
#========================================
# (common)
#----------------------------------------
OBJM = vstplugmain
OBJA = audioeffect
OBJX = audioeffectx
OBJC = $(OBJM).o $(OBJA).o $(OBJX).o

$(OBJM).o : $(SDK)$(OBJM).cpp
	$(CC) $(CFLAGS) $(SDK)$(OBJM).cpp
	
$(OBJX).o : $(SDK)$(OBJX).cpp
	$(CC) $(CFLAGS) $(SDK)$(OBJX).cpp
	
$(OBJA).o : $(SDK)$(OBJA).cpp
	$(CC) $(CFLAGS) $(SDK)$(OBJA).cpp
#----------------------------------------
# (output)
#----------------------------------------
OBJE = BoostComp
	 
OBJD = $(OBJE:=$(DYN))

#========================================
# B u i l d
#========================================
# all / clean
#----------------------------------------
all: $(OBJE)

clean:
	rm -f *.o $(OBJD)
	
cleanobj:
	rm -f *.o
#----------------------------------------
# individual
#----------------------------------------
BoostComp: $(OBJC) BoostComp.o
	$(CC) $(LFLAGS) $(OBJC) BoostComp.o -o BoostComp$(DYN)
BoostComp.o: $(SRC)BoostComp.cpp $(SRC)BoostComp.h
	$(CC) $(CFLAGS) $(SRC)BoostComp.cpp
