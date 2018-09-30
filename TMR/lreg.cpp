////////////////////////////////////////////////////////////////////////////////
/// THIS VERSION OF THE CODE USES TRIPLICATION TO AVOID FAILURES             ///
////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<exception>

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
using namespace std;

vector<double> x; // input of training set
vector<double> y; // observed values of training set inputs
vector<double> T; // the adjustment variables

int equals(vector<double> a, vector<double> b){
	if (a.size() != b.size()) return 0;
	for (unsigned int i = 0; i<a.size(); i++){
		if(a[i] != b[i]) return 0;
	}
	return 1;
}

/**
	Predicts the value related to v using the Ts variables
*/
double predict(double v){
	bool crashV1 = false, crashV2 = false, crashV3 = false;
	//ALSO TRIPLICATED
	double val1 = 0, val2 = 0, val3 = 0;	
	try{
		val1 = 0;
		for(unsigned int i = 0; i<T.size(); i++){
			val1+= (T[i] * pow(v, i));
		}
	}catch (exception& e){
		crashV1 = true;
	}
	try{
		val2 = 0;
		for(unsigned int i = 0; i<T.size(); i++){
			val2+= (T[i] * pow(v, i));
		}
	}catch(exception& e){
		crashV2 = true;
	}
	try{
		val3 = 0;
		for(unsigned int i = 0; i<T.size(); i++){
			val3+= (T[i] * pow(v, i));
		}
	}catch(exception& e){
		crashV3 = true;
	}
	if (crashV1 || crashV2 || crashV3){
		if (!crashV1) return val1;
		else if(!crashV2) return val2;
		else if(!crashV3) return val3;
		else return 0;	
	}	
	else return (val1 == val2)?val1:val3;
	
}
/**
	Calculates the mean squared error of T
*/
double meanSquaredError(){
	double error = 0;
	for(unsigned int i = 0; i<x.size(); i++){
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
	for(unsigned int i = 0; i<x.size(); i++){
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
	for(unsigned int i = 0; i<T.size(); i++){
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
	for(unsigned int i = 0; i<iterations; i++){
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
	for (unsigned int i = 0; i<T.size(); i ++){
		out<<'\t'<<'T'<<i<<" = "<<T[i];
	}
	out<<endl;
	out<<"Mean Squared Error: " << meanSquaredError()<<endl;
}


void lreg(char* input, char* output){
	ifstream inp (input);
	ofstream out (output);	
	int testCases;	
	inp >> testCases;
	
	for (unsigned int i = 0; i<testCases; i++){
		double alpha, temp;
		int iterations, N, sizeOfTraining, predictions;
		inp >> alpha >> iterations >> N >> sizeOfTraining >> predictions;
		//Auxiliar vector for redundancy		
		vector<double> readedX;
		vector<double> readedY;
		vector<double> T1;
		vector<double> T2;
		vector<double> T3;
		//READING DATA
		for (unsigned int j = 0; j<sizeOfTraining; j++){
			inp >> temp;
			readedX.push_back(temp);
		} 
		for (unsigned int j = 0; j<sizeOfTraining; j++){
			inp >> temp;
			readedY.push_back(temp);
		}
		bool crashT1 = false, crashT2 = false, crashT3 = false;
		//TRAINING
		try{
			x = readedX;
			y = readedY;
			train(iterations, alpha, N);
			T1 = T;
		}catch(exception& e){
			crashT1 = true;
		}
		try{
			x = readedX;
			y = readedY;
			train(iterations, alpha, N);
			T2 = T;
		}
		catch(exception& e){
			crashT2 = true;
		}
		try{
		x = readedX;
		y = readedY;
		train(iterations, alpha, N);
		T3 = T;
		}
		catch(exception& e){
			crashT3 = true;
		}
		if (crashT3 || crashT2 || crashT1){
			//uses anyone that avoided crash			
			if (!crashT1) T = T1;
			else if (!crashT2) T = T2;
			else if (!crashT3) T = T3;
			else T = vector<double>(N, 0);
		}	
		else{
			//if (T1 = T2) T = T1; else T = T3; 
			//triplicates comparission	
			if (equals(T1, T2) + equals(T1, T2) + equals(T1, T2) >= 2)
				T = T1;
			else 
				T = T3;
		}
		saveTs(out); // Save the training results		
		//PREDICTING
		out<<"Predictions:"<<endl;
		for (unsigned int j = 0; j < predictions; j++){
			inp >> temp;
			out << "f("<<temp<<") = "<<predict(temp)<< endl;
		}
	}
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
	
	
	lreg(argv[1], argv[2]);
	
	
	
	return 0;
}
