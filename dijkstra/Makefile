CFLAGS = -Wall -Wextra -std=c++17

dial: dial.cpp Graph.cpp creator.cpp
	g++ $(CFLAGS) dial.cpp Graph.cpp creator.cpp CircularArray.cpp -o dial

dijkstra: dijkstra.cpp Graph.cpp creator.cpp
	g++ $(CFLAGS) dijkstra.cpp Graph.cpp creator.cpp -o dijkstra

clean:
	@rm dijkstra dial