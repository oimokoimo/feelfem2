#!/bin/sh

makedate=`date`

cat <<EOT
// This may look like C code, but it is really -*- C++ -*-

// #include "makedate.h"

char* makedate = "${makedate}";
EOT
