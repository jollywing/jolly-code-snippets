
;;;auto-insert 开始
(setq inhibit-startup-message t);
(insert "************************************************************\n")
(insert "如需翻阅：请按CTRL+V向下翻阅,ALT+V向上翻阅\n");
(insert "************************************************************\n")
;;;auto-insert 结束

(create-file-buffer "result.txt")
(switch-to-buffer "result.txt")
(insert "正在进行一些计算，请安心等待结果....\n" )
(insert "假设在进行一些耗时的运算......\n")
(insert "假设在进行一些耗时的运算......\n")
(insert "假设在进行一些耗时的运算......\n")
(insert "假设在进行一些耗时的运算......\n")
(split-window-vertically)
(other-window 1)
(snake)