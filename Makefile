all:
	 rm -rf bin build/CMakeFiles/discovery-service.dir
	 cmake -DCMAKE_BUILD_TYPE=Release --fresh -S. -Bbuild -G Ninja
	 ninja -C build

debug:
	 rm -rf bin build/discovery-service.dir
	 cmake -DCMAKE_BUILD_TYPE=Debug --fresh -S. -Bbuild -G Ninja
	 ninja -v -C build

clean:
	rm -rf build bin