APPNAME := test
CSRC := $(wildcard *.c)
CXXSRC := $(wildcard *.cpp ../incubator/*.cpp)
OBJS := $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)

CXXFLAGS +=
CFLAGS += -Wall -Wextra -pedantic -O2
CPPFLAGS += -I../incubator
LDLIBS += -lstdc++
LDFLAGS += -s

ifdef DEBUG
CFLAGS := $(filter-out -O%,$(CFLAGS)) -g -O0 -D DEBUG
LDFLAGS := $(filter-out -s,$(LDFLAGS)) -rdynamic
endif

.PHONY: all clean

all: $(APPNAME)

clean:
	$(RM) $(APPNAME) $(OBJS) $(CLEAN)

# Header dependencies
CPPFLAGS += -MMD
CLEAN += $(OBJS:.o=.d)
-include $(OBJS:.o=.d)

-include version.mk

$(APPNAME): $(OBJS)
