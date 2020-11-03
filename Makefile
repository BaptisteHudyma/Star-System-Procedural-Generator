CC = g++
CFLAGS = -Wall
LIBS = 

OUTFILE = ./build/

OBJ_CPP = $(wildcard *.cpp )
OBJ_O = $(patsubst %.cpp, $(OUTFILE)%.o, $(notdir ${OBJ_CPP}))

all: $(OBJ_O) 
	$(CC) -o galaxy $(OBJ_O) $(LIBS) 
	echo Finished

$(OUTFILE)%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OUTFILE)*
	echo "All Cleaned"

rmproper: clean
	$(RM) galaxy
	echo "All removed"
