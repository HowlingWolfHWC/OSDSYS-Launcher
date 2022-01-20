EE_BIN = main-nogui.elf
EE_BIN_PACKED = main-nogui-packed.ELF
EE_BIN_STRIPPED = main-nogui-stripped.ELF
EE_OBJS = main-nogui.o OSDInit.o libcdvd_add.o
EE_LIBS = -ldebug -lc -lcdvd -lpatches -lfileXio

all:
	$(MAKE) $(EE_BIN_PACKED)

clean:
	rm -fr *.ELF *.o *.bak

$(EE_BIN_STRIPPED): $(EE_BIN)
	$(EE_STRIP) -o $@ $<
	
$(EE_BIN_PACKED): $(EE_BIN_STRIPPED)
ifeq ($(USE_LOCAL_PACKER),1)
	ps2-packer/ps2-packer -v $< $@
else
	ps2-packer $< $@
endif

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
