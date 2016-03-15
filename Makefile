EXEC = raytracing
.PHONY: all
all: $(EXEC)

CC ?= gcc
CFLAGS = \
	-std=gnu99 -Wall -O0 -g -DNDEBUG -pthread
LDFLAGS = \
	-lm

XDOT = ~/xdot.py/xdot.py
GPROF2DOT = ~/gprof2dot/gprof2dot.py

ifeq ($(strip $(PROFILE)),1)
PROF_FLAGS = -pg
CFLAGS += $(PROF_FLAGS)
LDFLAGS += $(PROF_FLAGS) 
endif

OBJS := \
	objects.o \
	raytracing.o \
	main.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) -pthread

main.c: use-models.h
use-models.h: models.inc Makefile
	@echo '#include "models.inc"' > use-models.h
	@egrep "^(light|sphere|rectangular) " models.inc | \
	    sed -e 's/^light /append_light/g' \
	        -e 's/light[0-9]/(\&&, \&lights);/g' \
	        -e 's/^sphere /append_sphere/g' \
	        -e 's/sphere[0-9]/(\&&, \&spheres);/g' \
	        -e 's/^rectangular /append_rectangular/g' \
	        -e 's/rectangular[0-9]/(\&&, \&rectangulars);/g' \
	        -e 's/ = {//g' >> use-models.h

perf:
	perf stat \
		-e cache-misses,cache-references,instructions,cycles,branch-misses,branch-instructions \
		./raytracing

plot: check-gmon
	gprof ./$(EXEC) | $(GPROF2DOT) > $@.dot; \
	dot -Tpng -o $@.png $@.dot; \
	$(XDOT) ./$@.dot;

check-gmon:
	@(test -s $(EXEC) || make PROFILE=1)
	@(test -s gmon.out || ./$(EXEC))
	@(test -s gmon.out || { echo "ERROR: PROFILE needed be set to 1"; exit 1; })

astyle:
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]

clean:
	$(RM) $(EXEC) $(OBJS) use-models.h \
	out.ppm gmon.out plot.dot plot.png
