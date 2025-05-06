all:
	 rm -rf build
	 cmake -S. -Bbuild -G Ninja
	 ninja -C build

clean:
	rm -rf build bin