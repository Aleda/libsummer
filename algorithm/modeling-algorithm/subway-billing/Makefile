##! @BRIEF: Make file
##! @AUTHOR: Aleda(lishuo02@baidu.com)
##! @DATE: 2014/11/2 14:13

SOURCEPATH=-sourcepath src

CLASSPATH=-d bin -cp bin

ENTRY_POINT=SubwayBilling

PACKAGE_NAME=src

JAR_NAME=subway_billing.jar

MAINFEST=MAINFEST

JAVAC=javac

JAVA=java

JAR=jar

JCFLAGS=-g -encoding UTF-8

JFLAGS=-cp bin

JARFALGS=cvfm

SOURCE_FILE=SubwayBilling.java

TARGET=subway_billing

.PHONY: new clean run jar build usage
TARGET: build run

new:
	-mkdir -pv src bin script docs

clean:
	-rm -rf bin/*.class;
	-rm -rf bin/core.*;

run:
	$(JAVA) $(JFLAGS) $(ENTRY_POINT)

jar: 
	$(JAR) $(JARFALGS) $(JAR_NAME) $(ENTRY_POINT) -C ./bin 

build:
	$(JAVAC) $(JCFLAGS) $(SOURCEPATH) $(CLASSPATH) $(PACKAGE_NAME)/$(SOURCE_FILE)

usage:
	@echo "new  : 创建一个新的工作环境"
	@echo "clean: 清理class,jar等文件"
	@echo "run  : 运行程序"
	@echo "jar  : 打包成jar文件"
	@echo "build: 编译源文件"
	@echo "usage: 显示使用方法"
	@echo "make(无参数): build and run"
