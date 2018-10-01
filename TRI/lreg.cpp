
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

//struct that holds all elements of the answer, each one of the execution
//of the triplification will returns one of these 
typedef struct answer{
	//all elements are inside a vector because will return one to each test case
	vector<vector <double>> predictions;	//results of the values to predict
	vector<vector <bool>> crashes;			//says if there is crash on some prediction
	vector<vector <double>> thetas;			//thetas trained
	vector<bool> crashOnTrain;				//there is crash on train?
}ANS;

using namespace std;

vector<double> x; // input of training set
vector<double> y; // observed values of training set inputs
vector<double> T; // the adjustment variables

bool equals(vector<double> a, vector<double> b){
	if (a.size() != b.size()) return false;
	for (int i = 0; i<a.size(); i++){
		if(a[i] != b[i]) return false;
	}
	return true;
}

/**
	Predicts the value related to v using the Ts variables
*/
double predict(double v){
	double val = 0;
	for(int i = 0; i<T.size(); i++){
		val+= (T[i] * pow(v, i));
	}
	return val;
	
}
/**
	Calculates the mean squared error of T
*/
double meanSquaredError(){
	double error = 0;
	for(int i = 0; i<x.size(); i++){
		error+= ((predict(x[i]) - y[i]) * (predict(x[i]) - y[i]));	
	}
	error /= x.size();
	return error;

}
/**
	Calculates the partial derivate of the meanSquaredError function 
	to the adjustment variable whose position in T is passed in pos
*/
double partialDerivate(int pos){
	double pD = 0;
	for(int i = 0; i<x.size(); i++){
		pD += ((predict(x[i]) - y[i])*pow(x[i], pos));	
	}
	pD *= (2.0/x.size());
	return pD;
}

/**
	Adjusts the values of T 
*/
void adjust(double alpha){
	
	double PD;
	for(int i = 0; i<T.size(); i++){
		PD = partialDerivate(i);
		// alpha is different from the canonical version because this works better
		T[i]= T[i] - ((alpha / (sqrt( fabs(PD) ))) * PD); 
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
void train(int iterations, double alpha, int N, bool stopsWhenStable = true){
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
	for(int i = 0; i<iterations; i++){
		prevT = T; 	
		adjust(alpha);
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

void saveTs(ofstream& out){
	out<<"Thetas: "<<endl;
	for (int i = 0; i<T.size(); i ++){
		out<<'\t'<<'T'<<i<<" = "<<T[i];
	}
	out<<endl;
	out<<"Mean Squared Error: " << meanSquaredError()<<endl;
}

ANS lreg(char* input, char* output){
	ANS *answer;
	
	ifstream inp (input);
	ifstream out (output);
	unsigned int testCases;	
	inp >> testCases;
	
	for (int i = 0; i<testCases; i++){
		try{
			double alpha, temp;
			int iterations, N, sizeOfTraining, predictions;
			inp >> alpha >> iterations >> N >> sizeOfTraining >> predictions;
			
			//READING DATA
			for (int j = 0; j<sizeOfTraining; j++){
				inp >> temp;
				x.push_back(temp);
			} 
			for (int j = 0; j<sizeOfTraining; j++){
				inp >> temp;
				y.push_back(temp);
			} 
			//TRAINING
			train(iterations, alpha, N);
			answer->thetas.push_back(T);
			answer->crashOnTrain.push_back(false);
		}catch (exception& e){
			//error on training
			answer->crashOnTrain.push_back(true);
		}
		for (int j = 0; j < predictions; j++){
			inp >> temp;
			out << "f("<<temp<<") = "<<predict(temp)<< endl;
		}
	}
	return answer;
	
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
	
	
	return 0;
}
