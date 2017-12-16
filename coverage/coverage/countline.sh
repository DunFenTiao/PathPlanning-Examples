#!/bin/bash

find . -name "*.cpp" -or -name "*.h" |xargs wc -l
