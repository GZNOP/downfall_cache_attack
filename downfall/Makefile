CC                   = gcc
G+					 = g++
AS                   = gcc
LD                   = gcc
CFLAGS              += -D_GNU_SOURCE -O0 
INCLUDE              = -I.
LDFLAGS             += $(SUBDIRS:%=-L %) -lpthread -lstdc++

SOURCES              = $(shell ls *.c)
cppSOURCES           = $(shell ls *.cpp)
OBJECTS              = $(SOURCES:.c=.o) $(cppSOURCES:.cpp=.o) attacker.o
OUTPUT               = gds

BUILDDIRS            = $(SUBDIRS:%=build-%)
CLEANDIRS            = $(SUBDIRS:%=clean-%)

.SILENT:
all: $(OUTPUT) victim

$(OUTPUT): $(BUILDDIRS) $(OBJECTS)
	echo "$(INDENT)[LD]" $(OBJECTS) $(LIBS) -o $(OUTPUT) 
	$(LD) $(OBJECTS) -no-pie  $(LDFLAGS) -o $(OUTPUT) 

%.o : %.c
	echo "$(INDENT)[CC] " $<
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

%.o : %.cpp
	echo "$(INDENT)[G+] " $<
	$(G+) $(CPPFLAGS) $(INCLUDE) -c $<

%.o : %.S
	echo "$(INDENT)[AS] " $<
	$(AS) $(CFLAGS) $(INCLUDE) -c $< -o $@

victim: victim_d/victim.c victim_d/gather.S
	$(CC) $(CFLAGS) $^ -o $@

clean: $(CLEANDIRS)
	echo "$(INDENT)[RM]" $(OBJECTS) $(OUTPUT) victim
	rm -f $(OBJECTS) $(OUTPUT) victim
