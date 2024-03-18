APP_NAME = bess
SUBDIRS = ./$(APP_NAME)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@



clean:
ifeq ($(OS),Windows_NT)
	del /s /q *.exe
	del /s /q *.o
	if exist "out" rmdir /s /q out
else	
	find . -type f -name '*.o' -delete
	rm out -rf
endif

run:
	./out/$(APP_NAME)

.PHONY: all $(SUBDIRS)
