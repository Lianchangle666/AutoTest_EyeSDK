
# testSDKParameters 项目概述

----------

本项目基于MechEye SDK，采用cmake的构建方式，主要通过向相机输入正常参数、异常参数来检查相机参数是否存在异常。所有参数通过文件夹中的data.csv中读取，csv中包括所有参数测试用例（包括LSR/Laser/Uhp等相机），脚本运行成功后，会在项目目录下生成一个名为result.csv的简易测试报告。



## 如何构建： ##
1. 复制testSDKParameters文件夹所在路径
2. 打开Cmake
3. 将testSDKParameters文件夹所在路径粘贴到source code处(where is the source code)
4. 设置构建的文件夹路径(where to build the binaries)
5. 点击Configure/Generate/Open Project
6. 将MainTest设置设置为首启动项
7. 在main函数中connect函数后输入要连接的相机IP，并运行；
8. 脚本运行成功后，会在项目目录下生成一个名为result.csv的测试报告。



## 注意事项： ##
1. 必须使用Mech-Eye ApI。
2. 通过set参数来对比get出的数值是否正常。
3. 如下一次执行，需将result.csv删除或从项目中移除，下次运行的结果会接在已存在result.csv之后。


## data.csv说明： ##
1. TestCase：参数测试用例名称
2. setParameters：用于传入set函数中的参数
3. getParameters：理论应get出来的值
4. isboundaryvalue：setParameters传入的参数是否是合法值，合法值是ok，非法值是error



## result.csv说明： ##
1. TestCase：参数测试用例名称
2. Set：传入set函数中的参数
3. Get：实际get出来的值
4. Result：pass表示测试通过，fail表示测试不通过
5. ReturnMsgs：返回的错误码，及报错信息


## 目录结构： ##
testSDKParameters   
│   
│&ensp; CMakeLists.txt  
│&ensp; data.csv  
│&ensp; MainTest.cpp  
│  
└─include  
&emsp; &emsp; &emsp; Func.h  
&emsp; &emsp; &emsp; readCSV.h