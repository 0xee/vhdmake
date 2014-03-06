
vhdmake is a makefile generator for VHDL projects.

For usage info call "vhdmake -h" 

[Building:]
        Just calling make is enough, if all dependencies are satisfied.
        Dependencies:  boost (specifically boost_system and boost_filesystem), 
        a c++11 compliant compiler (eg. gcc 4.7+) and, if you want to modify
        the parsers, the Coco/R parser generator. Installation prefix and Coco/R
        location can be set in cfg.mk

[Installation:]
        make install
        installs vhdmake to the path set in cfg.mk, for which you obviously
        need write permissions.

[License:]
	see LICENSE

Have fun!
