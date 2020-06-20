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

cp $MKF_TMPL $TAR_MAKEFILE

sed -i "s/<__BOOST_INC_TO_FILL__>/${BOOST_INC_HOME}/" $TAR_MAKEFILE
sed -i "s/<__BOOST_LIB_TO_FILL__>/${BOOST_LIB_HOME}/" $TAR_MAKEFILE
