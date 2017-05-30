# NeuralNet-QT

MultiLayerPerceptron with backpropagation alghorithm. Interface made in QtCreator.

You can choose net topology and activation function type and beta parameter. There are two learning options : online (weights corrected after signgle sample) and batch option (weights are corrected when all samples are shown in random order)

Setting input data :

Input data format :

a1, a2 a3 a4 .... an

b1 b2 b3 b4 ... bn

....
where a and b vectors are training samples with n numbers.

Ouput format is the same :

Ta1 Ta2 ... Tam

Tb1 Tb2 ... Tbm

....
where Ta and Tb are target vectors with m samples.

Example : 

XOR problem : 

Inputs.txt : 
0 0
0 1
1 0
1 1

Targets.txt
0
1
1
0


After training you can type single vector of n (same size as training sample) values to feedfoward it and see the results.

TODO : 
- improvment alghoritm - very poor performence for bigger data, net is not learning 
- improvment alghoritm - improve learning time
- sometimes net with logistic activation function not working

