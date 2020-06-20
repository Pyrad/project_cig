#!/bin/sh -

if [[ -z $BOOST_INC_HOME ]]; then
    echo "Env var BOOST_INC_HOME is not found"
    exit
fi

if [[ -z $BOOST_LIB_HOME ]]; then
    echo "Env var BOOST_LIB_HOME is not found"
    exit
fi
