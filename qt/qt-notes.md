
# QT Notes #

## build your QT project ##
1. edit your source file;
2. `qtmake -project` to create project file;
3. `qtmake [-makefile]` to create makefile; `qtmake -config release` to create makefile of release version.
4. `make`, will create binary with default name `qt`.

## Qt半自动的内存管理 ##

在Qt中，以下情况下你new出的对象你可以不用 亲自去delete (但你应该清楚delete在何处被Qt调用的，怎么被调用的)：

- QObject及其派生类的对象，如果其parent非0，那么其parent析构时会析构该对象(本文内容围绕这一点展开 )
- QWidget及其派生类的对象，可以设置 Qt::WA_DeleteOnClose 标志位(当close时会析构该对象)
- QAbstractAnimation派生类的对象，可以设置 QAbstractAnimation::DeleteWhenStopped
- QRunnable::setAutoDelete()
- MediaSource::setAutoDelete()
- ...

## Q_OBJECT ##

The Q_OBJECT macro at the beginning of the class definition is necessary for all classes that define signals or slots

## Windows上安装QT4后更改MinGW的路径 ##

在windows上安装使用MinGW的QT4时，并不会一起安装MinGW。
在安装过程中，会让你指定已经安装的MinGW的路径。
当你使用QT4时，将使用你指定的MinGW的路径下的g++来编译构建程序。

在安装QT4之后，如果想更改MinGW的路径，在哪里更改呢。

原来在QT4的bin目录下，有一个 `qtvars.bat` 的批处理文件。
它是QT4安装时根据你的选择和输入自动生成的。
当你启动QT4的命令行提示符时，会执行这个文件，设置执行路径。

在我的 `qtvars.bat` 中有这样一行，这行设置了MinGW路径。

    set PATH=%PATH%;E:\jollywing\MinGW\bin

把 `E:\jollywing\MinGW\bin` 更改成你的MinGW下bin目录的路径，就可以了。

2014-06-11 周三
