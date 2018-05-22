CXX = g++
INCLUDE = ../../include
override CXXFLAGS += -Wall -Wextra -std=c++14 -I $(INCLUDE)
override LINK += -lSDL2 -lGL -lGLU -lpthread -lIL -lassimp -lboost_system -lboost_filesystem
ENGINE = ../../src/engine

 SOR = $(shell find $(ENGINE) -name '*.cpp')
 SOR += $(shell find . -name '*.cpp')

target : $(patsubst %.cpp, %.o, $(foreach file, $(SOR), $(shell basename $(file))))
	$(CXX) -o $@ $^ $(LINK)

define template
$(1) : $(2)
	$(CXX) $(CXXFLAGS) -c $$<
endef

$(foreach file, $(SOR), $(eval $(call template, $(patsubst %.cpp, %.o, $(shell basename $(file))), $(file))))

.PHONY: clean

clean:
	rm *.o
