all:
	cmake -H. -B./build
	make -j8 -C ./build

clean:
	rm -rf ./build
	rm -rf ./bin
	rm -rf cmake-build*
	rm -f sqlite3.db
