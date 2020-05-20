#include <stdio.h>
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
			printf("\t4 Salir al menu\n");
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
					printf("Ingresa el proceso que deseas matar\n");
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
		printf("\t5 Paginacion segmentada\n");
		printf("\t6 Segmentacion paginada\n");
		printf("\t7 Salir\n");
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
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
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