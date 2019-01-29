# dir=../bin-r
dir=/tmp/zhscript2
tag=$(dir)/gtksh
pdir=$(tag)-plugin
f1=-std=c++1y -O3 -Wall -fmessage-length=0
pf1=$(f1) -fPIC
pc=pkg-config --cflags --libs
pub=main/pub/*.cpp main/pub/*.h

os_ := $(shell cat /etc/issue)
ifneq ($(findstring 16.,$(os_)),)
f_wk := -Dver_u1704_
else
ifneq ($(findstring 17.04,$(os_)),)
f_wk := -Dver_u1704_
endif
endif

tags=$(tag) $(pdir)/webkit/webkit.so $(pdir)/src.so $(pdir)/vte.so $(pdir)/cairog.so

all: mkdir $(tags)
mkdir:
	mkdir -p $(pdir)/webkit
clean:
	rm $(tags)

$(tag): main/*.cpp main/*.h $(pub)
	g++ $^ -o "$@" $(f1) -ldl -lstdc++fs `$(pc) gtk+-3.0`

$(pdir)/webkit/webkit.so: plugin/webkit/*.cpp plugin/webkit/*.h $(pub)
	g++ $^ -o "$@" -shared $(pf1) $(f_wk) `$(pc) gtk+-3.0 webkit2gtk-4.0`

$(pdir)/src.so: plugin/src/*.cpp plugin/src/*.h $(pub)
	g++ $^ -o "$@" -shared $(pf1) `$(pc) gtk+-3.0 gtksourceview-3.0`

$(pdir)/vte.so: plugin/vte/*.cpp plugin/vte/*.h $(pub)
	g++ $^ -o "$@" -shared $(pf1) `$(pc) gtk+-3.0 vte-2.91`

$(pdir)/cairog.so: plugin/cairog/*.cpp plugin/cairog/*.h $(pub)
	g++ $^ -o "$@" -shared $(pf1) `$(pc) gtk+-3.0`

