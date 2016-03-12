#!/bin/bash
##! AUTHOR: Aleda(aledalee@foxmail.com | aleda.cn)

### 1. What Is it?
SPFA的建模实现：一个简易的地铁计费Demo，是一道面试题。
具体细节请看：./docs/DesignDocument

### 2. Hierarchy.
.
├── bin
│   ├── Edge.class
│   └── SubwayBilling.class
├── docs
│   ├── DesignDocument
│   └── TestDocument
├── in.txt
├── MAINFEST
├── Makefile
├── out.txt
├── README
├── script
│   ├── build.sh
│   ├── stations.list
│   └── subway.map
└── src
    └── SubwayBilling.java

4 directories, 14 files

### 3. Requirements & Build
Requirements: javac   

Build:

    step 1:
    cd script && bash build_map.sh
    step 2: 
    make > out.txt
    step 3:
    make clean

### 4. Any question
Please contact Aleda(aledalee@foxmail.com | aleda.cn)

