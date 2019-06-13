#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//--- Structs ---//

typedef struct Pixel{	
	int R,G,B,status;
}Pixel;

typedef struct Blob{	
	int x,y,area;
	struct Blob* nseg;
	struct Blob* nant;
}Blob;

// --- Funções de Criação e Inserção --- //

Blob *makeBlob(int x,int y,int area){
	Blob *B = (Blob *) malloc(sizeof(Blob));
	B->x = x;
	B->y = y;
	B->area = area;
	B->nant = NULL;
	B->nseg = NULL;
	return B;
}


Blob *insertFirst(Blob *B,Blob *nv){
	if(B==NULL){
		return nv;
	}
	nv->nseg = B;
	B->nant = nv;
	return nv;	
}

Blob *insertLast(Blob *B,Blob *nv){
	Blob *aux = B;
	if(B==NULL){
		return nv;
	}
	while(aux->nseg!=NULL){
		aux=aux->nseg;
	}
	aux->nseg = nv;
	nv->nant = aux;
	return B;
}

Blob *insertOrder(Blob *B,Blob *nv){
	Blob *aux = B;
	if(B==NULL){
		return nv;
	}
	while(aux!=NULL){
		if(nv->area > aux->area ){
			if(aux->nant == NULL){
				B = insertFirst(B,nv);
				return B;
			}
			nv->nseg = aux;
			nv->nant = aux->nant;
			aux->nant->nseg = nv;
			aux->nant = nv;
			return B;
		}
		aux=aux->nseg;
	}
	B = insertLast(B,nv);
	return B;
}

Pixel* makePixel(int R,int G,int B){
	Pixel *new = (Pixel *) malloc(sizeof(Pixel));
	new->R = R;
	new->G = G;
	new->B = B;
	new->status = 0;
	return new;
}

Pixel** makeArray(int lines,int columns){
	Pixel **array = (Pixel **) malloc(lines*sizeof(Pixel *));
	int i;
	for(i=0;i<lines;i++){
		array[i] = (Pixel *) malloc(columns *sizeof(Pixel));
	}	
	return array;
}



// --- Funções de Ordenação ---//

void bubbleSort (int *V, int N) {
	int	k, kk, fim = N-1;
	int  aux;
	do{
		kk = 0;
		for (k = 0; k < fim; k++)
			if (V[k] > V[k+1]){
				aux = V[k];
				V[k] = V[k+1];
				V[k+1] = aux;
				kk = k;
			}
		fim = kk;
	}while (kk != 0);
}

// --- Funções de pesquisa  --- //

int find_x_center(Pixel **P,int lines,int columns,int c){
	int i,j,m=0,*V = NULL;
	for(i=0;i<lines;i++){
		for(j=0;j<columns;j++){
			if(P[i][j].status == c){
				V = (int *) realloc(V,(m+1)*sizeof(int));
				V[m] = i;
				m++;
			}
		}
	}
	bubbleSort(V,m);
	if(m%2 == 0){
		return (V[(m/2)-1]);
	}
	return (V[m/2]);
}

int find_y_center(Pixel **P,int lines,int columns,int c){
	int i,j,m=0,*V = NULL;
	for(i=0;i<lines;i++){
		for(j=0;j<columns;j++){
			if(P[i][j].status == c){
				V = (int *) realloc(V,(m+1)*sizeof(int));
				V[m] = j;
				m++;
			}
		}
	}	
	bubbleSort(V,m);
	if(m%2 == 0){
		return (V[(m/2)-1]);
	}
	return (V[m/2]);
}

Pixel** find_4_neighborhood(Pixel **P,int x,int y,int lines,int columns,int R,int G,int B,int D,int c){
			if((x+1)<lines&&((P[x+1][y].R >= R-D && P[x+1][y].R <= R+D) && (P[x+1][y].G >= G-D && P[x+1][y].G <= G+D) && (P[x+1][y].B >= B-D && P[x+1][y].B <= B+D) && (P[x+1][y].status == 0))){
				P[x+1][y].status = c;
				P = find_4_neighborhood(P,x+1,y,lines,columns,R,G,B,D,c);
			}
			if((x-1)>0 && ((P[x-1][y].R >= R-D && P[x-1][y].R <= R+D) && (P[x-1][y].G >= G-D && P[x-1][y].G <= G+D) && (P[x-1][y].B >= B-D && P[x-1][y].B <= B+D) && (P[x-1][y].status == 0))){
				P[x-1][y].status = c;
				P = find_4_neighborhood(P,x-1,y,lines,columns,R,G,B,D,c);
			}
			if((y-1)>0&&((P[x][y-1].R >= R-D && P[x][y-1].R <= R+D) && (P[x][y-1].G >= G-D && P[x][y-1].G <= G+D) && (P[x][y-1].B >= B-D && P[x][y-1].B <= B+D) && (P[x][y-1].status == 0))){
				P[x][y-1].status = c;
				P = find_4_neighborhood(P,x,y-1,lines,columns,R,G,B,D,c);
			}
			if((y+1)<columns && ((P[x][y+1].R >= R-D && P[x][y+1].R <= R+D) && (P[x][y+1].G >= G-D && P[x][y+1].G <= G+D) && (P[x][y+1].B >= B-D && P[x][y+1].B <= B+D) && (P[x][y+1].status == 0))){
				P[x][y+1].status = c;
				P = find_4_neighborhood(P,x,y+1,lines,columns,R,G,B,D,c);
			}
			return P;	
}

// --- // 

int areaCalculator(Pixel **P,int lines,int columns,int c){
	int i,j,count = 0;
	for(i=0;i<lines;i++){
		for(j=0;j<columns;j++){
			if(P[i][j].status == c){
				count++;
			}
		}
	}
	return count;
}

int findPixel(Pixel **P,int lines,int columns,int R,int G,int B,int D,char *name){
	int i,j,x,y,count=0,c=1,iteracao=0;
	Blob *b = NULL;
	for(i=0;i<lines;i++){
		for(j=0;j<columns;j++){
			if((P[i][j].R >= R-D && P[i][j].R <= R+D) && (P[i][j].G >= G-D && P[i][j].G <= G+D) && (P[i][j].B >= B-D && P[i][j].B <= B+D) && (P[i][j].status == 0)){
				P[i][j].status = c;
				P = find_4_neighborhood(P,i,j,lines,columns,R,G,B,D,c);
				count = areaCalculator(P,lines,columns,c);
				x = find_x_center(P,lines,columns,c);
				y = find_y_center(P,lines,columns,c);
				Blob *Pixel_Blob = makeBlob(x,y,count);
				b = insertOrder(b,Pixel_Blob);		
				c++;
			}
		}
	}		
	while(b!=NULL){
		if(b->area == 1){
			printf("%s; (%d,%d):  %d pixel \n",name,b->x,b->y,b->area);
			iteracao++;
		}	
		else{
			printf("%s; (%d,%d):  %d pixeis \n",name,b->x,b->y,b->area);
			iteracao++;
		}	
		b=b->nseg;
	}
	if(iteracao==0){
		return 0;
	}
	return 1;
}

// --- //


void findBlobs(char *file_name,int R,int G,int B,int D){
	FILE *file=fopen(file_name,"r");
	int i,c=0,j,lines,columns,channels,found=2,verify=0,aux=0;
	char name[200];
	if(file == NULL){
		printf("FILE EMPTY!\n");
		return;
	}
	while(!feof(file)){
		fgets(name,200,file);
		fscanf(file,"%d %d %d\n",&lines,&columns,&channels);
		Pixel **P  = makeArray(lines,columns);
		for(i=0;i<lines;i++){
			for(j=0;j<columns;j++){
				int R,G,B;
				fscanf(file,"%d\n%d\n%d\n",&R,&G,&B);
				Pixel *p = makePixel(R,G,B);
				P[i][j] = *p;
				free(p);
			}
		}
		name[strcspn(name,"\n")] = 0;
		found=findPixel(P,lines,columns,R,G,B,D,name);
		if(found==0){
			verify++;
		}
		else{
			printf("\n");
		}
		aux++;		
	}
	
	if(verify==aux){
		printf("\nNao foram encontrados pixeis com o valor (%d,%d,%d) e tolerancia %d\n",R,G,B,D);
	}
}

// --- //

void menu(){
	printf("\n1 - Procurar por Blobs");
	printf("\n2 - Consultar dados da Imagem");
	printf("\n0 - Sair\n");
}

int main(){
	int i,j,R,G,B,D,gateway=1,opcao,subopcao,lines,columns,channels,control;
	char name[200];
	FILE *file;
	do{
		printf("\nEscolha uma opcao:\n");
		menu();
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				do{
					control=1;
					printf("Inserir valores (R,G,B) e tolerancia: \n");
					scanf("%d%d%d%d",&R,&G,&B,&D);
					if((R<0 || R>255) || (G<0 || G>255) || (B<0 || B>255) || (D<0 || D>255)){
						printf("Valores inválidos\n");
						control=0;
					}
				}while(control==0);
				findBlobs("imgs.txt",R,G,B,D);
				printf("\n --------------------------------- \n");
				break;
			case 2:
				file=fopen("imgs.txt","r");
				while(!feof(file)){
					fgets(name,200,file);
					fscanf(file,"%d %d %d\n",&lines,&columns,&channels);
					for(i=0;i<lines;i++){
						for(j=0;j<columns;j++){
							int R,G,B;
							fscanf(file,"%d\n%d\n%d\n",&R,&G,&B);
						}
					}
					name[strcspn(name,"\n")] = 0;
					printf("\n%s: Linhas= %d, Colunas= %d, Canais= %d\n",name,lines,columns,channels);
				}
				rewind(file);
				printf("\n --------------------------------- \n");
				break;
			case 0:
				printf("Programa terminado\n");
				gateway=0;
				break;
			default:
				printf("Opcao Invalida\n");
				break;
		}
	}while(gateway!=0);
}