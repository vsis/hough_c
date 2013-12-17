CXX=gcc
CFLAGS=-Wall -W -O2 -lm
CVFLAGS=-lopencv_{core,highgui,imgproc}
OBJ=proc.o
APP=lab1

all: $(OBJ) main.o
	$(CXX) -o $(APP) main.o $(OBJ) $(CFLAGS) $(CVFLAGS)
	@echo "construido con éxito."

obj: $(OBJ)
	@echo "objetos compilados."

%.o: %.c %.h 
	$(CXX) -c -o $@ $< $(CFLAGS) $(CVFLAGS)

clear:
	rm -frv $(APP) *.o

.PHONY: clear

