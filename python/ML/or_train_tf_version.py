import tensorflow as tf
import numpy as np

# placeholder
x_placeholder = tf.placeholder(tf.float32, shape=(1, 2))
y_placeholder = tf.placeholder(tf.float32, shape=(1, 1))
# variables
weights = tf.Variable([[0.5],[0.5]], name='weights')
bias = tf.Variable(0.0, name='bias')
# w.x +b, w: (2, 1), y: (1,), b:(1,)
y = tf.sigmoid(tf.matmul(input_iter, weights) + bias)

cost = (y - y_placeholder) * (y - y_placeholder)
loss = tf.reduce_mean(cost_list)
init = tf.initialize_all_variables()
optimizer = tf.train.GradientDescentOptimizer(1.0)
sess.run(init)
sess = tf.Session()
result = sess.run(op)
epoch = 0
step = 0
while epoch < 2000:
    optimizer.minimize(loss)
    step += 1
    if step % 4 == 0:
        epoch += 1
    if step % 100 == 0:
        print(loss)

sess.close()
