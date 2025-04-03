all:
	cmake -H. -B./build
	make -C ./build

clean:
	rm -rf ./build
	rm -rf ./bin
	rm -rf cmake-build*
	rm sqlite3.db
