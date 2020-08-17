#include "csvReader.h"
#include <stdlib.h>
#include <stdio.h>

void cleanBuff(char* buff, int buffersize);

/*
* This is an auxuliary procedure, that reads a specific format of csv value.
*
* X is a regular array passed as reference, rows and columns are regular 
* integers passed as reference, separator is the character used for separate columns and
* buffersize is the length of the char array used for store each string cell.
*
* if your CSV file has big values, consider increase the buffersize.
*
* As X is a regular array and a CSV file returns an matrix, the correct form to access
* X_i,j is X[i*columns + j]
*/
void getDataFromCSV(char* path, float* X[], int* rows, int* columns,  char separator, int buffersize){
	
	FILE* file = fopen(path, "r");
	
	/*
	* The following procedure is used to count the number of rows and columns.
	*/
	
	char curr;
	
	/*
	* This variable starts with 1 because the algorithm counts the number of separators,
	* for example, the row 0,0,0,0 has three commas and four columns.
	*/
	(*columns) = 1;
	(*rows) = 1;
	
	do{
		curr = getc(file);
		
		if(curr == separator)
			++(*columns);
	}while(curr!='\n');
	
	do{
		
		curr = getc(file);
		
		if(curr == '\n')
			++(*rows);
		
	}while(curr!=EOF);
	
	fclose(file);
	
	/*
	* The following procedure is used for fill matrix X.
	*/
	
	char buff[buffersize];
	
	curr = ' ';
	
	file = fopen(path, "r");
	
	*X = (float*) malloc((*columns)*(*rows)*sizeof(float));
	int xRowIndex = 0;
	int xColumnIndex = 0;
	
	for(xRowIndex = 0; xRowIndex < (*rows); xRowIndex++){
		
		int  i;
		double value;
		
		do{
			
			i = 0;
			
			cleanBuff(buff, buffersize);
			
			curr = getc(file);
			
			while(curr != separator && curr != '\n'){
				buff[i++] = curr;
				curr = getc(file);
			}
		
			sscanf(buff, "%lf", &value);
			
			*(*X + xRowIndex*(*columns) + xColumnIndex++) = value;
			
		}while(curr != '\n');
		
		xColumnIndex = 0;
		
	}
	
}

/*
* This procedure is used to remove residues of buffer.
*/
void cleanBuff(char* buff, int buffersize){
	for(int i = 0; i < buffersize; i++){
		
		buff[i] = 0;
		
	}
}


