步骤如下:

1.vscode下安装如下插件:

clang-format

clangd

2.Ubuntu下安装clangd软件

sudo apt-get install clangd

3.将下面两个文件拷贝至项目

.clang-format:代码文件格式化

.clang-tidy:代码静态语法检查

cp .clang-format projects/

cp .clang-tidy projects/


4.cmake编译(添加-DCMAKE_EXPORT_COMPILE_COMMANDS)

  #添加-DDCMAKE_EXPORT_COMPILE_COMMANDS,在编译时将生成静态规则文件 compile_commands.json,根据这个文件clang-tidy可以实现静态语法问题检查

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

