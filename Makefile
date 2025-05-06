all:
	 rm -rf build bin
	 cmake -DCMAKE_BUILD_TYPE=Release -S. -Bbuild
	 cmake --build build

debug:
	 rm -rf build bin
	 cmake -DCMAKE_BUILD_TYPE=Debug -S. -Bbuild
	 cmake --build build

clean:
	rm -rf build bin