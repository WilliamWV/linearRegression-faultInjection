
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

/*
	Specification
	 
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

/**
	Modifications to selective hardening this code for fault tolerance:
		* change for indexes from int to unsigned int
		* triplicate variables 
		* include ECC on vectors of double
*/

typedef unsigned int UINT;

using namespace std;

vector<double> x; // input of training set
vector<double> y; // observed values of training set inputs
vector<double> T; // the adjustment variables

double a1, a2, a3; // triplication of alpha

UINT selectTriUInt(UINT a, UINT b, UINT c){
	return (a == b)? a : c;
}
double selectTriDouble(double a, double b, double c){
	return (a == b)? a : c;
}



bool equals(vector<double> a, vector<double> b){
	if (a.size() != b.size()) return false;
	for (UINT i1 = 0, i2 = 0, i3 = 0; 
		 selectTriUInt(i1, i2, i3)<a.size(); 
		 i1++, i2++, i3++)
	{
		if(a[selectTriUInt(i1, i2, i3)] != b[selectTriUInt(i1, i2, i3)]) 
			return false;
	}
	return true;
}

/**
	Predicts the value related to v using the Ts variables
*/
double predict(double v){
	double val = 0;
	for(UINT i1 = 0, i2 = 0, i3 = 0; 
		selectTriUInt(i1, i2, i3)<T.size(); 
		i1++, i2++, i3++)
	{
		val+= (T[selectTriUInt(i1, i2, i3)] * pow(v, selectTriUInt(i1, i2, i3)));
	}
	return val;
	
}
/**
	Calculates the mean squared error of T
*/
double meanSquaredError(){
	double error = 0;
	for(UINT i1 = 0, i2 = 0, i3 = 0; 
		selectTriUInt(i1, i2, i3)<x.size(); 
		i1++, i2++, i3++)
	{
		error+= ((predict(x[selectTriUInt(i1, i2, i3)]) - y[selectTriUInt(i1, i2, i3)]) * (predict(x[selectTriUInt(i1, i2, i3)]) - y[selectTriUInt(i1, i2, i3)]));	
	}
	error /= x.size();
	return error;

}
/**
	Calculates the partial derivate of the meanSquaredError function 
	to the adjustment variable whose position in T is passed in pos
*/
double partialDerivate(UINT pos){
	double pD = 0;
	for(UINT i1 = 0, i2 = 0, i3 = 0; 
		selectTriUInt(i1, i2, i3)<x.size(); 
		i1++, i2++, i3++)
	{
		pD += ((predict(x[selectTriUInt(i1, i2, i3)]) - y[selectTriUInt(i1, i2, i3)])*pow(x[selectTriUInt(i1, i2, i3)], pos));	
	}
	pD *= (2.0/x.size());
	return pD;
}

/**
	Adjusts the values of T 
*/
void adjust(){
	
	double PD;
	for(UINT i1 = 0, i2 = 0, i3 = 0; 
		selectTriUInt(i1, i2, i3)<T.size(); 
		i1++, i2++, i3++)
	{
		PD = partialDerivate(selectTriUInt(i1, i2, i3));
		// alpha is different from the canonical version because this works better
		T[selectTriUInt(i1, i2, i3)]= T[selectTriUInt(i1, i2, i3)] - ((selectTriDouble(a1, a2, a3) / (sqrt( fabs(PD) ))) * PD); 
	}
}

/**
	Trains the linear regression model
	* iterations: max number of iterations
	* alpha: the learning rate to adjust Ts
	* N : number of Ts used
	* stopsWhenStable: stops if T are unchanged

	P.S.: After experimental conclusions I understood that it would be better
		  if alpha was smaller to greater derivates, such that a step is not so 
		  catastrophic in local steps. So the new alpha are calculated as
			N_Alpha = alpha / (sqrt(PD))
*/
void train(UINT iterations, int N, bool stopsWhenStable = true){
	/**
		This will suppose the initial values of T as zeros
		1) Compute the meanSquaredError of current predictions
		2) Update the values of T using gradient descendent
		3) Repeat until reach the maximum number of iterations, or
		   if stopsWhenStable = true also when T stops changing 
	*/
	T = vector<double>(N, 0);
	vector<double> prevT = T; 
	vector<double> bestT = T; 
	double bestMSE = meanSquaredError();
	double MSE;	
	for(UINT i1 = 0, i2 = 0, i3 = 0;
		selectTriUInt(i1, i2, i3)<iterations; 
		i1++, i2++, i3++)
	{
		prevT = T; 	
		adjust();
		MSE = meanSquaredError();
		if (MSE < bestMSE){
			bestMSE = MSE;
			bestT = T; 
		}
		if (equals(T, prevT) && stopsWhenStable){ // implement equals
			break;		
		}
	}
	T = bestT;
}

/*
It must receive an input file formated as follows:
	1° Line : one integer T -> number of test cases
	2° to 5° repeat to all test case	
	2° Line : method parameters -> alpha, iterations, N, size of 
		      training set, predictions
	3° Line : inputs x of the training set
	4° Line : values y of the training set
	5° Line : set z of new inputs to predict*/


int main(int argc, char* argv[]){
	
	if (argc != 3) {
		cout << "Wrong number of arguments" <<endl;
		cout <<"  Use as : " << endl; 
		cout <<'\t'<<argv[0]<<" <input file> "<<"<output file>"<<endl;
		return 1;
	}
	
	ifstream inp (argv[1]);
	ofstream out (argv[2]);
		
	UINT testCases;	
	inp >> testCases;
	
	for (UINT i1 = 0, i2 = 0, i3 = 0; 
		 selectTriUInt(i1, i2, i3)<testCases; 
		 i1++, i2++, i3++)
	{
		double alpha, temp;
		UINT iterations, N, sizeOfTraining, predictions;
		inp >> alpha >> iterations >> N >> sizeOfTraining >> predictions;
		//triplication of alpha		
		a1 = alpha;
		a2 = alpha;
		a3 = alpha;
		//READING DATA
		for (UINT j1 = 0, j2 = 0, j3 = 0; 
			 selectTriUInt(j1, j2, j3)<sizeOfTraining; 
			 j1++, j2++, j3++)
		{
			inp >> temp;
			x.push_back(temp);
		} 
		for (UINT j1 = 0, j2 = 0, j3 = 0; 
			 selectTriUInt(j1, j2, j3)<sizeOfTraining; 
			 j1++, j2++, j3++)
		{
			inp >> temp;
			y.push_back(temp);
		} 
		//TRAINING
		train(iterations, N);
		//PREDICTING
		for (UINT j1 = 0, j2 = 0, j3 = 0; 
			 selectTriUInt(j1, j2, j3) < predictions; 
			 j1++, j2++, j3++){
			inp >> temp;
			out << predict(temp)<< endl;
		}
			
	}
	
	return 0;
}
