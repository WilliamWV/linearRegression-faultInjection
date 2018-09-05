#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;
//This have the object of generatting random inputs to lreg

int main(int argc, char* argv[]){
	if (argc != 3){
		cout<<"Wrong number of arguments"<<endl;
		cout<<"Use as: "<<argv[0] <<" <generatedInputDestinyFile> <reportFile>"<<endl;
	}
	ofstream out (argv[1]);
	ofstream report(argv[2]);
	int testCases = 3;
	out<<testCases<<endl;	
	for (int i = 0; i<3; i++){
		//Alpha: decreases with increases of degree
		double alpha = 0.0002 / pow(i + 1, 2);
		//Iterations: increase with increase of degree		
		int iterations = 30000 * (i + 1);
		//N: the degree representations;
		int N = i + 2;
		//size of training set: increases with the degree
		int sizeOfTrainingSet = 4 * (i+2);
		//predictions : increases with the degree
		int predictions = 2 * (i+2);
		out<<alpha<<' '<<iterations<<' '<<N<<' '<<sizeOfTrainingSet<<' '<<predictions<<endl;
		
	
		//The test case input generation will occur as follows:
		//The x values are in [-2 * sizeOfTrainingSet, 2 * sizeOfTrainingSet]
		//The y values are corresponding to the application of a polynomial 
		//with degree i+1 whose coefficients are randomy generated between [-2*(i+1), 2*(i+1)]
		//The z values are in [-2 * sizeOfTrainingSet, 2 * sizeOfTrainingSet]
		srand(time(NULL));
		vector<double> x;
		vector<double> coeff;
		vector<double> y;
		vector<double> z;
		//Value generation
		for(int j = 0; j < sizeOfTrainingSet; j++){
			x.push_back(rand() % (4*sizeOfTrainingSet + 1) - 2*sizeOfTrainingSet);			
		}
		for(int j = 0; j<N; j++){
			coeff.push_back(rand()%(4*(i+1) + 1) - 2*(i+1));		
		}
		for(int j = 0; j<sizeOfTrainingSet; j++){
			double val = 0;
			for(int k = 0; k<N; k++){
				val += coeff[k] * pow(x[j], k); 
			}
			y.push_back(val);
		}
		for(int j = 0; j<predictions; j++){
			z.push_back(rand() % (4*sizeOfTrainingSet + 1) - 2*sizeOfTrainingSet);
		}
		//Value writing
		for(int j = 0; j<x.size(); j++){
			out<<x[j]<<' ';
		}
		out<<endl;
		for(int j = 0; j<y.size(); j++){
			out<<y[j]<<' ';
		}
		out<<endl;
		for(int j = 0; j<z.size(); j++){
			out<<z[j]<<' ';
		}
		out<<endl;
		
		for(int j = 0; j<coeff.size(); j++){
			report<<"C"<<j<<" = "<<coeff[j]<<'\t';	
		}
		report<<endl;
		
	}
	return 0;
}
