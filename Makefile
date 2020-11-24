########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = gcc
CPPFLAGS = -D_XOPEN_SOURCE=500 
CFLAGS   = -ansi -pedantic -O1 -Wall -fmessage-length=0
LDFLAGS  = 

# Makefile settings - Can be customized.
APPNAME_RX = main_reader
APPNAME_TX = main_writer
EXT = .c
SRCDIR = src
INCDIR = inc
OBJDIR = obj

DOC = doc

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm -rf
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME_TX) $(APPNAME_RX) doc

doc: Doxyfile
	@doxygen $<
	@google-chrome $(DOC)/html/index.html

# Builds the tx app
$(APPNAME_TX): $(OBJ)
	@echo Building application...
	$(CC) $(CFLAGS) -o $@ $(filter-out $(OBJDIR)/$(APPNAME_RX).o, $^) $(LDFLAGS)

# Builds the rx app
$(APPNAME_RX): $(OBJ)
	@echo Building application...
	$(CC) $(CFLAGS) -o $@ $(filter-out $(OBJDIR)/$(APPNAME_TX).o, $^) $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@echo Creating dependecy rules...
	@$(CPP) $(CFLAGS) -I $(INCDIR) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@echo Building object files...
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME_TX) $(APPNAME_RX) $(DOC) $(OBJDIR) *.txt

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)