.PHONY: all clean

all: combined

clean:
	$(RM) combined

%: %.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 $< -o $@
