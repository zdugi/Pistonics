##################################################
# Makefile for Pistonics by Dugi                 #   
# Info:                                          #
# 	Default start point (main function) is   #
# 	located int src/main.cpp. Rule for it    #
# 	is written dedicated. All other          #
# 	deppendencies (files) your should add	 #
# 	in TGDEPS.				 #
##################################################

CC = g++ -g
CFLAGS = -Werror -Wall -lSDL2 -lSDL2_ttf
SDIR = src
BDIR = build
ODIR = obj
PROG = program # this is program exec name
TGDEPS = Shape.cpp \
	 Rectangle.cpp \
	 BoundBox.cpp \
	 GameObject2D.cpp \
	 CollisionEngine.cpp \
	 Display.cpp \
	 Game.cpp \
	 Player.cpp \
	 Wall.cpp \
	 Enemy.cpp \
	 GameState.cpp \
	 Coin.cpp \
	 AIOutput.cpp \
	 Test.cpp \
	 TextRenderEngine.cpp
OBJECTS = $(patsubst %.cpp,$(ODIR)/%.o,$(TGDEPS))

$(BDIR)/$(PROG): $(OBJECTS) $(ODIR)/main.o
	$(CC) $(CFLAGS) $(OBJECTS) $(ODIR)/main.o -o $@

$(OBJECTS): | $(ODIR)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: $(SDIR)/%.cpp $(SDIR)/%.h
	$(CC) -c -o $@ $<

$(ODIR)/main.o: $(SDIR)/main.cpp
	$(CC) -c $(SDIR)/main.cpp -o $@ 

.PHONY: clean
clean:
	rm -r $(ODIR)/* $(BDIR)/$(PROG)
