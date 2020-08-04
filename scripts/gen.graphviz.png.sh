#!/bin/sh -

dotfiles=`ls *.dot`
for df in $dotfiles; do
    echo "Create PNG for: $df"
    dot -Tpng -O $df
done
