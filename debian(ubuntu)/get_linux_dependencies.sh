#!/bin/bash

ldd $1|awk '{print $1}'|sed 's/\..*//'|while read n; do echo "----- $n -----"; apt-cache search ^$n; done
