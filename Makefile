# Top-level Makefile

# Find all subdirectories containing a Makefile
SUBDIRS := $(shell find . -type f -name 'Makefile' -not -path './Makefile' -exec dirname {} \;)

# Default target
all: $(SUBDIRS)

# Rule to build each subdirectory
$(SUBDIRS):
	-$(MAKE) -C $@ build

# Clean target for each subdirectory
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all clean $(SUBDIRS)
