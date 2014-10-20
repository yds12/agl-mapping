# Makefile

# Build the AGL library
release: map.cpp camera.cpp isometricmap.cpp ortogonalmap.cpp
	g++ -fPIC -c camera.cpp
	g++ -fPIC -c map.cpp
	g++ -fPIC -c isometricmap.cpp
	g++ -fPIC -c ortogonalmap.cpp	
	g++ -shared -o ../lib/libagl-mapping.so camera.o map.o isometricmap.o ortogonalmap.o -lSDL -lagl

# Build the AGL library for debugging
debug: map.cpp camera.cpp isometricmap.cpp ortogonalmap.cpp
	g++ -fPIC -g -c camera.cpp
	g++ -fPIC -g -c map.cpp
	g++ -fPIC -g -c isometricmap.cpp
	g++ -fPIC -g -c ortogonalmap.cpp	
	g++ -shared -g -o ../lib/libagl-mapping.so camera.o map.o isometricmap.o ortogonalmap.o -lSDL -lagl

# Build the test application
test: test.cpp
	g++ -g -o test test.cpp -lagl -lagl-mapping

# Install the AGL library on the system
install:
	../install.sh

# Uninstall the AGL library to the system
remove:
	../remove.sh

# Generates the AGL documentation
doc:
	doxygen doxyfile

# Cleans the directories, removing executables and objects
clean:
	rm *.o test ../lib/*.so
