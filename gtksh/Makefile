tag=../bin-r/gtksh
tag=/zzzzzzzzzzz4/usr/lib/zhscript2/gtksh
pdir=$(tag)-plugin
f1=-std=c++1y -O3 -Wall -fmessage-length=0
pf1=$(f1) -fPIC
pc=pkg-config --cflags --libs

all: $(tag) $(pdir)/webkit/webkit.so $(pdir)/src.so $(pdir)/vte.so

$(tag): main/*.cpp main/*.h main/pub/*.cpp main/pub/*.h
	g++ -o "$@" $(f1) $^ -ldl -lstdc++fs `$(pc) gtk+-3.0`

$(pdir)/webkit/webkit.so: plugin/webkit/*.cpp plugin/webkit/*.h plugin/webkit/pub/*.cpp plugin/webkit/pub/*.h
	g++ -shared -o "$@" $(pf1) $^ `$(pc) gtk+-3.0 webkit2gtk-4.0`

$(pdir)/src.so: plugin/src/*.cpp plugin/src/*.h plugin/src/pub/*.cpp plugin/src/pub/*.h
	g++ -shared -o "$@" $(pf1) $^ `$(pc) gtk+-3.0 gtksourceview-3.0`

$(pdir)/vte.so: plugin/vte/*.cpp plugin/vte/*.h plugin/vte/pub/*.cpp plugin/vte/pub/*.h
	g++ -shared -o "$@" $(pf1) $^ `$(pc) gtk+-3.0 vte-2.91`

