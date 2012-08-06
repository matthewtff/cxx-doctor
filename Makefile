all: external doctor

external: koohar oodb
	cp external/koohar/src/libkoohar* external/lib/
	cp external/oodb/src/liboodb* external/lib/

koohar:
	make -C external/koohar/src -j3 static

oodb:
	make -C external/oodb/src -j3 static

doctor:
	make -C src/

clean: external-clean doctor-clean

external-clean: koohar-clean oodb-clean
	rm external/lib/*

koohar-clean:
	make -C external/koohar/src clean

oodb-clean:
	make -C external/oodb/src clean

doctor-clean:
	make -C src/ clean

rebuild: clean all
