##! @BRIEF  : makefile
##! @AUTHOR : Aleda(lishuo02@baidu.com || 348983192@qq.com)
##! @DATE   : 2015-03-11 13:47
##! @MODE   : 64Bit
##! @USAGE  :
##!          make         ==>  编译&链接
##!          make clean   ==>  rm ./src/*.o & rm APP


ifeq ($(shell uname -m),x86_64)
CC=gcc
AR=ar
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
ARFLAGS=rv
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I./include -I./src
LIBS=./libsummer.a
TEST_SRCS=$(wildcard test/*.cpp)
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))
TEST_OBJS=$(patsubst %cpp,%o,$(TEST_SRCS))

TARGET_APP_NAME=summer
TARGET_AR_NAME=libsummer.a
TARGET_TEST_NAME=smr_test

.PHONY: all clean output
all: $(TARGET_AR_NAME) .copy-conf 
	@echo "[BUILD][Target: all]"
	@echo "make all done"
clean:
	@echo "[BUILD][Target: clean]"
	rm -rf ./src/*.o ./test/*.o
	rm -rf $(TARGET_APP_NAME)
	rm -rf output
	rm -r include lib
	make -C ./test clean
	@echo "make clean done"
output:
	@echo "[BUILD][Target: output]"
	mkdir -p output/include
	mkdir -p output/lib
	cp src/*.h output/include
	cp libsummer.a output/lib
	@echo "make output done"
    
.PHONY: ar
ar: $(TARGET_AR_NAME)
	@echo "[ARCHIVE][Target: ar]"
	@echo "make ar done"

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

.PHONY: test
test: 
	@echo "[BUILD][Target: test]"
	make -C ./test
	@echo "make test done"

$(TARGET_APP_NAME): $(OBJS)
	@echo "[BUILD][Target: $(TARHET_APP_NAME)]"
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $<
	$(CXX) $(OBJS) -Xlinker "-(" $(LIBS) -Xlinker "-)" -o $@
	@echo "make $(TARGET_APP_NAME) done"

$(TARGET_AR_NAME): $(OBJS)
	@echo "[ARCHIVE][Target: $(TARGET_AR_NAME)]"
	$(AR) $(ARFLAGS) $@ $(OBJS)
	mkdir -p lib
	mv $@ lib
	mkdir include
	cp src/*.h include
	@echo "make $(TARGET_AR_NAME) done"

.copy-conf:
	@echo "[BUILD][Target: conf]"
	@echo "cp conf done"

src/%.o: src/%.cpp 
	@echo "[BUILD][Target: compiler]"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o $@ $<
	@echo "make compiler done"
test/test_%: test/%.o
	@echo "[BUILD][Target: compiler]"
	$(CXX) $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS) -Xlinker "-(" $(LIBS) -Xlinker "-)" -o $@ $<
	@echo "make test_app done"

test/%.o: test/%.cpp
	@echo "[BUILD][Target: test_compiler]"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o $@ $<
	@echo "make test_compiler done"

endif #ifeq ($(shell uname -m),x86_64)


