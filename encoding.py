import numpy as np 
import cv2
import tensorflow as tf
from tensorflow.contrib.layers import fully_connected

np.random.seed(7)

img_height = 84 # px
img_width = 52 # px
channels = 1

num_inputs = img_height * img_width * channels

x = tf.placeholder(tf.float32, [None, img_height * img_width * channels], name = 'InputData')


def conv2d(input, name, kshape, strides = [1, 1, 1, 1]):
	with tf.name_scope(name):
		W = tf.get_variable(name = 'w_' + name, 
							shape = kshape,
							initializer = tf.contrib.layers.xavier_initializer(uniform = False))
		b = tf.get_variable(name = 'b_' + name,
							shape = [kshape[3]],
							initializer = tf.contrib.layers.xavier_initializer(uniform = False))
		out = tf.nn.conv2d(input, W, strides = strides, padding = 'SAME')
		out = tf.nn.bias_add(out, b)
		out = tf.nn.relu(out)
		return out

def deconv2d(input, name, kshape, n_outputs, strides = [1, 1]):
	with tf.name_scope(name):
		out = tf.contrib.layers.conv2d_transpose(input,
												num_outputs = n_outputs,
												kernel_size = kshape,
												stride = strides,
												padding = 'SAME',
												weights_initializer = tf.contrib.layers.xavier_initializer_conv2d(uniform = False),
												biases_initializer = tf.contrib.layers.xavier_initializer(uniform = False),
												activation_fn = tf.nn.relu)
		return out

def maxpool2d(x, name, kshape = [1, 2, 2, 1], strides = [1, 2, 2, 1]):
	with tf.name_scope(name):
		out = tf.nn.max_pool(x, 
							ksize = kshape,
							strides = strides, 
							padding = 'SAME')

def upsample(input, name, factor = [2, 2]):


def ConvAutoEncoder(x, name):
	with tf.name_scope(name):
		c1 = conv2d(input, name = 'c1', kshape = [5, 5, 1, 25])





