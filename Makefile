INSTALL := /usr/local/cs2110-tools

all :
	mkdir $(INSTALL)/include
	install -m 0644 debugging.h $(INSTALL)/include
	install -m 0644 libgbaio.a $(INSTALL)/lib
