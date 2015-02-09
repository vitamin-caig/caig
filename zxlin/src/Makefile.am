bin_PROGRAMS = zxlin
zxlin_SOURCES = ay.cpp ay.h computer.cpp computer.h context.cpp context.h \
		cpu.cpp cpu_funcs.cpp cpu_funcs.h cpu.h cpu_tabs.h dac.cpp dac.h debugger.cpp \
		debugger.h device.h disasm.cpp disasm.h dump.cpp dumpeditor.cpp dumpeditor.h \
		dump.h editor.cpp editor.h font.h iomanager.cpp iomanager.h keyboard.cpp \
		keyboard.h main.cpp memory.cpp memory.h mnemotab.h mouse.cpp mouse.h \
		soundmanager.cpp soundmanager.h textmatrix.cpp textmatrix.h types.h ula.cpp ula.h \
		wordeditor.cpp wordeditor.h zxlin.cpp zxlin.h configure.cpp gfxcontrol.cpp \
		betadisk.cpp cuilib.cpp cuilib.h cuitypes.h UI.cpp options.ui headings.h headings.i \
		ini.cpp ini.h keys.h keys.i libini.h list.h list.i types.i dma.cpp options.cpp

all: options.h all-am
	cp -f zxlin ../result/zxlin
    
options.h: options.ui
	rm -rf options.h;
	$(UIC) options.ui > options.h ;

options.moc: options.h
	$(MOC) options.h -o options.moc

options.cpp: options.ui options.h options.moc
	rm -f options.cpp
	$(UIC) -tr "" -i options.h options.ui > options.cpp ; ret=$$?;
	echo '#include "options.moc"' >> options.cpp;

clean:
	rm -f options.cpp options.h options.moc
	rm -f *.o
	rm -f zxlin


# set the include path found by configure
INCLUDES= $(all_includes)

AM_CXXFLAGS=
AM_CPPFLAGS=

# the library search path.
zxlin_LDFLAGS = $(all_libraries)
