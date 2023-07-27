### HMI 编译

#### Linux 平台编译步骤

```
1. QT5.15，CMake版本大于3.14；
```

```
2. HMI依赖仓库
执行：git submodule init，git submodule update增加依赖仓库；
 https://git.cowarobot.com/yaoyongl/tboxhmi-common；
 https://git.cowarobot.com/yaoyongl/tbox_canserver；
```

```
3. 编译tboxhmi-common
 python3 compile.py host_tbox (host_tbox为所编译的版本)
```

```

4. 编译HMI项目
 mkdir build
 cd build
 cmake ..
 make
 结束后会在bin文件下生成可执行文件；
```
