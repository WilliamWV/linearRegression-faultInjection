
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
using namespace std;

typedef unsigned int UINT;

vector<double> x; // input of training set
vector<double> y; // observed values of training set inputs
vector<double> T1; // the adjustment variables
vector<double> T2;

double xChecksum = 0;
double yChecksum = 0;

/**
	Alterações na duplicação seletiva
		* Duplica variáveis de laço,pois a maioria dos laços é usado para calcular
		  os parâmetros de ajuste T e um erro em um parâmetro afeta todas as predições
		  e porque essa duplicação é simples e gera pouco overhead
		* Protege variáveis importantes para o cálculo dos parâmetros como:
			- pos : indica qual dos parâmetros está sendo atualizado
			- alpha : indica a taca de aprendizado do algoritmo
			- iterations : indica quantidade de iterações no cálculo dos parâmetros
		* Ideias:
			- Proteger x e y com checksums e verificar no final da execução
			- Ver se encontra invariantes simples mas próximos do ideal nos laços com cálculos
			- Verificar se uma duplicação de T vale a pena
	
*/

int detected = 0;


UINT verifyUintDup(UINT a, UINT b){
	if (a != b && detected != 1){
		//gerar entrada no log
		ofstream fp ("/tmp/lreg/detected.log", std::ofstream::app);
		fp << "verifyUint: a = "<<a<<"; b = "<<b<<endl;
        detected = 1;	
	}
	return a;
}
double verifyDoubleDup(double a, double b){
	if (a != b && detected != 1){
		//gerar entrada no log
		ofstream fp ("/tmp/lreg/detected.log", std::ofstream::app);
		fp << "verifyDouble: a = "<<a<<"; b = "<<b<<endl;
        detected = 1;	
	}	
	return a;
}


void verifyChecksum(vector<double> vec, double check){
	if(detected!=1){
		double temp = 0;		
		for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<vec.size(); i1++, i2++){
			temp+= vec[verifyUintDup(i1, i2)];
		}
		if(temp!=check){
			//gerar entrada no log
			ofstream fp ("/tmp/lreg/detected.log", std::ofstream::app);
			fp << "checksum failed"<<endl;
		    detected = 1;
		}
	}
}

bool equals(vector<double> a, vector<double> b){
	if (a.size() != b.size()) return false;
	for (UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<a.size(); i1++, i2++){
		if(a[verifyUintDup(i1, i2)] != b[verifyUintDup(i1, i2)]) 
			return false;
	}

	return true;
}

/**
	Predicts the value related to v using the Ts variables
*/
double predict(double v){
	double val = 0;
	
	for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<T1.size(); i1++, i2++){
		val+= (verifyDoubleDup(T1[verifyUintDup(i1, i2)], T2[verifyUintDup(i1, i2)]) * pow(v, verifyUintDup(i1, i2)));
	}
	return val;
	
}
/**
	Calculates the mean squared error of T
*/
double meanSquaredError(){
	double error = 0;
	
	for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<x.size(); i1++, i2++){
		error+= ((predict(x[verifyUintDup(i1, i2)]) - y[verifyUintDup(i1, i2)]) * (predict(x[verifyUintDup(i1, i2)]) - y[verifyUintDup(i1, i2)]));	
	}
	error /= x.size();
	return error;

}
/**
	Calculates the partial derivate of the meanSquaredError function 
	to the adjustment variable whose position in T is passed in pos
*/
double partialDerivate(UINT pos1, UINT pos2){
	double pD = 0;
	
	for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<x.size(); i1++, i2++){
		pD += ((predict(x[verifyUintDup(i1, i2)]) - y[verifyUintDup(i1, i2)])*pow(x[verifyUintDup(i1, i2)], verifyUintDup(pos1, pos2)));	
	}
	pD *= (2.0/x.size());
	return pD;
}

/**
	Adjusts the values of T 
*/
void adjust(double alpha1, double alpha2){
	
	double PD;
	
	for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<T1.size(); i1++, i2++){
		PD = partialDerivate(verifyUintDup(i1, i2), verifyUintDup(i1, i2));
		// alpha is different from the canonical version because this works better
		double diff = ((verifyDoubleDup(alpha1, alpha2) / (sqrt( fabs(PD) ))) * PD);
		T1[verifyUintDup(i1, i2)]= T1[verifyUintDup(i1, i2)] - diff;
		T2[verifyUintDup(i1, i2)]= T2[verifyUintDup(i1, i2)] - diff;
		 
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
void train(UINT iter1, UINT iter2, UINT N, double alpha1, double alpha2, bool stopsWhenStable = true){
	/**
		This will suppose the initial values of T as zeros
		1) Compute the meanSquaredError of current predictions
		2) Update the values of T using gradient descendent
		3) Repeat until reach the maximum number of iterations, or
		   if stopsWhenStable = true also when T stops changing 
	*/
	T1 = vector<double>(N, 0);
	T2 = vector<double>(N, 0);
	vector<double> prevT = T1; 
	vector<double> bestT = T1; 
	double bestMSE = meanSquaredError();
	double MSE;	
	for(UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<verifyUintDup(iter1, iter2); i1++, i2++){
		prevT = T1; 	
		adjust(verifyDoubleDup(alpha1, alpha2), verifyDoubleDup(alpha1, alpha2));
		MSE = meanSquaredError();
		if (MSE < bestMSE){
			bestMSE = MSE;
			bestT = T1; 
		}
		if (equals(T1, prevT) && stopsWhenStable){ // implement equals
			break;		
		}
	}
	//T1 = bestT;
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
	
	for (UINT i1 = 0, i2 = 0; verifyUintDup(i1, i2)<testCases; i1++, i2++){
		double alpha, temp;
		UINT iterations, N, sizeOfTraining, predictions;
		inp >> alpha >> iterations >> N >> sizeOfTraining >> predictions;
		UINT pred2 = predictions;
		//READING DATA
		for (UINT j1 = 0, j2 = 0; verifyUintDup(j1, j2)<sizeOfTraining; j1++, j2++){
			inp >> temp;
			x.push_back(temp);
			xChecksum+=temp;
		} 
		for (UINT j1 = 0, j2 = 0; verifyUintDup(j1, j2)<sizeOfTraining; j1++, j2++){
			inp >> temp;
			y.push_back(temp);
			yChecksum+=temp;
		} 
		//TRAINING
		train(iterations, iterations, N, alpha, alpha);
		for (UINT j1 = 0, j2 = 0; verifyUintDup(j1, j2) < verifyUintDup(predictions, pred2); j1++, j2++){
			inp >> temp;
			out<<predict(temp)<< endl;
		}
		verifyChecksum(x, xChecksum);
		verifyChecksum(y, yChecksum);
			
	}
	
	return 0;
}
