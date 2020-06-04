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
	bool *bolt;
	bolt = (bool *)calloc(particiones,sizeof(bool));
	if (part!=NULL && bolt!=NULL){
		float esp;
		int espacio=0,temp,op;
		for (temp = 0; temp < particiones; ++temp)
			bolt[temp]=false;
		
		while (1){
			printf("\n-----------------------------------------------------------------\n\n");
			printf("\t0 Agreagar proceso\n");
			printf("\t1 Ver Procesos\n");
			printf("\t2 Ver Memoria\n");
			printf("\t3 Eliminar Proceso\n");
			printf("\t4 Salir\n");
			printf("\n-----------------------------------------------------------------\n\n");
			
			printf("ingresa la opcion\n");
			scanf("%d",&op);
			switch(op){
				case 0:
					if (espacio < particiones){
						temp=0;
						while(temp==0){
							printf("Ingresa el espacio ocupado del proceso en Mb\n");
							scanf("%f",&esp);
							if (esp<=(float)memoria/particiones && esp>0){
								for (int e = 0; e < particiones; ++e)
									if (bolt[e]==false){
										part[espacio]= esp;	
										temp=1;
										++espacio;
										bolt[e]=true;
										break;
									}
							}else{
								printf("\nProceso demaciado grande o tiene un valor invalido\n");
							}
						}
					}else{
						printf("\n\n\n\n\n\n\n\n\n-----------------------------------------------------------------\n\n");
						printf("\tNo queda espacio para agreagar mas procesos\n");
						printf("\n-----------------------------------------------------------------\n\n");
					}
					break;
				case 1:
					printf("\nLista de procesos\n\n");
					for (int e = 0;e < particiones ; ++e){
						if(bolt[e]==true)
							printf("Proceso id: %d\n Espacio de paricion %d: %.2f\t espacio utilizado: %.2f\n",e,e,(float)memoria/particiones,part[e]);
					}
					break;
				case 2:
					printf("\nMemoria\n\n");
					for (int e = 0;e < particiones ; ++e){
						if (bolt[e]==true)
							printf("Espacio: %d\n espacio total: %.2f\t Estado:  Ocupado\n",e,(float)memoria/particiones);
						if (bolt[e]==false)
							printf("Espacio: %d\n espacio total: %.2f\t Estado:  Disponible\n",e,(float)memoria/particiones);
					}
					break;
				case 3:
					if (espacio==0) {
						printf("No hay procesos registrados\n");
						break;
					}
					int e;
					printf("Ingresa el id del Proceso\n");
					scanf("%d",&e);
					if(e>=0 && e< particiones){
						if(bolt[e]==true){
							bolt[e]=false;
							part[e]=0;
							--espacio;
							printf("Proceso eliminado\n");
						}else printf("Proceso no encontrado\n");
					}else printf("Id invalido\n");
					break;
				case 4:
					free(part);
					free(bolt);
					return 0;
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
void verSeg(int ***pro,int pp,int part,int swap){
	int i=0;
	for(i=0;i<pp;i++){
		printf("Tarea %d\tTamano %d Mb y %d slots de memoria\n",i,      pro[i][0][0],pro[i][0][1]);
		printf("\tCodigo\t\tporcentaje:%d\tSlots %d\tAlmacenado en:",  pro[i][1][0],pro[i][1][1] );
		if (pro[i][1][2]==1){
			printf(" Memoria \n");
		}else printf(" Meoria virtual\n");
		printf("\tDatos\t\tporcentaje:%d\tSlots %d\tAlmacenado en:",   pro[i][2][0],pro[i][2][1] );
		if (pro[i][2][2]==1){
			printf(" Memoria \n");
		}else printf(" Meoria virtual\n");
		printf("\tBiblioteca\tporcentaje:%d\tSlots %d\tAlmacenado en:",pro[i][3][0],pro[i][3][1] );
		if (pro[i][3][2]==1){
			printf(" Memoria \n");
		}else printf(" Meoria virtual\n");
	}
	printf("  Memoria restante: %d\t Memoria virtual restante: %d\n",part,swap );
}
int ***addSeg(int ***pro,int *pp,int *memo,int *swap,int dis,int total){
	int size,porcen[3];
	int i = 0,temp=0,acu=0,aux,bc;
	printf("Ingresa el tamaño en Mb de la tarea\n");
	scanf("%d",&size);
	acu= size;
	if(size>0 && size<total){
		while(1){
			printf("Ingresa el porcentaje de Codigo\n");
			scanf("%d",&porcen[0]);
			printf("Ingresa el porcentaje de Datos\n");
			scanf("%d",&porcen[1]);
			printf("Ingresa el porcentaje de Bibliotecas\n");
			scanf("%d",&porcen[2]);
			if((porcen[0]+porcen[1]+porcen[2])==100){
				break;
			}else printf("Porcentajes invalidos\n");
		}
		size=size/dis;
		aux=size;
		temp=(aux*porcen[0])%(100)==0?0:1;
		bc=(aux*porcen[0])/(100)+temp;
		printf("%d\n",bc );
		temp=(aux*porcen[1])%(100)==0?0:1;
		bc+=(aux*porcen[1])/(100)+temp;
		printf("%d\n",bc );
		temp=(aux*porcen[2])%(100)==0?0:1;
		bc+=(aux*porcen[2])/(100)+temp;
		printf("%d\n",bc );
		size=bc;
		if (size<=memo[0] && *pp==0){
			pro[0][0][0]=acu;
			pro[0][1][0]=porcen[0];
			pro[0][2][0]=porcen[1];
			pro[0][3][0]=porcen[2];
			pro[0][0][1]=size;
			temp=(aux*porcen[0])%(100)==0?0:1;
			pro[0][1][1]=(aux*porcen[0])/(100)+temp;
			temp=(aux*porcen[1])%(100)==0?0:1;
			pro[0][2][1]=(aux*porcen[1])/(100)+temp;
			temp=(aux*porcen[2])%(100)==0?0:1;
			pro[0][3][1]=(aux*porcen[2])/(100)+temp;
			pro[0][1][2]=1;
			pro[0][2][2]=1;
			pro[0][3][2]=1;
			//temp=size-(pro[0][1][1]+pro[0][2][1]+pro[0][3][1]);
			//pro[0][1][1]+=temp;
			memo[0]=memo[0]-size;
			printf("Se agrego la tarea a la memoria principal\n"); 
			pp[0]+=1;
			return pro;
		}
		printf("paso, size %d, memo %d, swap %d, pp %d\n",size,*memo,*swap,*pp);
		if(size<=memo[0] && pp[0]!=0){
			pro = realloc(pro,(pp[0]+1)*sizeof(int **));
			pro[pp[0]] =(int **)calloc(4,sizeof(int*));
			for (i = 0; i < 4; ++i)
				pro[pp[0]][i]=(int*)calloc(3,sizeof(int));
			pro[pp[0]][0][0]=acu;
			pro[pp[0]][1][0]=porcen[0];
			pro[pp[0]][2][0]=porcen[1];
			pro[pp[0]][3][0]=porcen[2];
			pro[pp[0]][0][1]=size;
			temp=(aux*porcen[0])%(100)==0?0:1;
			pro[pp[0]][1][1]=(aux*porcen[0])/(100)+temp;
			temp=(aux*porcen[1])%(100)==0?0:1;
			pro[pp[0]][2][1]=(aux*porcen[1])/(100)+temp;
			temp=(aux*porcen[2])%(100)==0?0:1;
			pro[pp[0]][3][1]=(aux*porcen[2])/(100)+temp;
			pro[pp[0]][1][2]=1;
			pro[pp[0]][2][2]=1;
			pro[pp[0]][3][2]=1;
			//temp=size-(pro[0][1][1]+pro[0][2][1]+pro[0][3][1]);
			//pro[pp[0]][1][1]+=temp;
			memo[0]=memo[0]-size;
			printf("Se agrego la tarea a la memoria principal\n"); 
			pp[0]+=1;
			return pro;
		}else if(size<=swap[0] && pp[0]!=0){
			pro = realloc(pro,(pp[0]+1)*sizeof(int **));
			pro[pp[0]] =(int **)calloc(4,sizeof(int*));
			for (i = 0; i < 4; ++i)
				pro[pp[0]][i]=(int*)calloc(3,sizeof(int));
			pro[pp[0]][0][0]=acu;
			pro[pp[0]][1][0]=porcen[0];
			pro[pp[0]][2][0]=porcen[1];
			pro[pp[0]][3][0]=porcen[2];
			pro[pp[0]][0][1]=size;
			temp=(aux*porcen[0])%(100)==0?0:1;
			pro[pp[0]][1][1]=(aux*porcen[0])/(100)+temp;
			temp=(aux*porcen[1])%(100)==0?0:1;
			pro[pp[0]][2][1]=(aux*porcen[1])/(100)+temp;
			temp=(aux*porcen[2])%(100)==0?0:1;
			pro[pp[0]][3][1]=(aux*porcen[2])/(100)+temp;
			pro[pp[0]][1][2]=0;
			pro[pp[0]][2][2]=0;
			pro[pp[0]][3][2]=0;
			//temp=size-(pro[0][1][1]+pro[0][2][1]+pro[0][3][1]);
			//pro[pp[0]][1][1]+=temp;
			swap[0]=swap[0]-size;
			printf("Se agrego la tarea a la memoria virtual\n"); 
			pp[0]+=1;
			return pro;
		}else if(size<=(swap[0]+memo[0]) && pp[0]!=0){
			pro = realloc(pro,(pp[0]+1)*sizeof(int **));
			pro[pp[0]] =(int **)calloc(4,sizeof(int*));
			for (i = 0; i < 4; ++i)
				pro[pp[0]][i]=(int*)calloc(3,sizeof(int));
			pro[pp[0]][0][0]=acu;
			pro[pp[0]][1][0]=porcen[0];
			pro[pp[0]][2][0]=porcen[1];
			pro[pp[0]][3][0]=porcen[2];
			pro[pp[0]][0][1]=size;
			temp=(aux*porcen[0])%(100)==0?0:1;
			pro[pp[0]][1][1]=(aux*porcen[0])/(100)+temp;
			temp=(aux*porcen[1])%(100)==0?0:1;
			pro[pp[0]][2][1]=(aux*porcen[1])/(100)+temp;
			temp=(aux*porcen[2])%(100)==0?0:1;
			pro[pp[0]][3][1]=(aux*porcen[2])/(100)+temp;
			//temp=size-(pro[0][1][1]+pro[0][2][1]+pro[0][3][1]);
			if((pro[pp[0]][1][1]+pro[pp[0]][2][1])<=swap[0] && pro[pp[0]][3][1]<=memo[0]){//1 entran dos a swap
					pro[pp[0]][1][2]=0;
					pro[pp[0]][2][2]=0;
					pro[pp[0]][3][2]=1;
					swap[0]-=(pro[pp[0]][1][1]+pro[pp[0]][2][1]);
					memo[0]-=pro[pp[0]][3][1];
					pp[0]+=1;
			}else if((pro[pp[0]][1][1]+pro[pp[0]][3][1])<=swap[0] && pro[pp[0]][2][1]<=memo[0]){//2 entran dos a swap
					pro[pp[0]][1][2]=0;
					pro[pp[0]][2][2]=1;
					pro[pp[0]][3][2]=0;
					swap[0]-=(pro[pp[0]][1][1]+pro[pp[0]][3][1]);
					memo[0]-=pro[pp[0]][2][1];
					pp[0]+=1;
			}else if((pro[pp[0]][3][1]+pro[pp[0]][2][1])<=swap[0] && pro[pp[0]][1][1]<=memo[0]){//3 entran dos a swap
					pro[pp[0]][1][2]=1;
					pro[pp[0]][2][2]=0;
					pro[pp[0]][3][2]=0;
					swap[0]-=(pro[pp[0]][3][1]+pro[pp[0]][2][1]);
					memo[0]-=pro[pp[0]][1][1];
					pp[0]+=1;
			}else if((pro[pp[0]][1][1]+pro[pp[0]][2][1])<=memo[0] && pro[pp[0]][3][1]<=swap[0]){//4 entran dos a memoria
					pro[pp[0]][1][2]=1;
					pro[pp[0]][2][2]=1;
					pro[pp[0]][3][2]=0;
					memo[0]-=(pro[pp[0]][1][1]+pro[pp[0]][2][1]);
					swap[0]-= pro[pp[0]][3][1];
					pp[0]+=1;
			}else if((pro[pp[0]][1][1]+pro[pp[0]][3][1])<=memo[0] && pro[pp[0]][2][1]<=swap[0]){//5 entran dos a memoria
					pro[pp[0]][1][2]=1;
					pro[pp[0]][2][2]=0;
					pro[pp[0]][3][2]=1;
					memo[0]-=(pro[pp[0]][1][1]+pro[pp[0]][3][1]);
					swap[0]-= pro[pp[0]][2][1];
					pp[0]+=1;
			}else if((pro[pp[0]][3][1]+pro[pp[0]][2][1])<=memo[0] && pro[pp[0]][1][1]<=swap[0]){//6 entran dos a memoria
					pro[pp[0]][1][2]=0;
					pro[pp[0]][2][2]=1;
					pro[pp[0]][3][2]=1;
					memo[0]-=(pro[pp[0]][3][1]+pro[pp[0]][2][1]);
					swap[0]-= pro[pp[0]][1][1];
					pp[0]+=1;
			}else printf("Algo salio mal\n");
			return pro;
		}
		printf("me salgo we\n");
	}else printf("Tamano de tarea invalido\n");
	printf("me sali we\n");
	return pro;
}
void segPlano(int ***pro,int *pp,int *memo,int *swap){
	int aux,fl=0;
	printf("Ingresa la tarea que deseas enviar a segundo plano\n");
	scanf("%d",&aux);
	if (aux>=0 && aux<pp[0]){
		if (pro[aux][1][2]==1 && pro[aux][1][1]<=swap[0]){
			pro[aux][1][2]=0;
			swap[0]=swap[0]-pro[aux][1][1];
			memo[0]=memo[0]+pro[aux][1][1];
			fl++;
			printf("Se movio la seccion de codigo a memoria virtual\n");
		}
		if(pro[aux][2][2]==1 && pro[aux][2][1]<=swap[0]){
			pro[aux][2][2]=0;
			swap[0]=swap[0]-pro[aux][2][1];
			memo[0]=memo[0]+pro[aux][2][1];
			fl++;
			printf("Se movio la seccion de datos a memoria virtual\n");
		}
		if(pro[aux][3][2]==1 && pro[aux][3][1]<=swap[0]){
			pro[aux][3][2]=0;
			swap[0]=swap[0]-pro[aux][3][1];
			memo[0]=memo[0]+pro[aux][3][1];
			fl++;
			printf("Se movio la seccion de bibliotecas a memoria virtual\n");
		}
		if (fl==0)printf("No se pudieron mover las secciones\n");
	}else printf("Erro de indice\n");
}
void primPlano(int ***pro,int *pp,int *memo,int *swap){
	int aux,fl=0;
	printf("Ingresa la tarea que deseas enviar a memoria\n");
	scanf("%d",&aux);
	if (aux>=0 && aux<pp[0]){
		if (pro[aux][1][2]==0 && pro[aux][1][1]<=memo[0]){
			pro[aux][1][2]=1;
			swap[0]=swap[0]+pro[aux][1][1];
			memo[0]=memo[0]-pro[aux][1][1];
			fl++;
			printf("Se movio la seccion de codigo a memoria\n");
		}
		if(pro[aux][2][2]==0 && pro[aux][2][1]<=memo[0]){
			pro[aux][2][2]=1;
			swap[0]=swap[0]+pro[aux][2][1];
			memo[0]=memo[0]-pro[aux][2][1];
			fl++;
			printf("Se movio la seccion de datos a memoria\n");
		}
		if(pro[aux][3][2]==0 && pro[aux][3][1]<=memo[0]){
			pro[aux][3][2]=1;
			swap[0]=swap[0]+pro[aux][3][1];
			memo[0]=memo[0]-pro[aux][3][1];
			fl++;
			printf("Se movio la seccion de bibliotecas a memoria\n");
		}
		if (fl==0)printf("No se pudieron mover las secciones a Memoria\n");
	}else printf("Erro de indice\n");
}
void memSeg(int ***pro,int pp,int memo,int swap){
	int i,b,c,acum=0;
	printf("\n\n\tMemoria\n");
	for (i=0;i<memo;i++){
		printf("%d\t[___] Disponible\n",acum );
		acum++;
	}
	for (i=0;i<pp;i++){
		for (b=1;b<4;b++)
			if(pro[i][b][2]==1)
				for(c=0;c<pro[i][b][1];c++){
					printf("%d\t[___] Tarea %d seccion %d\n",acum,i,b);
					acum++;
				}
	}
	acum=0;
	printf("\n\tMemoria virtual\n");
	for (i=0;i<swap;i++){
		printf("%d\t[___] Disponible\n",acum );
		acum++;
	}
	for (i=0;i<pp;i++){
		for (b=1;b<4;b++)
			if(pro[i][b][2]==0)
				for(c=0;c<pro[i][b][1];c++){
					printf("%d\t[___] Tarea %d seccion %d\n",acum,i,b);
					acum++;
				}
	}
	printf("\nPresiona enter para continuar\n");
	getchar();
	getchar();
}
int ***killSeg(int ***pro,int *pp, int *memo){
	int i,aux,b;
	printf("Ingresa el id de la tarea que deseas matar\n");
	scanf("%d",&i);
	if (i>=0 && i<pp[0]){
		aux=pro[i][0][1];
		for (int b = i; b < pp[0]-1; ++b){
			pro[b][0][0]=pro[b+1][0][0];
			pro[b][1][0]=pro[b+1][1][0];
			pro[b][2][0]=pro[b+1][2][0];
			pro[b][3][0]=pro[b+1][3][0];
			pro[b][0][1]=pro[b+1][0][1];
			pro[b][1][1]=pro[b+1][1][1];
			pro[b][2][1]=pro[b+1][2][1];
			pro[b][3][1]=pro[b+1][3][1];
			pro[b][1][2]=pro[b+1][1][2];
			pro[b][2][2]=pro[b+1][2][2];
			pro[b][3][2]=pro[b+1][3][2];
		}
		memo[0]+=aux;
		--pp[0];
		pro=realloc(pro,(pp[0])*sizeof(int **));
		printf("Se elimino exitosamente\n");
		return pro;
	}else printf("Error de Id\n");
	return pro;
}
int funSegementacion(){
	int ***procesos,pp=0;//procesos
	int i,op,temp;//auxiliares
	int parTotales, swap, memoriaTotal, swapTotal, part, size;
	/*
	memoriaTotal en Mb
	size 		tamaño de las particiones
	parTotales 	slots totales en memoria
	swapTotal  	slots totales en SWAP
	part 	   	slots restantes en memoria
	swao 		slots restantes en SWAP
	*/
	procesos=(int ***) calloc(1,sizeof(int **));
	procesos[0]=(int **)calloc(4,sizeof(int*));
	for (i = 0; i < 4; ++i)
		procesos[0][i]=(int*)calloc(3,sizeof(int));
	if(procesos!=NULL && procesos[0]!=NULL && procesos[0][0]!=NULL){
		printf("Ingrese la memoria deseada en Mb\n");
		scanf("%d",&memoriaTotal);
		printf("Ingrese el tamano de las particiones Mb\n");
		scanf("%d",&size);
		parTotales=memoriaTotal/size;
		memoriaTotal=parTotales*size;
		swapTotal=parTotales;
		part=parTotales;
		swap=part;
		printf("\n*********** Dispone de %d particiones de %d Mb \n",parTotales,size);
		printf("\n*********** Con una memoria total usable de : %d Mb",memoriaTotal);
		while (1){
			printf("\n-----------------------------------------------------------------\n\n");
			printf("\tSegmentacion\n");
			printf("\t1 Agregar tarea\n");
			printf("\t2 Matar tarea\n");
			printf("\t3 Enviar a segundo plano\n");
			printf("\t4 Enviar a memoria\n");
			printf("\t5 Ver Memoria\n");
			printf("\t6 Ver procesos\n");
			printf("\t7 Salir\n");
			printf("\n-----------------------------------------------------------------\n\n");
			
			printf("ingresa la opcion\n");
			scanf("%d",&op);
			switch(op){
				case 1:
					procesos=addSeg(procesos,&pp,&part,&swap,size,memoriaTotal);
					break;
				case 2:
					procesos=killSeg(procesos,&pp,&part);	
					break;
				case 3:
					segPlano(procesos,&pp,&part,&swap);
					break;
				case 4:
					primPlano(procesos,&pp,&part,&swap);
					break;
				case 5:
					memSeg(procesos,pp,part,swap);
					break;
				case 6:
					verSeg(procesos,pp,part,swap);
					break;
				case 7:
					free(procesos);
					return 0;
				default:
					printf("\nOpcion no valida\n");
					printf("Precione enter para continuar\n");
					getchar();
					getchar();

			}
		}
	}else printf("No se pudo reservar memoria, ya que este programa usa memoria Dinamica\n");
	return 0;

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