#include <stdlib.h>
#include <stdio.h>
int euclid(int m, int n){
	if(n>m){
		n = n + m; 
		m = n - m; 
		n = n - m; 
	}
	int remainder;
	remainder=m%n;
	if(remainder!=0){
		return(euclid(n,remainder));	
		}else{
			return(n);
		}
}

int main(){
	char retStr[12]; 
	//int result=euclid(119,544);
	int result=euclid(544,119);
	sprintf(retStr, "%d", result);
	printf("Result: %s\n", retStr);
	return 0;
}
