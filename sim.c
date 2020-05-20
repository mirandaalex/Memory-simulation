#include <stdio.h>

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
	return 0;
}


int funDinamica(void){



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