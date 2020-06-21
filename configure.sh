#!/bin/sh -

if [[ -z $BOOST_INC_HOME ]]; then
    echo "Env var BOOST_INC_HOME is not found"
    exit
else
    echo "Found env var BOOST_INC_HOME: $BOOST_INC_HOME"
fi

if [[ -z $BOOST_LIB_HOME ]]; then
    echo "Env var BOOST_LIB_HOME is not found"
    exit
else
    echo "Found env var BOOST_LIB_HOME: $BOOST_LIB_HOME"
fi

MKF_TMPL="./template.makefile"
TAR_MAKEFILE="GNUmakefile"
if [[ ! -f $MKF_TMPL ]]; then
    echo "Template file($MKF_TMPL) for Makefile is not found"
    exit
fi

if [[ -f $TAR_MAKEFILE ]]; then
    echo "Warning: removing old $TAR_MAKEFILE"
    rm -rf $TAR_MAKEFILE
fi

CXX_BIN=`which g++`
if [[ $? == 1 ]]; then
    echo "Error: g++ is not found"
    exit
else
    echo "g++ is $CXX_BIN"
fi

GXX_VER=`g++ --version | head -n 1 | cut -d' ' -f 3`
echo "g++ version is: ${GXX_VER}"

cp $MKF_TMPL $TAR_MAKEFILE

### Don't use '/' in reg expression in sed, as $BOOST_INC_HOME has '/'
### in its string value
sed -i "s#<__BOOST_INC_TO_FILL__>#${BOOST_INC_HOME}#g" $TAR_MAKEFILE
sed -i "s#<__BOOST_LIB_TO_FILL__>#${BOOST_LIB_HOME}#g" $TAR_MAKEFILE
sed -i "s#<__CXX_TO_FILL>#${CXX_BIN}#g" $TAR_MAKEFILE


### Clean old objects & binary directory
OBJ_DIR="./objs"
BIN_DIR="./bin"
if [[ -d $OBJ_DIR ]]; then
    echo "Warning: old objects in dir <$OBJ_DIR> will be removed"
    rm -rf ${OBJ_DIR}/*
else
    echo "Creating directory for objects: $OBJ_DIR"
    mkdir $OBJ_DIR
fi

if [[ -d $BIN_DIR ]]; then
    echo "Warning: old binaries in dir <$BIN_DIR> will be removed"
    rm -rf ${BIN_DIR}/*
else
    echo "Creating directory for objects: $BIN_DIR"
    mkdir $BIN_DIR
fi

echo "Target make file created: $TAR_MAKEFILE"
