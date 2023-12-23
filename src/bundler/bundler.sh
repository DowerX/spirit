#!/bin/bash

MAPPING="build/bundler/mapping.h"
HEADERS="build/bundler"

cd "$(dirname "$0")"

cd ../..
mkdir -p build/bundler/assets

ASSETS=""
for x in "obj" "png" "vert" "frag"; do
  ASSETS="$(find . -type f -name "*.$x")
$ASSETS"
done

echo -e "#pragma once\n" > $HEADERS/assets/assets.h

echo -e "#pragma once

#include <bundler.h>
#include <map>
#include <assets/assets.h>

namespace Bundler {
static std::map<std::string, Asset> assets = {" > $MAPPING

for x in $ASSETS; do
  file="${x:2}"
  
  header="${file%%.*}.c"
  mkdir -p "$HEADERS/$(dirname $header)"
  xxd -i "$file" > "$HEADERS/$header"


  var_name="$(echo "$file" | tr '/\-.' '_')"
  echo "extern unsigned char $var_name[]; extern unsigned int ${var_name}_len;" >> $HEADERS/assets/assets.h
  echo "ASSET(\"$file\", $var_name)", >> $MAPPING
done

echo "};}" >> $MAPPING