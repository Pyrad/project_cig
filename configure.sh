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

cp $MKF_TMPL $TAR_MAKEFILE

### Don't use '/' in reg expression in sed, as $BOOST_INC_HOME has '/'
### in its string value
sed -i "s#<__BOOST_INC_TO_FILL__>#${BOOST_INC_HOME}#g" $TAR_MAKEFILE
sed -i "s#<__BOOST_LIB_TO_FILL__>#${BOOST_LIB_HOME}#g" $TAR_MAKEFILE
