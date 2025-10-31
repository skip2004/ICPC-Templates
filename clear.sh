#!/usr/bin/env bash
# 清理 LaTeX 辅助文件与缓存目录（minted、build 等）

# 删除常见 LaTeX 临时文件
rm -f *.aux *.toc *.out *.lof *.lot *.bbl *.blg *.fdb_latexmk *.fls *.log *.synctex.gz

# 定义需要清空的缓存目录
CACHE_DIRS=(
  "_minted"
  "minted-cache"
  "build"
  ".auxdir"
)

# 遍历清理这些目录中的内容
for dir in "${CACHE_DIRS[@]}"; do
  if [ -d "$dir" ]; then
    rm -rf "$dir"/*
    echo "🧹 Cleared contents of $dir/"
  else
    echo "⚠️  $dir/ not found, skipped."
  fi
done

echo "✅ Finished cleaning LaTeX auxiliary files and caches."

