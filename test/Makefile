# generated Fri Mar 28 18:06:15 2014 by vhdmake

all: Makefile \
		c.vhd.done \
		test.vhd.done \
		test/a.vhd.done \
		test/b.vhd.done \
		

Makefile: config.cfg
	vhdmake config.cfg

libs: 
	mkdir -p libs
	vlib libs/work

libs/libs.done: libs/c libs/work 

libs/c: libs
	vlib libs/c
	vmap c libs/c

libs/work: libs
	vlib libs/work
	vmap work libs/work



c.vhd.done: libs/libs.done c.vhd 
	vcom -2008 -work c c.vhd
	touch c.vhd.done

test.vhd.done: libs/libs.done test.vhd 
	vcom -2008 -work work test.vhd
	touch test.vhd.done

test/a.vhd.done: libs/libs.done test/a.vhd 
	vcom -2008 -work work test/a.vhd
	touch test/a.vhd.done

test/b.vhd.done: libs/libs.done test/b.vhd test/a.vhd.done 
	vcom -2008 -work work test/b.vhd
	touch test/b.vhd.done



sim:
	make -C test sim


clean:
	rm -rf libs/c c.vhd.done libs/work test.vhd.done test/a.vhd.done test/b.vhd.done 

.PHONY: clean
