minegg: main.cpp
	g++ main.cpp -luuid -std=c++11 -O2 `pkg-config --cflags --libs opencv` -w -o minegg

install: minegg
	install -s minegg /usr/local/bin/minegg