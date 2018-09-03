
#include<iostream>
#include<fstream>
#include<vector>

/*
	Specifications
	It must receive an imput file formated as follows:
	1° Line : one integer T -> number of test cases
	2° to 5° repeat to all test case	
	2° Line : method parameters
	3° Line : inputs x of the training set
	4° Line : values y of the training set
	5° Line : set z of new inputs to predict
	 
	The objective of the agent is to predict the function f 
	that maps x to y minimizing the mean squared error, such that
	f(x) = T0 + T1*x + T2*x² + ... + Tn*x^n
	
	To accomplish this, the method may use a performance function
	to say how well the prediction is doing, this is based on the 
	training set, that is the difference between f(x) and y

	This error function is given by:
	E(T0, T1, T2, ..., TN) = (1/M) * sum(i = 1:M, (f(xi) - yi)²)
	And M is the size of the training set while N is the number of 
	variables to ajust 
	
	So the agent's goal summarizes to determine the set of Ts that 
	minimizes the function E. To do this the agent uses the 
	gradient method, where the update of each T can be calculated
	based on the partial derivative of function E to this var
	

*/
using namespace std;

vector<double> x; // input of training set
vector<double> y; // observed values of training set inputs

double bestMSE;
/**
	Calculates the mean squared error of 
	the input vector T considering x and y as the training set
*/
double meanSquaredError(vector<double> T);
/**
	Calculates the partial derivate of the meanSquaredError function 
	to the adjustment variable whose position in T is passed in pos
*/
double partialDerivate(vector<double> T, int pos);

/**
	Adjusts the value of Theta of position pos using alpha as learning 
	rate
*/
vector<double> adjust(vector<double> T, int pos, double alpha);

void train(){
	/**
		This will suppose the initial values of T as zeros
		1) Compute current predictions to X
		2) Compute the meanSquaredError 
		3) Update the values of T using gradient descendent
		4) Repeat until the meanSquaredError stop decreasing or until 			   reach the maximun number of iterations
	*/
	
}

int main(){
	return 0;
}
