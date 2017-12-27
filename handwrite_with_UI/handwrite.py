# -*- coding:utf-8
import numpy
import struct
import math
import random
from PIL import Image

class Bpnet(object):
	"""bp NN to fit the handwrite"""
	def __init__(self):
		super(Bpnet, self).__init__()
		self.first = 784
		self.second = 50
		self.third = 10
		self.alpha = 0.35
		self.mu = 0.05

		self.input = numpy.zeros(self.first)
		self.hide = numpy.zeros(self.second)
		self.output = numpy.zeros(self.third)

		self.target = numpy.zeros(self.third)
		self.weight1 = numpy.zeros((self.first, self.second))
		self.weight2 = numpy.zeros((self.second, self.third))
		self.threshold1 = numpy.zeros(self.second)
		self.threshold2 = numpy.zeros(self.third)
		self.delta1 = numpy.zeros(self.second)
		self.delta2 = numpy.zeros(self.third)
		self.last_delta1 = numpy.zeros(self.second)
		self.last_delta2 = numpy.zeros(self.third)

	def sigmoid(self, x):
		return 1.0/(1.0 + math.exp(-x))

	def initial(self):
		for i in range(self.first):
			for j in range(self.second):
				self.weight1[i][j] = random.random() - 0.5
		for i in range(self.second):
			for j in range(self.third):
				self.weight2[i][j] = random.random() - 0.5
		for i in range(self.second):
			self.threshold1[i] = random.random() - 0.5
		for i in range(self.third):
			self.threshold2[i] = random.random() - 0.5

	def envalue1(self):
		for i in range(self.second):
			self.hide[i] = 0
			#for j in range(self.first):
			#	self.hide[i] += self.weight1[j][i]*self.input[j]
			trans = numpy.transpose(self.weight1)
			self.hide[i] = numpy.dot(self.input, trans[i][:])
			self.hide[i] += self.threshold1[i]
			self.hide[i] = self.sigmoid(self.hide[i])

	def envalue2(self):
		for i in range(self.third):
			self.output[i] = 0
			#for j in range(self.second):
			#	self.output[i] += self.weight2[j][i]*self.hide[j]
			trans = numpy.transpose(self.weight2)
			self.output[i] = numpy.dot(self.hide, trans[i][:])
			self.output[i] += self.threshold2[i]
			self.output[i] = self.sigmoid(self.output[i])

	def delta_output(self):
		for i in range(self.third):
			self.delta2[i] = (self.output[i] - self.target[i])*self.output[i]*(1.0 - self.output[i]) + self.mu*self.last_delta2[i]
			self.last_delta2[i] = self.delta2[i]

	def delta_hide(self):
		for i in range(self.second):
			sigma = 0
			#for j in range(self.third):
			#	sigma += self.delta2[j]*self.weight2[i][j]
			sigma = numpy.dot(self.delta2, self.weight2[i][:])
			self.delta1[i] = sigma*self.hide[i]*(1.0 - self.hide[i]) + self.mu*self.last_delta1[i]
			self.last_delta1[i] = self.delta1[i]

	def traceback1(self):
		for i in range(self.second):
			#for j in range(self.third):
			#	self.weight2[i][j] -= self.alpha*self.delta2[j]*self.hide[i]
			self.weight2[i][:] = self.weight2[i][:] - self.alpha*self.hide[i]*self.delta2
		for i in range(self.third):
			self.threshold2[i] -= self.alpha*self.delta2[i];

	def traceback2(self):
		for i in range(self.first):
			#for j in range(self.second):
			#	self.weight1[i][j] -= self.alpha*self.delta1[j]*self.input[i]
			self.weight1[i][:] =  self.weight1[i][:] - self.alpha*self.input[i]*self.delta1
		for i in range(self.second):
			self.threshold1[i] -= self.alpha*self.delta1[i]

	def train(self):
		#读取minist到train_buf和label_buf
		test_count = 0;
		image_train = open('train-images.idx3-ubyte', 'rb')
		image_label = open('train-labels.idx1-ubyte', 'rb')
		train_buf = image_train.read()
		image_train.close()
		label_buf = image_label.read()
		image_label.close()
		#解析图像的label
		label_index = 0
		magic, train_label_num = struct.unpack_from('>II', label_buf, label_index)
		print (magic, ' ', train_label_num)
		label_index += struct.calcsize('>II')
		#解析训练图像train_buf
		train_index = 0
		magic, train_img_num, numRows, numColums = struct.unpack_from('>IIII', train_buf, train_index)
		print (magic, ' ', train_img_num, ' ', numRows, ' ', numColums)
		train_index += struct.calcsize('>IIII')
		#读取每一个图像信息
		for i in range(train_img_num):
        	#image
			im = struct.unpack_from('>784B', train_buf, train_index)
			train_index += struct.calcsize('>784B')
			im = numpy.array(im)
			im = im.reshape(1, 28*28)
            #label
			label_item = int(struct.unpack_from('>B', label_buf, label_index)[0])
			label_index += struct.calcsize('>B')
            #设置target和input
			for k in range(self.third):
				self.target[k] = 0
			self.target[label_item] = 1
			for k in range(self.first):
				if im[0][k] < 128:
					self.input[k] = 0
				else:
					self.input[k] = 1
			self.envalue1();
			self.envalue2();
			self.delta_output();
			self.delta_hide();
			self.traceback1();
			self.traceback2();
			test_count += 1
			if test_count%1000 == 0:
				print('test count is ', test_count)
		print('done!')

	def test(self):
		#读取minist test到test_buf和label_buf
		test_count = 0
		success_count = 0
		image_test = open('t10k-images.idx3-ubyte', 'rb')
		test_label = open('t10k-labels.idx1-ubyte', 'rb')
		try:
			test_buf = image_test.read()
		finally:
			image_test.close()
		try:
			test_label_buf = test_label.read()
		finally:
			test_label.close()
		#解析测试图像的label
		label_index = 0
		magic, test_label_num = struct.unpack_from('>II', test_label_buf, label_index)
		print (magic, ' ', test_label_num)
		label_index += struct.calcsize('>II')
		#解析测试图像train_buf
		train_index = 0
		magic, test_img_num, numRows, numColums = struct.unpack_from('>IIII', test_buf, train_index)
		print (magic, ' ', test_img_num, ' ', numRows, ' ', numColums)
		train_index += struct.calcsize('>IIII')
		#读取每一个图像信息
		for i in range(test_img_num):
			#image
			im = struct.unpack_from('>784B', test_buf, train_index)
			train_index += struct.calcsize('>784B')
			im = numpy.array(im)
			im = im.reshape(1, 28*28)
			#label
			label_item = int(struct.unpack_from('>B', test_label_buf, label_index)[0])
			label_index += struct.calcsize('>B')
			#输入input
			for k in range(self.first):
				if im[0][k] < 128:
					self.input[k] = 0
				else:
					self.input[k] = 1
			#检查输出是否match
			self.envalue1();
			self.envalue2();
			max_value = -100000
			max_index = -1
			for k in range(self.third):
				if self.output[k] > max_value:
					max_value = self.output[k]
					max_index = k
			if int(max_index) == int(label_item):
				success_count += 1
			test_count += 1
			if test_count%100 == 0:
				print(success_count, ' ', test_count)
		rate = success_count/test_img_num
		print('success_rate is ', rate)

	def inputAndTest(self, path):
		im = Image.open(path)
		im = im.convert('L')
		im = numpy.array(im)
		for i in range(28):
			for j in range(28):
				if im[i][j] >= 128:
					im[i][j] = 0
				else:
					im[i][j] = 1
		im = im.reshape(1, 28*28)
		for i in range(self.first):
			self.input[i] = im[0][i]
		#for i in range(28):
		#	for j in range(28):
		#		print(self.input[i*28+j], end='')
		#	print(' ')
		self.envalue1()
		self.envalue2()
		max_value = -100000
		max_index = -1
		for k in range(self.third):
			if self.output[k] > max_value:
				max_value = self.output[k]
				max_index = k
		print('we get ', max_index)
		return max_index

