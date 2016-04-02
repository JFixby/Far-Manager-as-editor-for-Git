# Far Manager as editor for Git

When you're using [Far Manager](http://www.farmanager.com) as Git
editor, you can't do it when you're using Bash ([Cannot run Far from
Git Bash](https://forum.farmanager.com/viewtopic.php?t=9926)).

This utility allows you to fix it. Just configure your Git as follow:

```
[core]
    editor = ~/farexec.exe /d/far/far.exe -e0:0
```

where

* `~/farexec.exe` is this utility,
* `/d/far/far.exe` is Far file manager installation path.
    