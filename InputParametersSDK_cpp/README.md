# SDK采图时间计算 #
----------
## 脚本说明： ##
基于Mech-Eye C++ SDK计算拍照时间、存图时间，用户通过手动输入2D曝光时间、3D曝光时间、模式等参数，自动采图、存图并计算时间。  

## 如何构建： ##

1. 复制InputParametersSDK_cpp文件夹所在路径
2. 打开Cmake
3. 将InputParametersSDK_cpp文件夹所在路径粘贴到source code处(where is the source code)
4. 设置构建的文件夹路径(where to build the binaries)
5. 依次点击Configure/Generate/Open Project
6. 将MainTest设置设置为首启动项
7. 在main函数中输入要连接的相机IP，并运行；

## 注意事项： ##
1. 必须使用Mech-Eye ApI。
2. visual studio 2019及其以上版本。
3. windows 端使用。