调用方法:
创建神经网络 							bp = handwrite.Bpnet()
训练	(时间2-3分钟)					bp.train()
使用minist测试 						bp.test()
输入图片路径 要求28 * 28并得到预测 	bp.inputAndTest()

train里为可供读入并测试的图片