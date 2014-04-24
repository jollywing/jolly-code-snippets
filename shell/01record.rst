
==============================================
record: 一个快速记录时间使用的shell小工具
==============================================

.. contents:: 内容

作品和作者信息
==========================

:实现语言: Unix shell
:版本: 0.1.3
:许可: GPL，你可以根据自己的需要自由地修改
:作者: Jiqing Wu
:邮箱: jiqingwu@gmail.com


用途
==========================

- 记录自己一天的时间是怎么使用的，如果你觉得一天不知不觉就晃过去了，
  你就可能需要这样的工具。
- 你可能需要快速记录一些重要或有纪念意义的事，record就是个合适的工具。
- 其实，它有点像离线的微型博客。


使用帮助
==========================

- ``$record`` ，如果有当天的记录，则打印这些记录。
- ``$record your_record`` ，将 ``your_record`` 添加到今天记录。
- ``$record --help`` 或者 ``$record -h`` ，显示帮助信息。
- ``$record --version`` 或者 ``$record -v`` ，显示版本信息。
- ``$record --list`` 或者 ``$record -l`` ，列出都有哪些记录。
- ``$record --review yyyy-mm-dd`` 或者 ``$record -r yyyy-mm-dd``
  打印指定日期的记录。
- ``$record --comment your_comment`` 或者 ``$record -c your_comment``
  对刚才的记录进行评论。

当你开始使用 ``record`` 时， ``record`` 将在你的家目录下建立一个存放
记录的目录 ``RECORD`` ，如果你不喜欢这个目录，你可以修改脚本中的
``root_dir`` 变量。

如果你在2009年10月30日的12点钟添加了一条
“看电影《斗牛》”的记录， 如果记录目录下没有 ``2009-10-30`` 这个文件，
则会创建这个文件，并在该文件中添加 ``12:00 看电影《斗牛》`` 这条记录。


代码
=========================

::
 
  #! /bin/sh
  
  # name : record
  # author: Jiqing Wu
  # email: jiqingwu@gmail.com
  # version: 0.1
  # create: 2009-10-29 
  # last Update: 2010-01-22
  
  # 说明：
  # 这是我写的用于记录自己时间使用的小工具，
  # 你也可以用它快速记录一些事情，类似微博
  
  # 记录的目标文件为~/RECORD/yyyy-mm-dd
  root_dir=$HOME/blog/40pim/RECORD
  file=$root_dir/`date +%F`
  
  version()
  {
      sed -e 's/^    //' <<EndVersion
      record -- record your activities.
      version 0.1.3
      author: Jiqing Wu (jiqingwu@gmail.com)
      release date: 2009-10-29
      last updated: 2010-01-22
      License: GPL, http://www.gnu.org/copyleft/gpl.html
  EndVersion
  }
  
  help()
  {
      sed -e 's/^    //' <<EndHelp
      Usage: record [option] | [your_record]
  
      Without arguments, if there is record file of today,
      print all records of today.
  
      record your_record -- append your_record to the records of today.
  
      -v, --version: show version.
      -h, --help: show this help.
      -l, --list: list all records.
      -r date, --review date: check the records of the date.
          The format of date is yyyy-mm-dd
      -c your_comment, --comment your_comment:
          comment the last activity.
  EndHelp
  }
  
  review()
  {
      if [ -z $1 ]; then
          echo "Usage: record --review yyyy-mm-dd"
      else
          old_file=$root_dir/$1
          if [ -f $old_file ]; then
              cat $old_file
          else
              echo "There are not records of $1" 
          fi
      fi
  }
  
  comment()
  {
      if [ -z $1 ]; then
          echo "Usage: record --comment <your_comment>"
      else
          echo "      < $1 >" >> $file
      fi
  }
  
  
  if [ -z $1 ]; then
      #如果不加参数，并且目标文件不存在，显示警告信息
      if [ ! -f $file ]; then
          echo "record what?"
      #如果不加参数，并且目标文件存在，输出记录内容
      else
          cat $file
      fi
      exit 0
  fi
  
  # 如果目标文件夹不存在，建立该文件夹
  if [ ! -d $root_dir ]; then
      mkdir $root_dir
  fi
  
  case $1 in
      --help|-h) help;;
      --version|-v) version;;
      --list|-l) ls $root_dir;;
      --review|-r) review "$2";;
      --comment|-c) comment $2;;
      *) echo `date +%H:%M` $* >> $file;;
  esac
  
  exit 0


**代码的使用方法**

- 复制以上代码到一个名为record的文件中。你也可以直接在 这里_ 下载。
- chmod +x record，让record具有可执行权限。
- 把record 放入PATH变量指定的一个目录中，就可以使用record了。

.. _这里: http://code.google.com/p/girl-sword/downloads/list

