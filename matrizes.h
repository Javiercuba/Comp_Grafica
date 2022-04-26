float gMatriz[3][3];  // matriz de transformacao


void operaTransforma(float v[]) {
	float temp[3];
	int i, j;
	  // temp = Matriz x vetor
	for(i=0; i<3; i++) {
		temp[i] = 0.0f;
		for(j=0; j<3; j++)
			temp[i] = temp[i] + gMatriz[i][j] * v[j];
	}
	  // copia vetor resultando no vetor original
	for(i=0; i<3; i++)
		v[i] = temp[i];
}



void matrizIdentidade(){
	int i,j;
	//Criando matrizIdentidade;
	for( i=0; i<3;i++){
		for(j =0;j<3;j++){
			if(i==j){
				gMatriz[i][j] = 1.0f;
			}else{
				gMatriz[i][j] = 0.0f;
			}
		}
	}
}




