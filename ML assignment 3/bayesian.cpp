#include <iostream>
#include <bits/stdc++.h>

using namespace std;
char sttemp[400];
int face_count = 0,total_face = 0,total_nonface = 0;
int trainface[10000][80][80];
int traindo[10000];

int testingface[10000][80][80];
int testdo[10000];
int confusion_matrix[2][2];
double prob[4][80][80],probofface,probofnonface;

void find_probabilty(int x,int y){

	int ppfy =  0,pnfc = 0,ppfn = 0,pnfn = 0;

	for(int i = 0; i<face_count;i++){
			if(trainface[i][x][y] == 1 && traindo[i] == 1){       
				ppfy++;
			}
			if(trainface[i][x][y] == 1 && traindo[i] == 0){		 
				ppfn++;
			}
			if(trainface[i][x][y] == 0 && traindo[i] == 1){       
				pnfc++;
			}
			if(trainface[i][x][y] == 0 && traindo[i] == 0){       
				pnfn++;
			}
	}

	prob[0][x][y] = (double)ppfy/(double)(total_face+1);
	prob[0][x][y] = log(prob[0][x][y]);

	prob[1][x][y] = (double)ppfn/(double)(total_nonface+1);
	prob[1][x][y] = log(prob[1][x][y]);

	prob[2][x][y] = (double)pnfc/(double)(total_face+1);
	prob[2][x][y] = log(prob[2][x][y]);

	prob[3][x][y] = (double)pnfn/(double)(total_nonface+1);
	prob[3][x][y] = log(prob[3][x][y]);
}

int test(int face){     //TEST Function
	double lf = probofface,lnf = probofnonface;
		int temp = 0;
		for(int i = 1; i<=70;i++)
    		for(int j = 1;j<=59;j++){
    			if(testingface[face][i][j] == 1){
    				lf+=prob[0][i][j];
    				lnf+=prob[1][i][j];
    									
    			}
    			else{
    				lf+=prob[2][i][j];
    				lnf+=prob[3][i][j];
    				
    			}
 	  			if(lf>lnf)
    			temp = 1;
    			else if(lf <lnf)
    			temp = 0;  			
    	}

    	return temp;
}

int main(){


	//READING TRAINDATALABELS FILE AND STORING IN traindo ARRAY
	FILE *inputfile = fopen("facedatatrainlabels","r+");
	int ct = 0;

	while(fscanf(inputfile, "%[^\n]s",sttemp)!=EOF){
	 	int temp = int(sttemp[0]-'0');
	 	traindo[ct] = temp;
	 	if(temp)total_face++;
	 	else
	 		total_nonface++;
	 	ct++;
	 	fgetc(inputfile);
	}
	
	ct = 1,face_count = 0;
	inputfile = fopen("facedatatrain","r+");
	
	while(fscanf(inputfile, "%[^\n]s",sttemp)!=EOF){
   		if(ct%70 == 0){
   			ct = 0;
   			face_count++;
   		}
   		int len = strlen(sttemp),j = 0;
        for(int i = 0; i<len;i++){
        	if(sttemp[i] == '#')
        		trainface[face_count][ct][i] = 1;
        }
        ct++;
       fgetc(inputfile);

    }


	//probability for each pixel
    for(int i = 1; i<=70;i++)
    	for(int j = 1;j<=59;j++)
    		find_probabilty(i,j);



  	inputfile = fopen("facedatatestlabels","r+");
	ct = 0;
	//reading testing data
	while(fscanf(inputfile, "%[^\n]s",sttemp)!=EOF){
	 	int temp = int(sttemp[0]-'0');
	 	testdo[ct] = temp;
	 	
	 	ct++;
	 	fgetc(inputfile);
	}

	
	ct = 1;
	inputfile = fopen("facedatatest","r+");
	face_count = 0;

	while(fscanf(inputfile, "%[^\n]s",sttemp)!=EOF){
   		if(ct%70 == 0){
   			ct = 0;
   			face_count++;
   		}
   		int len = strlen(sttemp),j = 0;
        for(int i = 0; i<len;i++){
        	if(sttemp[i] == '#')
        		testingface[face_count][ct][i] = 1;
        }
        ct++;
       fgetc(inputfile);
    }

    //testing
    probofface = (double)total_face/(double)(total_face+total_nonface+1);
    probofnonface = (double)total_nonface/(double)(total_nonface+total_face+1);
    
  ofstream outputFile;
  outputFile.open("BayesClassifierOutput.txt");
  outputFile << setw(3) << "#" << setw(16) << "Given Class" << setw(31) << right << "Predicted Class" << endl;
  outputFile << "--------------------------------------------------" << endl;  
	int cor = 0;
  for(int k = 0; k<face_count;k++){
   	int x = test(k);


  
    outputFile << setw(3) << k+1 << setw(16) << x;
  
    
    	if ((x == 1 &&testdo[k] == 1)||(x == 0 && testdo[k] == 0) )
      {
    		cor++;
        outputFile << "  ------------  ";
      }
      else
        outputFile << "  xxxxxxxxxxxx  ";

      outputFile << testdo[k] << endl;

    	if(x == 0 && testdo[k] == 0)
    		confusion_matrix[0][0]++;
    	if(x == 1 && testdo[k] == 1)
    		confusion_matrix[1][1]++;

    	if(x == 0 && testdo[k] == 1)
    		confusion_matrix[1][0]++;
    	
    	if(x == 1 && testdo[k] == 0)
    		confusion_matrix[0][1]++;


    }


cout<<"Confusion Matrix"<<endl<<"   "<<confusion_matrix[0][0]<<"   "<<confusion_matrix[0][1]<<endl<<"   "<<confusion_matrix[1][0]<<"   "<<confusion_matrix[1][1]<<endl;

double acc = (double)cor/(double)face_count*100;
outputFile << "--------------------------------------------------" << endl;
outputFile << "Total number of instances in test data = " << face_count << endl;
outputFile << "Number of correctly predicted instances = " << cor << endl;
outputFile << "Accuracy = " << acc <<"%"<< endl;
outputFile.close();
cout<<"Accuracy is: " <<acc<<"%"<<endl;
cout<<"(Check BayesClassifierOutput.txt for more details)"<<endl;



}