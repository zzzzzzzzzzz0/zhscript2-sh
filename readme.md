# 中文脚本 zhscript 第二版的 sh（外壳）

第二版能够兼容第一版的外壳，反之不然

[gtksh](gtksh/) 是第一版中 gtkmmsh 的实现方式（主程序 + 插件）的回归，
当初 gtkmmsh 为摆脱 gtkmm 版本依赖、界面可以不必由描述文件而分成 vtesh、webkitsh、srcvwsh、cairogsh（写程序最后一个顿号不用“和”），
但带来的问题便是像 edit_zs 这样的复合界面的应用无法去实现，
[gtksh-plugin](gtksh/plugin/) 里包括 vte、webkit、src、cairog，也将写法从“使主窗、居中。”简化为“使居中。”