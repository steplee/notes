#!/bin/sh

f=$(mktemp)

pandoc -f markdown_github $1 -o $f

google-chrome $f
