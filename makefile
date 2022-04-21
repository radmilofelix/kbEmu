all: kbEmu

kbEmu.o: kbEmu.cpp
	g++ -c kbEmu.cpp

kbScancodeEmulator.o: kbScancodeEmulator.cpp
	g++ -c kbScancodeEmulator.cpp

kbEmu: kbEmu.o kbScancodeEmulator.o
	g++ kbScancodeEmulator.o kbEmu.o -o kbEmu

clean:
	rm -rf *o kbEmu
	
install:
	cp kbEmu /usr/bin
