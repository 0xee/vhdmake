
TARGETS = all build clean test install

.PHONY: $(TARGETS)


$(TARGETS):
	$(MAKE) -C src $(MAKECMDGOALS)
