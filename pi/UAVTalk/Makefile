CFLAGS = -std=c99
LFLAGS = -lm -lwiringPi

ODIR = build

_OBJ = UAVTalk.o MessageViewer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	gcc -c -o $@ $< $(CFLAGS) $(LFLAGS)

#$(ODIR)/SerialComm_Test.o: SerialComm_Test.c
#	gcc -c -o $@ $< $(CFLAGS) $(LFLAGS)

all: serial listen poll

serial: $(ODIR)/SerialComm_Test.o $(OBJ) 
	gcc -o $@ $^ $(CFLAGS) $(LFLAGS)

listen: $(ODIR)/SerialListen_Test.o $(OBJ) 
	gcc -o $@ $^ $(CFLAGS) $(LFLAGS)

poll: $(ODIR)/SerialPoll_Test.o $(OBJ) 
	gcc -o $@ $^ $(CFLAGS) $(LFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o serial listen poll
