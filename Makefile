#
# frogger makefile
#
CPP = g++
CPPFLAGS = -std=c++11 -MMD -L/usr/local/SFML/lib -I/usr/local/SFML/include

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)
-include $(OBJS:%.o=%.d)
# all : ;echo $(OBJS)

frogger : $(OBJS)
	$(CPP) $(CPPFLAGS) -o frogger $^ -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

# remove compilation products

.PHONY: clean

clean:
	rm -f frogger *.o *.d