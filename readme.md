### HMI编译

#### Linux平台编译步骤

~~~
1. QT5.15，CMake版本大于3.14；
~~~

~~~
2. HMI依赖仓库
执行：git submodule init，git submodule update增加依赖仓库；
 https://git.cowarobot.com/yaoyongl/tboxhmi-common；
 https://git.cowarobot.com/yaoyongl/tbox_canserver；
~~~

~~~
3. 编译tboxhmi-common
 python3 compile.py host_tbox (host_tbox为所编译的版本)
~~~

~~~

4. 编译HMI项目
 mkdir build
 cd build
 cmake ..
 make
 结束后会在bin文件下生成可执行文件；
~~~

~~~
5. 模拟tbox发送can数据
 执行can.sh脚本创建虚拟can环境，然后安装canplayer；
 将tboxhmi-common/sdk/host_tbox/canService/bin中的CanService启动；
 执行canplayer -I can1.log可以发送模拟的can数据，ca1.log可在链接		   https://zi9wcyo1i5.feishu.cn/docs/doccnkgjHAJnXAPUL9pwHfJ1rB6中下载
~~~

6. 增加IMX8平台编译宏
cmake -DPLATFORM_IMX8=0 .. 主机环境使用
cmake -DPLATFORM_IMX8=1 .. IMX8环境使用

7. CMakeLists.txt 增加版本号及编译时间宏（BUILD_VERSION，BUILD_TIME）