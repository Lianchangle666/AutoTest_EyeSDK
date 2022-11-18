#`Mech_Eye_Halcon_Continuous_Test.hdev`#

----------
**Halcon 连续测试例程**：  
1. 无限循环  
2. 变量count为循环次数  
3.` Error_index` 为报错次数、`ErrorMessage` 为报错信息、`Error_grabtime` 为报错持续时间。

**Halcon 连续测试例程注意试项**：  
1. 交换机或直连（无局域网）  
2. 测试主机和Viewer均设置为静态IP  
3. 为防止出现超时，`Scan2DExposureTime` 与 `Scan3DExposureTime`均为固定值