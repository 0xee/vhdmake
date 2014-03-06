include ../../cfg.mk 

GENSRC = Scanner.h Parser.h Scanner.cpp Parser.cpp

$(GENSRC): *.atg	
	echo "Generating $(patsubst %.atg,%,$<) scanner/parser"
	$(COCO) -frames $(COCO_FRAMES) $< -namespace $(patsubst %.atg,%,$<)

clean:
#rm -rf $(GENSRC) $(patsubst %,%.old,$(GENSRC))

.PHONY: clean
