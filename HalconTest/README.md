#`Mech_Eye_Halcon_Continuous_Test.hdev`#

----------
**Halcon 连续测试例程**：  
1. 变量`run_times`为要循环的总次数。   
2. 变量`cur_times`为当前循环的次数。   
3.`error_index` 为报错发生所在的次数、`all_error_message` 为所有报错信息。   
4.`count_write_object_model_3d_error` 为`write_object_model_3d`的报错次数。  
5.`count_write_image_error`为`write_image`的报错次数。  
6.`count_grab_data_error`为`grab_data`的报错次数。  
7.`other_error`为其他错误（非`write_object_model_3d_error`、`write_image`、`grab_data`）类型。

----------

**Halcon 连续测试例程注意试项**：  
1. 交换机或直连（无局域网）。  
2. 测试主机和Viewer均设置为静态IP。  
3. 为防止出现超时，`Scan2DExposureTime` 与 `Scan3DExposureTime`均为固定值。 

----------
