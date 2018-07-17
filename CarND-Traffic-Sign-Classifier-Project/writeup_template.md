# **Traffic Sign Recognition** 

## Writeup

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report


[//]: # (Image References)

[image1]: https://github.com/Van-Vu/car/blob/master/CarND-Traffic-Sign-Classifier-Project/writeup/distribution1.jpg "Distribution 1"
[image2]: https://github.com/Van-Vu/car/blob/master/CarND-Traffic-Sign-Classifier-Project/writeup/distribution2.jpg "Distribution 2"
[image3]: https://github.com/Van-Vu/car/blob/master/CarND-Traffic-Sign-Classifier-Project/writeup/GrayScaling.jpg "Grayscaling"
[image4]: ./examples/placeholder.png "Traffic Sign 1"
[image5]: ./examples/placeholder.png "Traffic Sign 2"
[image6]: ./examples/placeholder.png "Traffic Sign 3"
[image7]: ./examples/placeholder.png "Traffic Sign 4"
[image8]: ./examples/placeholder.png "Traffic Sign 5"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf. You can use this template as a guide for writing the report. The submission includes the project code.

You're reading it! and here is a link to my [project code](https://github.com/udacity/CarND-Traffic-Sign-Classifier-Project/blob/master/Traffic_Sign_Classifier.ipynb)

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the pandas library to calculate summary statistics of the traffic
signs data set:

Number of training examples = **34799**

Number of validation examples = **4410**

Number of testing examples = **12630**

Image data shape = **(32, 32, 3)**

Number of classes = **43**

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. It is a bar chart showing the data is unbalanced

![alt text][image1]

![alt text][image2]

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

As a first step, I decided to convert the images to grayscale because it gives better accuracy from my experiment below, it's also inline with Yan Lecun [paper](http://yann.lecun.com/exdb/publis/pdf/sermanet-ijcnn-11.pdf):"The ConvNet was trained with full supervision on the color images of the GTSRB dataset and reached 98.97% accuracy on the phase 1 test set. After the end of phase 1, additional experiments with grayscale images established a new record accuracy of 99.17%"

Here is an example of a traffic sign image before and after grayscaling then normalized the image data

![alt text][image3]

I normalized the image data because it ensures that each pixel has a similar data distribution. This makes convergence faster while training the network

#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x1 Gray image   							| 
| Convolution 5x5     	| 1x1 stride, 'VALID' padding, outputs 28x28x40	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x40 				|
| Convolution 5x5     	| 1x1 stride, 'VALID' padding, outputs 10x10x64	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x64   				|
| Flatten		      	| output: 1600					   				|
| Fully connected		| output: 1000 									|
| Fully connected		| output: 500  									|
| Fully connected		| output: 200  									|
| Softmax				| logits: 43   									|


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

I used Lenet architecture with following hyperparameters:
AdamOptimizer
BATCH_SIZE = 128

Bodom1: EPOCHS = 50
Image type: RGB
Convo1: 40
Convo2: 20
FC1=500 → 300
FC2=300 → 200
FC3=200 → 100
Learningrate = 0.001

Bodom9: EPOCHS = 100
Image type: RGB
Convo1: 40
Convo2: 20
FC1=500 → 300
FC2=300 → 200
FC3=200 → 100
Learningrate = 0.005

Bodom 10:
EPOCHS = 100
Image type: RGB
Convo1: 40
Convo2: 20
FC1=500 → 300
FC2=300 → 200
FC3=200 → 100
Learningrate = 0.0001

Bodom11:
EPOCHS = 100
Image type: RGB
Convo1: 40
Convo2: 20
FC1=500 → 300
FC2=300 → 200
FC3=200 → 100
Learningrate = 0.001

Bodom2: EPOCHS = 50
Image type: RGB
convo1=40
convo2= 60
FC1=1500 → 1000
FC2=1000 → 500
FC3=500 → 200
Learningrate = 0.001

Bodom3: EPOCHS = 50
Image type: RGB
convo1=32
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200
Learningrate = 0.001

Bodom4: EPOCHS = 50
Image type: RGB
convo1=32
convo2= 64
Learningrate = 0.001
FC1=1600 → 800
FC2=800 → 200

Bodom5: EPOCHS = 50
Learningrate = 0.001
Image type: RGB
convo1=40
convo2= 64
FC1=1600 → 500

Bodom 6: EPOCHS = 100
Learningrate = 0.001
Image type: RGB
convo1=40
convo2= 64
FC1=1600 → 500

Bodom7: EPOCHS = 50
Learningrate = 0.001
Image type: RGB
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200

Bodom12: 
EPOCHS = 50
Learningrate = 0.001
Image type: Gray
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200


Bodom13:
EPOCHS = 50
Learningrate = 0.0001
Image type: Gray
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200

Bodom14:
EPOCHS = 50
Learningrate = 0.0005
Image type: Gray
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200

Bodom15:
EPOCHS = 50
Learningrate = 0.0005
Image type: Gray
DROPOUT 0.5
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200

Bodom16:
EPOCHS = 100
Learningrate = 0.0005
Image type: Gray
DROPOUT 0.5
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200

Bodom17:
EPOCHS = 200
Learningrate = 0.0005
Image type: Gray
DROPOUT 0.5
convo1=40
convo2= 64
FC1=1600 → 1000
FC2=1000 → 500
FC3=500 → 200



#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

My final model results were:
* training set accuracy of ?
* validation set accuracy of ? 
* test set accuracy of ?

If an iterative approach was chosen:
* What was the first architecture that was tried and why was it chosen?
* What were some problems with the initial architecture?
* How was the architecture adjusted and why was it adjusted? Typical adjustments could include choosing a different model architecture, adding or taking away layers (pooling, dropout, convolution, etc), using an activation function or changing the activation function. One common justification for adjusting an architecture would be due to overfitting or underfitting. A high accuracy on the training set but low accuracy on the validation set indicates over fitting; a low accuracy on both sets indicates under fitting.
* Which parameters were tuned? How were they adjusted and why?
* What are some of the important design choices and why were they chosen? For example, why might a convolution layer work well with this problem? How might a dropout layer help with creating a successful model?

If a well known architecture was chosen:
* What architecture was chosen? Lenet
* Why did you believe it would be relevant to the traffic sign application?
LeNet is a 7-level convolutional network designed for handwritten and machine-printed character recognition. It uses convolution to extract spatial image features (in this case the traffic sign) at multiple location. The convolution layers reduce the number of parameters so the fully-connected layers can be used as final classifier without requiring large training set and computational power
Here is an example of LeNet-5 in action. 
* How does the final model's accuracy on the training, validation and test set provide evidence that the model is working well?


### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs that I found on the web:

![alt text][image4] ![alt text][image5] ![alt text][image6] 
![alt text][image7] ![alt text][image8]

The first image might be difficult to classify because ...

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| Stop Sign      		| Stop sign   									| 
| U-turn     			| U-turn 										|
| Yield					| Yield											|
| 100 km/h	      		| Bumpy Road					 				|
| Slippery Road			| Slippery Road      							|


The model was able to correctly guess 4 of the 5 traffic signs, which gives an accuracy of 80%. This compares favorably to the accuracy on the test set of ...

#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. (OPTIONAL: as described in the "Stand Out Suggestions" part of the rubric, visualizations can also be provided such as bar charts)

The code for making predictions on my final model is located in the 11th cell of the Ipython notebook.

For the first image, the model is relatively sure that this is a stop sign (probability of 0.6), and the image does contain a stop sign. The top five soft max probabilities were

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .60         			| Stop sign   									| 
| .20     				| U-turn 										|
| .05					| Yield											|
| .04	      			| Bumpy Road					 				|
| .01				    | Slippery Road      							|


For the second image ... 

### (Optional) Visualizing the Neural Network (See Step 4 of the Ipython notebook for more details)
#### 1. Discuss the visual output of your trained network's feature maps. What characteristics did the neural network use to make classifications?


