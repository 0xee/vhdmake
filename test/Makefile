# generated Thu Mar  6 18:05:40 2014 by vhdmake

all: Makefile \
		c.vhd.done \
		test.vhd.done \
		test/b.vhd.done \
		test/a.vhd.done \
		

Makefile: c.cfg
	vhdmake c.cfg

c:
	vlib c

work:
	vlib work



c.vhd.done: c c.vhd 
	vcom -2008 -work ./c c.vhd
	touch c.vhd.done

test.vhd.done: work test.vhd 
	vcom -2008 -work ./work test.vhd
	touch test.vhd.done

test/b.vhd.done: work test/b.vhd test/a.vhd.done 
	vcom -2008 -work ./work test/b.vhd
	touch test/b.vhd.done

test/a.vhd.done: work test/a.vhd 
	vcom -2008 -work ./work test/a.vhd
	touch test/a.vhd.done



clean:
	rm -rf c c.vhd.done work test.vhd.done test/b.vhd.done test/a.vhd.done 

.PHONY: clean
