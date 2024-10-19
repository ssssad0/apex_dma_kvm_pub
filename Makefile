CXX=g++ -w -I/usr/include/jsoncpp -ljsoncpp -lcurl
CXXFLAGS=-I./memflow_lib/memflow-ffi/ -L./memflow_lib/target/release -Wno-multichar -Wno-deprecated-declarations
LIBS=-lm -Wl,--no-as-needed -ldl -lpthread -l:libmemflow_ffi.a -I/usr/include/jsoncpp -ljsoncpp -lcurl

OUTDIR=./build
OBJDIR=$(OUTDIR)/obj

$(shell mkdir -p $(OBJDIR))

%.o: %.cpp
	$(CXX) -c -o $(OBJDIR)/$@ $< $(CXXFLAGS)

apex_dma: apex_dma.o Game.o Math.o memory.o
	$(CXX) -o $(OUTDIR)/$@ $(OBJDIR)/apex_dma.o $(OBJDIR)/Game.o $(OBJDIR)/Math.o $(OBJDIR)/memory.o $(CXXFLAGS) $(LIBS)

.PHONY: all
all: apex_dma

.DEFAULT_GOAL := all

clean:
	rm -rf $(OUTDIR)
