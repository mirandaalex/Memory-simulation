#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int funEstatica(void){
	int memoria=1;
	int particiones=0;
	printf("Ingrese la memoria deseada en Mb\n");
	scanf("%d",&memoria);
	printf("Ingrese las particiones deseadas\n");
	scanf("%d",&particiones);
	printf("\nMemoria %d Mb particiones %d\n",memoria,particiones );
	for (int i = 0; i < particiones; ++i)
	{
		printf("Paricion %d: %.2f Mb\n",i, (float)memoria/particiones);
	}
	float *part;
	part = (float *)calloc(particiones,sizeof(float));
	if (part!=NULL){
		float esp;
		int espacio,temp;
		printf("\n");
		for (espacio = 0; ; ++espacio){
			if (espacio < particiones){
				temp=0;
				while(temp==0){
					printf("Ingresa el espacio ocupado del proceso %d en Mb\n",espacio);
					scanf("%f",&esp);
					if (esp<=(float)memoria/particiones && esp>0){
						part[espacio]= esp;	
						temp=1;
					}else{
						printf("\nProceso demaciado grande o tiene un valor invalido\n");
					}
				}
			}else{
				printf("\n-----------------------------------------------------------------\n\n");
				printf("No queda espacio para agreagar mas procesos\n");
				printf("\n-----------------------------------------------------------------\n\n");
				printf("\n-----------------------------------------------------------------\n\n");
				printf("Lista de procesos\n\n");
				for (espacio = 0;espacio < particiones ; ++espacio){
					printf("Proceso: %d\n espacio total: %.2f\t espacio utilizado: %.2f\n",espacio,(float)memoria/particiones,part[espacio]);
				}
				printf("\n-----------------------------------------------------------------\n\n");		
				printf("Precione enter para continuar\n");
				free(part);
				getchar();
				getchar();
				return 1;
			}	
		}
	}
	printf("Error al reservar memoria\n");
	return 0;
}
void imprimeDinamica(float **memo, bool **part,int count){
	printf("         Memoria | Disponibilidad\n" );
	for (int i = 0; i <= count; ++i)
	{
		//printf("         Memoria | Disponibilidad\n" );
		printf("[ _ _ ]    %2.2f |  %s \n",memo[0][i],part[0][i]==false? "Disponible":"Ocupada");
	}
	printf("\n-----------------------------------------------------------------\n\n");		
	printf("Precione enter para continuar\n");
	getchar();
	getchar();
					
	
}

int funDinamica(void){
	int memoriatotal=1,particiones=0;
	printf("Ingrese la memoria deseada en Mb\n");
	scanf("%d",&memoriatotal);
	printf("\nMemoria %d Mb \n",memoriatotal);
	bool *part;
	float *memo;
	memo = (float *)calloc(1,sizeof(float));
	part = (bool *)calloc(1,sizeof(bool));
	if (part!=NULL && memo!=NULL){
		int op,auxi;
		float esp;
		memo[0]=(float)memoriatotal;
		part[0]=false;
		printf("\n\nMemoria total:  %.2f Mb\n",memo[0] );
		imprimeDinamica(&memo,&part,particiones);
		while(1){
			printf("\n-----------------------------------------------------------------\n\n");
			printf("\tParticion Dinamica\n");
			printf("\t1 Agreagar proceso\n");
			printf("\t2 Eliminar proceso\n");
			printf("\t3 Ver memoria\n");
			printf("\t4 Ver procesos\n");
			printf("\t5 Salir al menu\n");
			printf("\n-----------------------------------------------------------------\n\n");
			printf("ingresa la opcion\n");
			scanf("%d",&op);
			switch(op){
				case 1:
					printf("Ingresa el espacio ocupado del proceso en Mb\n");
					scanf("%f",&esp);
					int i = 0;
					float aux;
					bool temp=false;
					for (i=0; i <=particiones; ++i){
						if (memo[i]==esp && part[i]==false && temp==false){
							part[i]=true;
							temp=true;
							imprimeDinamica(&memo,&part,particiones);
		
						}else if(memo[i]>esp && part[i]==false && temp==false){				
							memo=(float *)realloc(memo,sizeof(float)*(particiones+2));
							part=(bool *)realloc(part,sizeof(bool)*(particiones+2));
							if (part!=NULL && memo!=NULL){
								aux=memo[i]-esp;
								memo[i]=esp;
								part[i]=true;
								temp=true;
								++particiones;
								memo[particiones]=aux;
								part[particiones]=false;
								imprimeDinamica(&memo,&part,particiones);
							}else{
								printf("Error al usar malloc");
								break;
							}
						}else if(memo[i]<esp && i==particiones){
							printf("No hay memoria suficiente\n");
						}
					}
					break;
				case 2:
					printf("Ingresa el id del proceso que deseas matar\n");
					scanf("%d",&auxi);
					if (auxi>=0 && auxi<=particiones ){
						part[auxi]!=false? part[auxi]=false:printf("El proceso no se encuentra ocupado\n");;
					}else printf("No existe el proceso: %d\n",auxi);
					imprimeDinamica(&memo,&part,particiones);
					break;
				case 3:
					imprimeDinamica(&memo,&part,particiones);
					break;
				case 4:
					for (int b = 0; b <=particiones; ++b){
						if(part[b]==true){printf("Proceso id: %i\t%.2f Mb\n",b,memo[b]);}
					}
					break;
				case 5:
					free(part);
					free(memo);
					return 1;
				default:
					printf("\nOpcion no valida\n");
					printf("Precione enter para continuar\n");
					getchar();
					getchar();

			}	

		}
	}
	printf("Error al reservar memoria\n");
	return 0;
}
void verProcPag( int **proc,int procesos, float **esp,int espera,float memoria){
	printf("\nProcesos en ejecucion\tmemoria restante: %.2f\n",memoria);
	for (int i = 0; i < procesos; ++i){
		if(proc[0][i]>0)printf("Proceso id: %d\t Paginas usadas: %d\n",i, proc[0][i]);
	}
	printf("\nProcesos en espera\n");
	for (int i = 0; i < espera; ++i){
		if(esp[0][i]>0)printf("Proceso id: %d\t Memoria requerida: %.2f Mb\n",i,esp[0][i]);
	}
	printf("\n-----------------------------------------------------------------\n\n");		
	printf("Precione enter para continuar\n");
	getchar();
	getchar();
}

int funPaginacion(void){
	int memoria=1;
	int pagina=0, numpag,pagUsadas=0,pagEspera=0,procesos=0;
	printf("Ingrese la memoria deseada en Mb\n");
	scanf("%d",&memoria);
	printf("Ingrese el tama%co de las paginas en kb\n",164);
	scanf("%d",&pagina);
	numpag=(memoria*1024)/pagina;
	printf("\nMemoria %d Mb paginas %d\n",memoria,numpag);
	int *part;
	float *espera;
	espera = (float *)calloc(1,sizeof(float));
	part = (int *)calloc(1,sizeof(int));
	if (part!=NULL && espera!=NULL){
		int aux, op,auxi;
		float esp, auxf;
		while(1){
			printf("\n-----------------------------------------------------------------\n\n");
			printf("\tParticion Dinamica\n");
			printf("\t1 Agreagar proceso\n");
			printf("\t2 Eliminar proceso\n");
			printf("\t3 Ver procesos\n");
			printf("\t4 Salir al menu\n");
			printf("\n-----------------------------------------------------------------\n\n");
			printf("ingresa la opcion\n");
			scanf("%d",&op);
			switch(op){
				case 1:
					printf("Ingresa el espacio ocupado del proceso en Mb\n");
					scanf("%f",&esp);
					aux=(esp*1024)/pagina;
					if((numpag-pagUsadas)>=aux){
						printf("\n**********Proceso en ejecucion********************\n");
						if(pagUsadas==0){
							part[0]=aux;
							pagUsadas+=aux;
							++procesos;
							verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
						}else{
							part=(int *)realloc(part,sizeof(int)*(procesos+1));
							if (part!=NULL){
								part[procesos]=aux;
								pagUsadas+=aux;
								++procesos;	
								verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
							}else{
								printf("Error en malloc\n");
								return 0;
							}
						}
					}else{
						if(numpag>=aux){
							printf("Se almacenara proceso en espera\n");
							if(pagEspera==0){
								espera[0]=esp;
								++pagEspera;
								verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
							}else{
								espera=(float *)realloc(espera,sizeof(float)*(pagEspera+1));
								if (espera!=NULL){
									espera[pagEspera]=esp;
									++pagEspera;
									verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
								}else {
									printf("error en malloc\n");
									return 0;
								}
							}
						}else printf("Proceso demaciado grande, no hay memoria total suficiente\n");
					}
					break;
				case 2:
					if (procesos>0){
							printf("Ingresa el id del proceso que deseas matar\n");
							scanf("%d",&auxi);
							if (auxi>=0 && auxi<procesos ){
								if(part[auxi]>0){
									pagUsadas-=part[auxi];
									part[auxi]=0;
									for (int c = 0; c < pagEspera; ++c){
										if (espera[c]>0 && (espera[c]/pagina)<=(numpag-pagUsadas)){
											printf("Proceso en espera se ejecutara\n");
											part=(int *)realloc(part,sizeof(int)*(procesos+1));
											if (part!=NULL){
												auxf=(espera[c]*1024)/pagina;
												part[procesos]=(int)auxf;
												pagUsadas+=part[procesos];
												espera[c]=0;
												++procesos;	
											}else{
												printf("Error en malloc\n");
												return 0;
											}

										}
									}
								}else{
									printf("El proceso no existe\n");
								}
							}else printf("No existe el proceso: %d\n",auxi);
							verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
						}else printf("No hay procesos\n");
					break;
				case 3:
					verProcPag(&part,procesos,&espera,pagEspera,(float)((numpag-pagUsadas)*pagina)/1024);
					break;
				case 4:
					free(part);
					free(espera);
					return 1;
				default:
					printf("\nOpcion no valida\n");
					printf("Precione enter para continuar\n");
					getchar();
					getchar();

			}	
		}
	}
	printf("Error al reservar memoria\n");
	return 0;
}

int funSegementacion(){
	float memoria=1;
	int segmentos=0,we=0;
	int segact=0;
	bool flagg=false;
	float tama,aux,res=0,temp=0,resant;
	printf("Ingrese la memoria deseada en Mb\n");
	scanf("%f",&memoria);
	printf("Ingrese los segmentos deseadas\n");
	scanf("%d",&segmentos);
	tama=(float)memoria/segmentos;
	printf("\nMemoria: %.2f Mb segmentos: %d de tamano %.2f Mb\n",memoria,segmentos ,tama);
	while(1){
		printf("\nIngresa el tamano del proceso en Mb ---- Tamano Disponible %.2f Mb\n",memoria);
		scanf("%f",&aux);
		if (aux>0 && aux<=memoria){
			printf("Proceso de %.2f Mb\nEn los segmentos: \n",aux);
			int cont=0;
			flagg=false;
			temp=aux*(-1);
			while(temp<0){
				if (cont==0 && res>0){
					temp=temp+res;
					flagg=true;
					resant=res;
				}else{
					temp=temp+tama;
				}
				++cont;
			}
			res=temp;
			if (flagg==true){
				--cont;
			}
			segact+=cont;
			for (int i = segact-cont-we; i < segact; ++i){
				printf("\t  %d \n",i);
				if (we==1 && i == (segact-cont-we)){
					printf("\t[_ _] %.2f Mb\n",resant);
				}else if(i==segact-1 && res >0){
					printf("\t[_ _] %.2f Mb\n",tama-res);
				}else{
					printf("\t[_ _] %.2f Mb\n",tama);
				}
			}
			if(res>0){ 
				we=1;
			}else we=0;
			memoria-=aux;
		}else {
			printf("Error en el tamano del proceso, memoria insuficiente\n");
			return 1;
		}if (memoria==0){
			printf("\n*******************************Run out of memory*****************************\n");
			printf("Press enter to continue\n");
			getchar();
			getchar();
			return 0;
		}
	printf("\n");
	}

}



int funSegementacionPag(){
	float memoria=1;
	int segmentos=0,we=0;
	int segact=0;
	int paginas,paginasSeg=0;
	bool flagg=false;
	float tama,aux,res=0,temp=0,resant,aux3;
	printf("Ingrese la memoria deseada en Mb\n");
	scanf("%f",&memoria);
	printf("Ingrese los segmentos deseadas\n");
	scanf("%d",&segmentos);
	printf("Ingrese el tamano de las paginas en kb\n");
	scanf("%d",&paginas);
	tama=(float)memoria/segmentos;
	aux=tama*1024;
	while (aux>0){
		aux=aux-paginas;
		paginasSeg++;	
	}
	if (aux<0){
		paginasSeg--;
	}
	printf("\nMemoria: %.2f Mb segmentos: %d de tamano %.2f Mb \nCon %d paginas de tamano: %d kb\n",memoria,segmentos ,tama,paginasSeg*segmentos,paginas);
	while(1){
		printf("\nIngresa el tamano del proceso en Mb ---- Tamano Disponible %.2f Mb\n",memoria);
		scanf("%f",&aux);
		if (aux>0 && aux<=memoria){
			printf("Proceso de %.2f Mb\nEn los segmentos: \n",aux);
			int cont=0;
			flagg=false;
			temp=aux*(-1);
			while(temp<0){
				if (cont==0 && res>0){
					temp=temp+res;
					flagg=true;
					resant=res;
				}else{
					temp=temp+tama;
				}
				++cont;
			}
			res=temp;
			if (flagg==true){
				--cont;
			}
			segact+=cont;
			for (int i = segact-cont-we; i < segact; ++i){
				printf("\t  %d \n",i);
				if (we==1 && i == (segact-cont-we)){
					
					printf("\t[_ _] %.2f Mb, %d paginas\n",resant,(int)(resant*1024)/paginas);
				}else if(i==segact-1 && res >0){
					printf("\t[_ _] %.2f Mb, %d paginas\n",tama-res,(int)((tama-res)*1024)/paginas);
				}else{
					printf("\t[_ _] %.2f Mb, %d paginas\n",tama,paginasSeg);
				}
			}
			if(res>0){ 
				we=1;
			}else we=0;
			memoria-=aux;
		}else {
			printf("Error en el tamano del proceso, memoria insuficiente\n");
			return 1;
		}if (memoria==0){
			printf("\n*******************************Run out of memory*****************************\n");
			printf("Press enter to continue\n");
			getchar();
			getchar();
			return 0;
		}
	printf("\n");
	}

}



int main(int argc, char const *argv[])
{
	int op;
	while (1){
		printf("\n-----------------------------------------------------------------\n\n");
		printf("\tTipos de administracion de memoria\n");
		printf("\t1 Particion Estatica\n");
		printf("\t2 Particion Dinamica\n");
		printf("\t3 Paginacion\n");
		printf("\t4 Segmentacion\n");
		printf("\t5 Segmentacion paginada\n");
		printf("\t6 Salir\n");
		printf("\n-----------------------------------------------------------------\n\n");
		
		printf("ingresa la opcion\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				funEstatica();
				break;
			case 2:
				funDinamica();
				break;
			case 3:
				funPaginacion();
				break;
			case 4:
				funSegementacion();
				break;
			case 5:
				funSegementacionPag();
				break;
			case 6:
				return 0;
			default:
				printf("\nOpcion no valida\n");
				printf("Precione enter para continuar\n");
				getchar();
				getchar();

		}
	}
	return 0;
}