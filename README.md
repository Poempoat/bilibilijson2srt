# Bilibili JSON to SRT

将哔哩哔哩CC字幕（JSON格式）转换为SRT格式。

## 使用

从[Releases](https://github.com/Poempoat/bilibilijson2srt/releases)中下载最新构建。

    Usage: your_program -i input_file [-o output_file]
    
    Example:
     json2srt -i input.json -o output.srt

将`your_program`替换为实际的程序名称

如果不指定`-o`参数，默认在同一文件内生成同名srt文件。

## 构建

使用`g++`进行构建编译

    g++ ./json2srt.cpp -o json2srt -static

注意：在Termux环境下不要使用`-static`参数。

## 如何获取CC字幕JSON？

使用PC浏览器访问视频，按下F12，点击网络选项卡并刷新网页，打开CC字幕，搜索`subtitle`，选中json文件，复制链接，下载。

![screenshot](https://raw.githubusercontent.com/Poempoat/bilibilijson2srt/main/screenshot.png)

## 许可证

该项目采用 [MIT许可证](https://raw.githubusercontent.com/Poempoat/bilibilijson2srt/main/LICENSE)。
