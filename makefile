all: 
	cd Release && make all  

# Other Targets
clean:
	cd Release && make clean   
	
install: all
	mkdir -p $(DESTDIR)${SDRROOT}/dom/components/fftlib
	install -m 664 fftlib.spd.xml $(DESTDIR)${SDRROOT}/dom/components/fftlib/fftlib.spd.xml
	mkdir -p $(DESTDIR)${SDRROOT}/dom/components/fftlib/Release
	install Release/libfftlib.so $(DESTDIR)${SDRROOT}/dom/components/fftlib/Release/libfftlib.so
	mkdir -p $(DESTDIR)${SDRROOT}/dom/components/fftlib/inc
	install -m 664 inc/*.h $(DESTDIR)${SDRROOT}/dom/components/fftlib/inc

