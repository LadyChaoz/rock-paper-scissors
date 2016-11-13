# Anne Warden
# CS 375 Final Project
# Makefile
CCFLAGS = `pkg-config --cflags --libs gtk+-2.0`
all:
	g++ -o referee referee.cpp
	g++ -o player player.cpp
	g++ -o gui-player gui-player.cpp ${CCFLAGS}

clean:
	rm referee player gui-player *~

submit.tar:
	tar -cvf aw308final.tar Makefile README referee.cpp player.cpp gui-player.cpp
