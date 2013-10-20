CC=arm-linux-gnueabi-gcc
CFLAGS=-static -Wall

OUTFILE=$(BINDIR)/$(HWEXEC)
HWEXEC=helloworld
BINDIR=../bin

HWSOURCE=$(HWEXEC).c
RM=rm -rf
MKDIR=mkdir -p

.PHONY: all clean

all: $(BINDIR) $(OUTFILE)

$(OUTFILE): $(HWSOURCE)
	$(CC) $(CFLAGS) $^ -o $(@)

$(BINDIR):
	$(MKDIR) $(BINDIR)

clean:
	$(RM) *.o $(OUTFILE)
