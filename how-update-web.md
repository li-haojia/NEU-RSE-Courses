# 如何更新网页内容

## 依赖
```
pip install mkdocs
```

1. 首先新建一个科目文件夹完毕，并在里面以`README.md`为文件名 建立说明文档。
2. 切换到根目录下
3. 然后运行updategitee.py (update.py 下载链接为github国内，速度慢不推荐)
4. 在终端中运行 `mkdocs gh-deploy`，更新Github端网站
   * 如果想要预览  运行`mkdocs serve`然后打开[http://127.0.0.1:8000/](http://127.0.0.1:8000/)即可实时预览