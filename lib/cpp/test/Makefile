
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
INCPATH=-I../include -I../src -I./
LIBS=../libsummer.a
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

TARGET_APP_NAME=test_smr_string test_smr_func
TARGET_AR_NAME=libsummer.a
TARGET_TEST_NAME=smr_test

.PHONY: all clean output
all: $(TARGET_APP_NAME) .copy-conf 
	@echo "[BUILD][Target: all]"
	@echo "make all done"
clean:
	@echo "[BUILD][Target: clean]"
	rm -rf ./*.o
	rm -rf $(TARGET_APP_NAME)
	@echo "make clean done"
output:
	@echo "[BUILD][Target: output]"
	
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
	cd test && make
	cd - 1>/dev/null 2>&1
	@echo "make test done"

$(TARGET_APP_NAME): %:%.o
	@echo "[BUILD][Target: $(TARHET_APP_NAME)]"
	$(CXX) $< -Xlinker "-(" $(LIBS) -Xlinker "-)" -o $@
	@echo "make $(TARGET_APP_NAME) done"

$(TARGET_AR_NAME): $(OBJS)
	@echo "[ARCHIVE][Target: $(TARGET_AR_NAME)]"
	$(AR) $(ARFLAGS) $@ $(OBJS)
	@echo "make $(TARGET_AR_NAME) done"

.copy-conf:
	@echo "[BUILD][Target: conf]"
	@echo "cp conf done"

$(OBJS): %.o: %.cpp 
	@echo "[BUILD][Target: compiler]"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o $@ $<
	@echo "make compiler done"

endif #ifeq ($(shell uname -m),x86_64)


