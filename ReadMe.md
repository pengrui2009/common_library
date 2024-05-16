代码静态检测效果示意图:

![image text](https://github.com/pengrui2009/CodereviewDemo/blob/master/view/code_static_review.png "Code Static Review")


步骤如下:

1.Ubuntu下安装clangd软件

sudo apt-get install clang clangd clang-format clang-tidy lldb lld gunpg-curl


2.vscode下安装如下插件:

clang-format

clangd



3.将下面两个文件拷贝至项目

.clang-format:代码文件格式化

.clang-tidy:代码静态语法检查

cp .clang-format projects/

cp .clang-tidy projects/


4.cmake编译(添加-DCMAKE_EXPORT_COMPILE_COMMANDS)

  #添加-DDCMAKE_EXPORT_COMPILE_COMMANDS,在编译时将生成静态规则文件 compile_commands.json,根据这个文件clang-tidy可以实现静态语法问题检查

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

