#!/bin/sh -

SNAME=`basename $0`
CWD=`pwd`
COPY_TO_DEBUG_PATH="${HOME}/temp/cig.debug"
MFILE="GNUmakefile"
GITDIR=".git"

if [[ -d $COPY_TO_DEBUG_PATH ]]; then
    echo "Dir $COPY_TO_DEBUG_PATH already exist, removing files inside..."
    rm -rf ${COPY_TO_DEBUG_PATH}/*
else
    echo "Dir $COPY_TO_DEBUG_PATH doesn't exist, creating"
    mkdir -p ${COPY_TO_DEBUG_PATH}
fi

echo "Copying files..."
cp -rf ./* ${COPY_TO_DEBUG_PATH}/

echo "Change dir to $COPY_TO_DEBUG_PATH to make clean"
cd ${COPY_TO_DEBUG_PATH}
if [[ -e $MFILE ]]; then
    make clean
else
    echo "Makefile not found: $MFILE"
fi

if [[ -d $GITDIR ]]; then
    echo "Remove git dir as tracking is not needed"
    rm -rf $GITDIR
fi

if [[ -e $SNAME ]]; then
    echo "Remove this script itself in target directory"
    rm -rf $SNAME
fi

echo "Done"
cd $CWD
