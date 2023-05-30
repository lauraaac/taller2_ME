CC = g++
CFLAGS = -Wall -std=c++11
SRCDIR = modularizacion
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp) sistema_de_colas.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(BINDIR)/programa.exe

.PHONY: all clean clean-all

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR) $(OBJDIR):
	mkdir $(subst /,\,$@)

clean:
	rmdir /s /q $(BINDIR) $(OBJDIR) erlang.out

clean-all: clean
	rm /obj/ /bin/ *.txt *.csv