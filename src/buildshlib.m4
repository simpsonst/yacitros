changequote({:,:}){:
all::

ROSHAR=roshar
MKDIR=CDir
CC=cc

CFLAGS += -IYacitros: -ICSWIs: -IDDSLib:
CFLAGS += -w -apcs 3/reent

PARTS=:}PARTS{:

all:: shlib
	ShlInstall shlib yacitros.:}NAME{: :}VERSION{:

o:
	$(MKDIR) $@

shlib: o $(PARTS:%=%.o)
	$(ROSHAR) -o $@ $(PARTS:%=o.%)

:}
