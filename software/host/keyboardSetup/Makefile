# Autodetecting OS
UNAME := $(shell uname -s)
ifeq "$(UNAME)" "Linux"
	OS=LINUX
endif
ifeq "$(UNAME)" "Darwin"
	OS=MACOSX
endif
ifeq "$(OS)" "Windows_NT"
	OS=WINDOWS
endif
# ...or override it here
#OS = LINUX
#OS = MACOSX
#OS = WINDOWS

PROG = keyboardSetup

ifeq ($(OS), LINUX)
TARGET = $(PROG)
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS)
LIBS = -lusb -lhidapi-hidraw

else ifeq ($(OS), MACOSX)
TARGET = $(PROG).dmg
SDK = /Developer/SDKs/MacOSX10.5.sdk
ARCH = -mmacosx-version-min=10.5 -arch ppc -arch i386
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -isysroot $(SDK) $(ARCH)
LIBS = $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation -lhidapi-hidraw

else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-gcc
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS)
LIBS = -lhid -lsetupapi -lhidapi-hidraw
endif

OBJS = $(PROG).o com.o utility.o

all: clean $(TARGET)
run: all test

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)
	$(STRIP) $(PROG)

$(PROG).exe: $(PROG)
	cp $(PROG) $(PROG).exe
$(PROG).dmg: $(PROG)
	mkdir tmp
	cp $(PROG) tmp
	hdiutil create -ov -volname "keyboardSetup" -srcfolder tmp $(PROG).dmg

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o
clean:
	rm -f *.o *.a $(PROG) $(PROG).exe $(PROG).dmg
	rm -rf tmp

TEST_CMD=./$(TARGET) --vid=16C0 --pid=0482 --macro=sample.txt
test:
	@echo ""
	@echo "------------------------------------------------------------------------"
	@echo $(TEST_CMD)
	@echo "------------------------------------------------------------------------"
	@$(TEST_CMD)

help:
	@echo "clean, all   - make [clean,all]"
	@echo "run          - make [clean,all,test]"
	@echo "test         - run test program"
