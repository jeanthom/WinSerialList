CC=i686-w64-mingw32-gcc
CXX=i686-w64-mingw32-g++

OBJS=src/main.o src/CClsWind.o src/CWind.o
CXXFLAGS=-lgdi32.lib -Os -flto
LDFLAGS=-flto -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -lgdi32 -mwindows -fdata-sections -ffunction-sections -Wl,--gc-sections

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Wl,--gc-sections

WinSerialList.exe: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ -Wl,--gc-sections -Wl,--strip-all

clean:
	rm src/*.o
	rm WinSerialList.exe
.PHONY: clean
