Step:

1. install vscode plugin:

clang-format

clangd

2. apt install clangd

sudo apt-get install clangd

3. cp files to projects

cp .clang-format projects/

cp .clang-tidy projects/


4. cmake编译(添加-DCMAKE_EXPORT_COMPILE_COMMANDS)

  #添加-DDCMAKE_EXPORT_COMPILE_COMMANDS,在编译时将生成静态规则文件 compile_commands.json,根据这个文件clang-tidy可以实现静态语法问题检查

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

