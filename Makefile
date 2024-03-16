APP_NAME = bess
SUBDIRS = ./$(APP_NAME)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	find . -type f -name '*.o' -delete
	rm out -rf
run:
	./out/$(APP_NAME)

.PHONY: all $(SUBDIRS)
