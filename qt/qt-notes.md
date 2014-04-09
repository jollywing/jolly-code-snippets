
# QT Notes #

## build your QT project ##
1. edit your source file;
2. `qtmake -project` to create project file;
3. `qtmake [-makefile]` to create makefile;
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
