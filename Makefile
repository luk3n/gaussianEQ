CXX=g++
CXXFLAGS=-g
APPNAME=gaussianeq
BINDIR=/usr/local/bin

$(APPNAME): $(APPNAME).o
		$(CXX) $(CXXFLAGS) -o $(APPNAME) $(APPNAME).o

$(APPNAME).o: $(APPNAME).cpp 
		$(CXX) $(CXXFLAGS) -c $(APPNAME).cpp

.PHONY: clean
clean:
		rm -rf $(APPNAME) *.o

install:
		cp gaussianeq $(BINDIR)

uninstall:
		rm $(BINDIR)/gaussianeq