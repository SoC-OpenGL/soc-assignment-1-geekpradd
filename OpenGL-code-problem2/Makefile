OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/trianglegradient
SRC1=trianglegradient.cpp  include/utility.cpp include/shader.cpp
BIN2=bin/chessboard
SRC2=chessboard.cpp  include/utility.cpp include/shader.cpp

all: $(BIN1) $(BIN2)

$(BIN1): $(SRC1)
	g++ $(CPPFLAGS) $(SRC1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRC2)
	g++ $(CPPFLAGS) $(SRC2) -o $(BIN2) $(LDFLAGS) $(LIBS)





