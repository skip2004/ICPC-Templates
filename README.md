# ICPC-Template
我的 ICPC 常用模板。

这里是[内容的简单解读](https://www.cnblogs.com/skip2004/p/19196741)：

## 目录说明
源代码位于 `./contents/` 目录中。  

LaTeX（TeX）源码位于 `./main.tex` 中。

## 使用环境与依赖

本项目使用 LaTeX 的 `minted/minted2` 宏包进行代码高亮，需要额外安装 Python 依赖：

```bash
pip install Pygments
```

在编译 TeX 文件时，需要在参数中加入 `-shell-escape` 来支持执行高亮渲染。

## 字体
需要自行安装 [Fira Code](https://github.com/tonsky/FiraCode)。

## 致谢

本项目基于 [fstqwq/Nemesis](https://github.com/fstqwq/Nemesis) 进行整理与扩展。
 
