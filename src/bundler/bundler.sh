#!/bin/bash

# set -x

BUNDLER="build/bundler"
MAPPING="$BUNDLER/mapping.h"
ASSETS_DIR="$BUNDLER/tmp/assets"

cd "$(dirname "$0")"

cd ../..
mkdir -p "$ASSETS_DIR"

ASSETS=""
for x in "obj" "png" "vert" "frag"; do
  ASSETS="$(find 'assets' -type f -name "*.$x")
$ASSETS"
done

echo -e "#pragma once\n" > "$ASSETS_DIR/assets.h"

echo -e "#pragma once

#include <bundler.h>
#include <map>
#include <assets/assets.h>

namespace Bundler {
static std::map<std::string, Asset> assets = {" > "$MAPPING"

for file in $ASSETS; do
  name="${file%%.*}.o"

  mkdir -p "$BUNDLER/tmp/$(dirname "$name")"

  if [ -f "$BUNDLER/$name" ] && [ "$BUNDLER/$name" -nt "$file" ]; then
    mv "$BUNDLER/$name" "$BUNDLER/tmp/$name"
    var_name="$(echo "$file" | tr '/\-.' '_')"
    echo "extern unsigned char $var_name[]; extern unsigned int ${var_name}_len;" >> "$ASSETS_DIR/assets.h"
    echo "ASSET(\"$file\", $var_name)", >> "$MAPPING"

    continue
  fi

  xxd -i "$file" | clang -x c -c -o "$BUNDLER/tmp/$name" -

  var_name="$(echo "$file" | tr '/\-.' '_')"
  echo "extern unsigned char $var_name[]; extern unsigned int ${var_name}_len;" >> "$ASSETS_DIR/assets.h"
  echo "ASSET(\"$file\", $var_name)", >> "$MAPPING"
done

echo "};}" >> "$MAPPING"

rm -rf "$BUNDLER/assets"
mv "$ASSETS_DIR" "$BUNDLER/assets"
rm -rf "$BUNDLER/tmp"