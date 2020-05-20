#include <stdio.h>

int funEstatica(void){
	int memoria=1;
	int particiones=0;
	printf("ingrese la memoria deseada\n");
	scanf("%d",&memoria);
	printf("ingrese las particiones\n");
	scanf("%d",&particiones);
	printf("memoria %d particiones %d\n",memoria,particiones );
	for (int i = 0; i < particiones; ++i)
	{
		printf("paricion %d: %.2f Mb\n",i, (float)memoria/particiones);
	}
	float *part;
	part = (float *)calloc(particiones,sizeof(float));
	if (part!=NULL){
		float esp;
		int espacio,temp;
		for (espacio = 0; ; ++espacio){
			if (espacio < particiones){
				temp=0;
				while(temp==0){
					printf("ingresa el espacio del proceso %d\n",espacio);
					scanf("%f",&esp);
					if (esp<=(float)memoria/particiones){
						part[espacio]= esp;	
						temp=1;
					}else{
						printf("proceso demaciado grande\n");
					}
				}
			}else{
				printf("\n-----------------------------------------------------------------\n\n");
				printf("No queda espacio para agreagar mas procesos\n");
				printf("\n-----------------------------------------------------------------\n\n");
				printf("\n-----------------------------------------------------------------\n\n");
				printf("Lista de procesos\n\n");
				for (espacio = 0;espacio < particiones ; ++espacio){
					printf("Proceso: %d\n espacio total: %f\t espacio utilizado: %f\n",espacio,(float)memoria/particiones,part[espacio]);
				}
				printf("\n-----------------------------------------------------------------\n\n");		
				free(part);
				getchar();
				getchar();
				return 1;
			}	
		}
	}
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
		if (op==7){
			break;
		}if(op==1){
			funEstatica();
		}
	}
	//funEstatica();
	return 0;
}