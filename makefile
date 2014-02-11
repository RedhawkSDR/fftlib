all: 
	cd Release && make all  

# Other Targets
clean:
	cd Release && make clean   
	
install: all
	mkdir -p ${SDRROOT}/dom/components/fftlib
	install -m 664 fftlib.spd.xml ${SDRROOT}/dom/components/fftlib/fftlib.spd.xml
	mkdir -p ${SDRROOT}/dom/components/fftlib/Release
	install Release/libfftlib.so ${SDRROOT}/dom/components/fftlib/Release/libfftlib.so
	mkdir -p ${SDRROOT}/dom/components/fftlib/inc
	install -m 664 inc/*.h ${SDRROOT}/dom/components/fftlib/inc