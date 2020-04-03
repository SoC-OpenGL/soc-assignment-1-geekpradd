OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/disc
SRC1=disc.cpp  include/utility.cpp include/shader.cpp
BIN2=bin/ring
SRC2=ring.cpp  include/utility.cpp include/shader.cpp
BIN3=bin/astroid
SRC3=astroid.cpp  include/utility.cpp include/shader.cpp
BIN4=bin/chessboard
SRC4=chessboard.cpp  include/utility.cpp include/shader.cpp

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)

$(BIN1): $(SRC1)
	g++ $(CPPFLAGS) $(SRC1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRC2)
	g++ $(CPPFLAGS) $(SRC2) -o $(BIN2) $(LDFLAGS) $(LIBS)
$(BIN3): $(SRC3)
	g++ $(CPPFLAGS) $(SRC3) -o $(BIN3) $(LDFLAGS) $(LIBS)
$(BIN4): $(SRC4)
	g++ $(CPPFLAGS) $(SRC4) -o $(BIN4) $(LDFLAGS) $(LIBS)






