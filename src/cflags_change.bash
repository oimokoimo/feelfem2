#!/bin/bash

# ルートディレクトリで実行

# 例: feelfem2/src など

echo "=== Updating CFLAGS in */Makefile ==="

find . -name Makefile | while read mf; do
echo "Processing: $mf"

```
# バックアップ
cp "$mf" "$mf.bak"

# CFLAGS行を書き換え
sed -i \
    -e 's/-fsanitize=address//g' \
    -e 's/-O0/-O2/g' \
    "$mf"

# CFLAGSが存在しない場合は追加（念のため）
if ! grep -q "^CFLAGS" "$mf"; then
    echo 'CFLAGS = -O2 -g' >> "$mf"
fi
```

done

echo "=== Done ==="

