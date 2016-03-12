##! @BRIEF  : makefile
##! @AUTHOR : Aleda(lishuo02@baidu.com || aleda.cn)
##! @DATE   : 2015-03-11 13:47
##! @MODE   : 64Bit
##! @USAGE  :
##!          make         ==>  编译&链接
##!          make clean   ==>  rm ./src/*.o & rm APP
##!          make test    ==>  make -C ./test
##!

ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC \
  --disable-ldap \
  --disable-ldaps
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS 
INCPATH=-I./include 
##! the libs you needed
LIBS=./lib/libcJSON.a ./lib/liburltools.a
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

TARGET_APP_NAME=parse-json

.PHONY: all
all: $(TARGET_APP_NAME) .copy-conf 
	@echo "[BUILD][Target: all]"
	@echo "make all done"
clean:
	@echo "[BUILD][Target: clean]"
	rm -rf ./src/*.o
	rm -rf $(TARGET_APP_NAME)
	@echo "make clean done"
.PHONY: dist
dist:
	@echo "[BUILD][Target: dist]"
	tar czvf output.tar.gz output
	@echo "make dist done"
.PHONY: distclean
distclean: clean
	@echo "[BUILD][Target: distclean]"
	rm -f output.tar.gz
	@echo "make distclean done"

$(TARGET_APP_NAME): $(OBJS)
	@echo "[BUILD][Target: $(TARHET_APP_NAME)]"
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $<
	$(CXX) $(OBJS) -Xlinker "-(" $(LIBS) -Xlinker "-)" -o $@
	@echo "make $(TARGET_APP_NAME) done"

.copy-conf:
	@echo "[BUILD][Target: conf]"
	@echo "cp conf done"

src/%.o: src/%.cpp 
	@echo "[BUILD][Target: compiler]"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o $@ $<
	@echo "make compiler done"

endif #ifeq ($(shell uname -m),x86_64)


