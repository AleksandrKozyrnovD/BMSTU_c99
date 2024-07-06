INCDIR := ./inc
SRCDIR := ./src
OUTDIR := ./out
UNITDIR := ./unit_tests

#Места, в которых будут производиться поиск
vpath %.c $(SRCDIR) $(UNITDIR)

#Товарищ компилятор
CC := gcc


#Стандартные библиотеки. Без них никуда
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic

CFLAGSLIB := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic -fPIC

#Библиотеки, указываемые после всех
LDFLAGS := -lm
UNITFLAGS := -lcheck -lpthread -lrt

#Все .c файлы из /src
SRCS := $(wildcard $(SRCDIR)/*.c)

#Список все возможных .o файлов из /src
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

LIBOBJS := $(filter-out $(OUTDIR)/main.o $(OUTDIR)/main_dyn.o, $(OBJS))

#Список модульных
TEST_SRCS := $(wildcard $(UNITDIR)/*.c)

#Аналогично делаем список всех .o для старых + модульных
ALL_OBJS := $(OBJS) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)

#Всевозможные зависимости
DEPS := $(ALL_OBJS:.o=.d)

PWD := $(shell pwd)

#Убираем main.o из списка всех объектных для модульных
TEST_OBJS := $(filter-out $(OUTDIR)/main.o $(OUTDIR)/main_dyn.o, $(ALL_OBJS))

.PHONY: release debug adress memory undef gcov func unit collect_coverage clean static dyn1 dyn2

release: app.exe

debug: CFLAGS += -O0 -g3
debug: app.exe

adress:
	make -f makefile_clang adress

memory:
	make -f makefile_clang memory

undef:
	make -f makefile_clang undef

func: debug
	./func_tests/scripts/func_tests.sh --valgrind

collect_coverage:
	cd out && gcov -o ./ ../$(SRCDIR)/*.c

# unit: LDFLAGS += -lcheck -lpthread -lrt
unit: unit_tests.exe
	./unit_tests.exe

gcov: CFLAGS += -O0 -g3 --coverage
gcov: LDFLAGS += --coverage
gcov: app.exe

$(OUTDIR)/libprocess.so: $(LIBOBJS)
	$(CC) -o $@ -shared $(LIBOBJS)

$(OUTDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $@ -c $< -fPIC

app.exe: $(OUTDIR)/main.o $(OUTDIR)/libprocess.so
	$(CC) $(CFLAGS) -o $@ $(OUTDIR)/main.o -L$(OUTDIR) -lprocess
	export LD_LIBRARY_PATH=$(PWD)/$(OUTDIR)/:$LD_LIBRARY_PATH

unit_tests.exe: $(TEST_OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(UNITFLAGS)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGSLIB) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

clean:
	rm -rf $(OUTDIR) .cache/
	rm -f ./*.exe ./vgcore* ./*.d ./*.o ./*.so
