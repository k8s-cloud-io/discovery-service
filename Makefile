all:
	 rm -rf build bin
	 cmake -DCMAKE_BUILD_TYPE=Release -S. -Bbuild -G Ninja
	 ninja -C build

debug:
	 rm -rf build bin
	 cmake -DCMAKE_BUILD_TYPE=Debug -S. -Bbuild -G Ninja
	 ninja -v -C build

clean:
	rm -rf build bin