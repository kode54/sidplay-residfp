.phony: all clean

all: combined${EXT}

clean:
	rm -f combined${EXT}

%{EXT}: %.cpp
	$(CXX) "$<"
