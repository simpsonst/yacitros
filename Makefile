all::

FIND=find
SED=sed
XARGS=xargs
CMP=cmp -s
CP=cp
MKDIR=mkdir -p

PREFIX=/usr/local


ifeq ($(notdir $(CC)),gcc)
endif

VWORDS:=$(shell src/getversion.sh --prefix=v MAJOR MINOR PATCH)
VERSION:=$(word 1,$(VWORDS))
BUILD:=$(word 2,$(VWORDS))

## Provide a version of $(abspath) that can cope with spaces in the
## current directory.
myblank:=
myspace:=$(myblank) $(myblank)
MYCURDIR:=$(subst $(myspace),\$(myspace),$(CURDIR)/)
MYABSPATH=$(foreach f,$1,$(if $(patsubst /%,,$f),$(MYCURDIR)$f,$f))

-include $(call MYABSPATH,config.mk)
-include yacitros-env.mk

ARM_HDRS += cond.h
ARM_HDRS += format.h
ARM_HDRS += mnemonic.h
ARM_HDRS += reg.h

RISCOS_HDRS += swiname.h
RISCOS_HDRS += var.h
RISCOS_HDRS += types.h
RISCOS_HDRS += time.h

RISCOS_DRAW_HDRS += op.h
RISCOS_DRAW_HDRS += types.h
RISCOS_HDRS += $(RISCOS_DRAW_HDRS:%=draw/%)

RISCOS_DRAWFILE_HDRS += types.h
RISCOS_HDRS += $(RISCOS_DRAWFILE_HDRS:%=drawfile/%)

RISCOS_FILE_HDRS += dir.h
RISCOS_FILE_HDRS += handle.h
RISCOS_FILE_HDRS += object.h
RISCOS_FILE_HDRS += open.h
RISCOS_FILE_HDRS += types.h
RISCOS_HDRS += $(RISCOS_FILE_HDRS:%=file/%)

RISCOS_FONT_HDRS += op.h
RISCOS_FONT_HDRS += types.h
RISCOS_HDRS += $(RISCOS_FONT_HDRS:%=font/%)

RISCOS_JOYSTICK_HDRS += op.h
RISCOS_JOYSTICK_HDRS += types.h
RISCOS_HDRS += $(RISCOS_JOYSTICK_HDRS:%=joystick/%)

RISCOS_KBD_HDRS += ikn.h
RISCOS_KBD_HDRS += keyname.h
RISCOS_KBD_HDRS += op.h
RISCOS_KBD_HDRS += types.h
RISCOS_HDRS += $(RISCOS_KBD_HDRS:%=kbd/%)

RISCOS_MOUSE_HDRS += op.h
RISCOS_MOUSE_HDRS += types.h
RISCOS_HDRS += $(RISCOS_MOUSE_HDRS:%=mouse/%)

RISCOS_SERIAL_HDRS += op.h
RISCOS_HDRS += $(RISCOS_SERIAL_HDRS:%=serial/%)

RISCOS_SOUND_HDRS +=
RISCOS_HDRS += $(RISCOS_SOUND_HDRS:%=sound/%)

RISCOS_SPRITE_HDRS += args.h
RISCOS_SPRITE_HDRS += op.h
RISCOS_SPRITE_HDRS += optypes.h
RISCOS_SPRITE_HDRS += types.h
RISCOS_HDRS += $(RISCOS_SPRITE_HDRS:%=sprite/%)

RISCOS_VDU_HDRS += action.h
RISCOS_VDU_HDRS += geom.h
RISCOS_VDU_HDRS += bell.h
RISCOS_VDU_HDRS += gfx.h
RISCOS_VDU_HDRS += modevars.h
RISCOS_VDU_HDRS += ptr.h
RISCOS_VDU_HDRS += screen.h
RISCOS_VDU_HDRS += types.h
RISCOS_VDU_HDRS += var.h
RISCOS_VDU_HDRS += vars.h
RISCOS_VDU_HDRS += colourtrans.h
RISCOS_VDU_HDRS += hourglass.h
RISCOS_HDRS += $(RISCOS_VDU_HDRS:%=vdu/%)

RISCOS_WIMP_HDRS += button.h
RISCOS_WIMP_HDRS += errflags.h
RISCOS_WIMP_HDRS += event.h
RISCOS_WIMP_HDRS += icon.h
RISCOS_WIMP_HDRS += key.h
RISCOS_WIMP_HDRS += msgtypes.h
RISCOS_WIMP_HDRS += op.h
RISCOS_WIMP_HDRS += opblocks.h
RISCOS_WIMP_HDRS += scroll.h
RISCOS_WIMP_HDRS += types.h
RISCOS_WIMP_HDRS += win.h
RISCOS_HDRS += $(RISCOS_WIMP_HDRS:%=wimp/%)

YACITROS_HDRS += common.h

YACITROS_OLD_DESKTOP_HDRS += alarm.h
YACITROS_OLD_DESKTOP_HDRS += dataxfer.h
YACITROS_OLD_DESKTOP_HDRS += drag.h
YACITROS_OLD_DESKTOP_HDRS += event.h
YACITROS_OLD_DESKTOP_HDRS += help.h
YACITROS_OLD_DESKTOP_HDRS += iconbar.h
YACITROS_OLD_DESKTOP_HDRS += label.h
YACITROS_OLD_DESKTOP_HDRS += menu.h
YACITROS_OLD_DESKTOP_HDRS += mode.h
YACITROS_OLD_DESKTOP_HDRS += shutdown.h
YACITROS_OLD_DESKTOP_HDRS += task.h
YACITROS_OLD_DESKTOP_HDRS += template.h
YACITROS_OLD_DESKTOP_HDRS += transmit.h
YACITROS_OLD_DESKTOP_HDRS += types.h
YACITROS_OLD_DESKTOP_HDRS += wimpmode.h
YACITROS_OLD_DESKTOP_HDRS += wimpmsg.h
YACITROS_OLD_DESKTOP_HDRS += win.h
YACITROS_OLD_DESKTOP_HDRS += colours.h
YACITROS_DESKTOP_HDRS += $(YACITROS_OLD_DESKTOP_HDRS)
RISCOS_HDRS += $(YACITROS_OLD_DESKTOP_HDRS:%=desktop/%)
YACITROS_HDRS += $(YACITROS_DESKTOP_HDRS:%=desktop/%)

YACITROS_OLD_VECTOR_HDRS += file.h
YACITROS_OLD_VECTOR_HDRS += fonttab.h
YACITROS_OLD_VECTOR_HDRS += generic.h
YACITROS_OLD_VECTOR_HDRS += group.h
YACITROS_OLD_VECTOR_HDRS += intern.h
YACITROS_OLD_VECTOR_HDRS += link.h
YACITROS_OLD_VECTOR_HDRS += op.h
YACITROS_OLD_VECTOR_HDRS += path.h
YACITROS_OLD_VECTOR_HDRS += sprite.h
YACITROS_OLD_VECTOR_HDRS += tagged.h
YACITROS_OLD_VECTOR_HDRS += text.h
YACITROS_OLD_VECTOR_HDRS += types.h
YACITROS_VECTOR_HDRS += $(YACITROS_OLD_VECTOR_HDRS)
RISCOS_HDRS += $(YACITROS_OLD_VECTOR_HDRS:%=vector/%)
YACITROS_HDRS += $(YACITROS_VECTOR_HDRS:%=vector/%)

headers += $(ARM_HDRS:%=arm/%)
headers += $(RISCOS_HDRS:%=riscos/%)
headers += $(YACITROS_HDRS:%=yacitros/%)

libraries += desktop
desktop_libname=yac_dsktop
desktop_mod += $(DESKTOP_MODS:%=desktop/%)
DESKTOP_MODS += help
DESKTOP_MODS += shutdown
DESKTOP_MODS += wimpmsg
DESKTOP_MODS += winicon
DESKTOP_MODS += alarm
DESKTOP_MODS += iconbar
DESKTOP_MODS += task
DESKTOP_MODS += win
DESKTOP_MODS += winmenu
DESKTOP_MODS += dataxfer
DESKTOP_MODS += label
DESKTOP_MODS += template
DESKTOP_MODS += winpane
DESKTOP_MODS += drag
DESKTOP_MODS += menu
DESKTOP_MODS += transmit
DESKTOP_MODS += winconf
DESKTOP_MODS += winplot
DESKTOP_MODS += event
DESKTOP_MODS += mode
DESKTOP_MODS += wimpmode
DESKTOP_MODS += winevent
DESKTOP_MODS += winredraw

libraries += vector
vector_libname=yac_vector
vector_mod += $(VECTOR_MODS:%=vector/%)
VECTOR_MODS += file
VECTOR_MODS += fonttab
VECTOR_MODS += generic
VECTOR_MODS += group
VECTOR_MODS += link
VECTOR_MODS += path
VECTOR_MODS += sprite
VECTOR_MODS += tagged
VECTOR_MODS += text

libraries += draw
draw_libname=yac_draw
draw_mod += $(DRAW_MODS:%=draw/%)
DRAW_MODS += op

libraries += file
file_libname=yac_file
file_mod += $(FILE_MODS:%=file/%)
FILE_MODS += dir
FILE_MODS += handle
FILE_MODS += object
FILE_MODS += open

libraries += font
font_libname=yac_font
font_mod += $(FONT_MODS:%=font/%)
FONT_MODS += op

libraries += joystick
joystick_libname=yac_joystk
joystick_mod += $(JOYSTICK_MODS:%=joystick/%)
JOYSTICK_MODS += op

libraries += kbd
kbd_libname=yac_kbd
kbd_mod += $(KBD_MODS:%=kbd/%)
KBD_MODS += keyname
KBD_MODS += op

libraries += mouse
mouse_libname=yac_mouse
mouse_mod += $(MOUSE_MODS:%=mouse/%)
MOUSE_MODS += op

libraries += os
os_libname=yac_os
os_mod += $(OS_MODS:%=os/%)
OS_MODS += swiname
OS_MODS += var
OS_MODS += time

libraries += serial
serial_libname=yac_serial
serial_mod += $(SERIAL_MODS:%=serial/%)
SERIAL_MODS += op

libraries += sprite
sprite_libname=yac_sprite
sprite_mod += $(SPRITE_MODS:%=sprite/%)
SPRITE_MODS += op

libraries += vdu
vdu_libname=yac_vdu
vdu_mod += $(VDU_MODS:%=vdu/%)
VDU_MODS += bell
VDU_MODS += geom
VDU_MODS += colourtran
VDU_MODS += gfx
VDU_MODS += hourglass
VDU_MODS += ptr
VDU_MODS += screen
VDU_MODS += var

libraries += wimp
wimp_libname=yac_wimp
wimp_mod += $(WIMP_MODS:%=wimp/%)
WIMP_MODS += desktop
WIMP_MODS += event
WIMP_MODS += icon
WIMP_MODS += memory
WIMP_MODS += template
WIMP_MODS += window
WIMP_MODS += error
WIMP_MODS += graphics
WIMP_MODS += input
WIMP_MODS += menu
WIMP_MODS += wimp


SOURCES:=$(filter-out $(headers),$(shell $(FIND) src/obj \( -name '*.c' -o -name '*.h' \) -printf '%P\n'))

riscos_zips += yacitros
yacitros_appname=!Yacitros
yacitros_rof += !Boot,feb
yacitros_rof += README,fff
yacitros_rof += COPYING,fff
yacitros_rof += VERSION,fff
yacitros_rof += $(call riscos_hdr,$(headers))
yacitros_rof += $(call riscos_src,$(SOURCES))
yacitros_rof += $(call riscos_lib,$(libraries))

include binodeps.mk

$(BINODEPS_OUTDIR)/riscos/!Yacitros/README,fff: README.md
	$(MKDIR) "$(@D)"
	$(CP) "$<" "$@"

$(BINODEPS_OUTDIR)/riscos/!Yacitros/COPYING,fff: LICENSE.txt
	$(MKDIR) "$(@D)"
	$(CP) "$<" "$@"

$(BINODEPS_OUTDIR)/riscos/!Yacitros/VERSION,fff: VERSION
	$(MKDIR) "$(@D)"
	$(CP) "$<" "$@"

all:: VERSION BUILD installed-libraries riscos-zips

install:: install-libraries install-riscos install-headers


tidy::
	$(FIND)	. -name "*~" -delete

distclean: blank
	$(RM) VERSION BUILD


MYCMPCP=$(CMP) -s '$1' '$2' || $(CP) '$1' '$2'
.PHONY: prepare-version
mktmp:
	@$(MKDIR) tmp/
prepare-version: mktmp
	$(file >tmp/BUILD,$(BUILD))
	$(file >tmp/VERSION,$(VERSION))
BUILD: prepare-version
	@$(call MYCMPCP,tmp/BUILD,$@)
VERSION: prepare-version
	@$(call MYCMPCP,tmp/VERSION,$@)


# Set this to the comma-separated list of years that should appear in
# the licence.  Do not use characters other than [0-9,] - no spaces.
YEARS=2000-3,2005,2007,2012-13

update-licence:
	$(FIND) . -name ".svn" -prune -or -type f -print0 | $(XARGS) -0 \
	$(SED) -i 's/Copyright (C) [0-9,-]\+  Steven Simpson/Copyright (C) $(YEARS)  Steven Simpson/g'
