all:
	 rm -rf build bin
	 cmake -S. -Bbuild -G Ninja
	 cmake --build build

debug:
	 rm -rf build bin
	 cmake -DCMAKE_BUILD_TYPE=Debug -S. -Bbuild
	 cmake --build build

clean:
	rm -rf build bin