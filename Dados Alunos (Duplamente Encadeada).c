//Programa de análise de dados de estudante ficcíonais.
//Disciplina: Estrutura de Dados;
//Autor: Douglas;

//Liberação das bibliotecas usadas no programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Especificação do tipo de dado NODO, usado na estrutura de dados
typedef struct nodo{
	struct nodo *anterior;
	char nome [20];
	int matricula;
	float nota1;
	float nota2;
	float nota3;
	float media;
	char nivel [10];
	struct nodo *proximo;
}Nodo;

//Criação do ponteiro inicial da estrutura de dados: Pilha
typedef struct{
	Nodo *inicio;
	int tam;
}Lista;

//Iniciando a criação do ponteiro;
Lista *criarLista (){
	Lista *lista = (Lista*) malloc (sizeof(Lista));
	lista->inicio = NULL;
	lista->tam = 0;
	return lista;
}

//Função para adicionar alunos, de forma ordenada na Estrutura de Dados
void push (Lista *lista, char nome[20], int matricula, float no1, float no2, float no3){
	Nodo *aux, *novo = (Nodo*) malloc (sizeof(Nodo));
	//Espeficicações dos campos do Nodo
	novo->anterior = NULL;
	strcpy(novo->nome, nome);
	novo->matricula = matricula;
	novo->nota1 = no1;
	novo->nota2 = no2;
	novo->nota3 = no3;
	novo->media = (no1 + no2 + no3)/3;
	if(novo->media >= 7){
		strcpy(novo->nivel, "Aprovado");
	}
	else{
		strcpy(novo->nivel, "Reprovado");
	}
	novo->proximo = NULL;
	
	//Organização para alocar o Nodo na estrutura de dados
	if(lista->inicio == NULL){
		lista->inicio = novo;
	}
	else if(strcmp(novo->nome, lista->inicio->nome) < 0){
		novo->proximo = lista->inicio;
		lista->inicio->anterior = novo;
		lista->inicio = novo;
	}
	else{
		aux = lista->inicio;;
		while(aux->proximo != NULL && strcmp(novo->nome, aux->proximo->nome) > 0){
			aux = aux->proximo;
		}
		novo->proximo = aux->proximo;
		if(aux->proximo){
			aux->proximo->anterior = novo;
		}
		aux->proximo = novo;
		novo->anterior = aux;
	}
	lista->tam++;
}

//Função para imprimir todos os dados dos alunos
void imprimir (Lista *lista){
	Nodo *aux = lista->inicio;
	int num = 1;
	while(aux != NULL){
		printf("\n\n============= Dados aluno %d ================\n", num);
		printf("\nNOME: %s", aux->nome);
		printf("\nMATRICULA: %d", aux->matricula);
		printf("\nNOTAS:\nNOTA 1: %.2f;\nNOTA 2: %.2f;\nNOTA 3: %.2f;", aux->nota1, aux->nota2, aux->nota3);
		printf("\nMEDIA: %.2f", aux->media);
		printf("\nSITUACAO: %s", aux->nivel);
		printf("\n================================================");
		num++;
		aux = aux->proximo;
	}
}

//Função para buscar um aluno específico na estrutura
Nodo* buscarAluno (Lista *lista, int matricula){
	Nodo *aux = lista->inicio;
	Nodo *aluno = NULL;
	
	while(aux != NULL && aux->matricula != matricula){
		aux = aux->proximo;
	}
	if(aux){
		aluno = aux;
	}
	return aluno;
	//Retorna os dados do aluno. Caso seja não exista o aluno, retorna NULL
}

//Função para remover aluno da Lista
Nodo *pop (Lista *lista, int matricula){
	Nodo *aux = lista->inicio;
	Nodo *remover = NULL;
	
	if(lista->inicio->matricula == matricula){
		remover = lista->inicio;
		lista->inicio = remover->proximo;
	}
	else{
		while(aux->proximo != NULL && aux->proximo->matricula != matricula){
			aux = aux->proximo;
		}
		if(aux->proximo){ //Verificar se não é nulo
			remover = aux->proximo;
			aux->proximo = remover->proximo;
			if(aux->proximo){ //Verificar se há um nodo após a posição do AUX
				aux->proximo->anterior = aux;
			}
		}
	}
	return remover;
	//Retorna os dados do aluno, caso este não exista, retornará NULL
}

//Função para saber se a lista está ou não vazia
int estaVazia (Lista *lista){
	if(lista->inicio == NULL){
		return 0;
	}
	else{
		return 1;
	}
}

//Programa Pincipal
void main (){
	Lista *lista = criarLista(); //Inicializando a lista
	int matricula, opcao;
	float nota1, nota2, nota3;
	char nome[20];
	do{ //Especificando os campos
		printf("\n=========================================\n");
		printf("================= MENU ==================\n");
		printf("\n=========================================\n");
		printf("\n1-Para adicionar um aluno;\n2-Para imprimir dados de um aluno;\n3-Para imprimir dados de todos os alunos;\n4-Para remover um aluno;\n0-Para encerrar o programa\n");
		printf("\n=========================================\n");
		scanf("%d", & opcao);
		system("cls");
		switch(opcao){
			case 1:
				printf("\n============= Adicionar Aluno =================\n");
				printf("\n===============================================\n");
				fflush(stdin);
				printf("\nNOME:");
				gets(nome);
				printf("\nMATRICULA:");
				scanf("%d", & matricula);
				printf("\nNOTAS:\nNOTA 1:");
				scanf("%f", & nota1);
				printf("\nNOTA 2:");
				scanf("%f", & nota2);
				printf("\nNOTA 3:");
				scanf("%f", & nota3);
				printf("\n===============================================\n");
				
				push(lista, nome, matricula, nota1, nota2, nota3);
				printf("\n\nAluno adicionado");
				system("cls");
			break;
			
			case 2:
				if(estaVazia(lista) != 0){
					printf("\n================= Imprimir dados do aluno =================");
					printf("\n===========================================================\n");
					printf("\nInforme a matricula do aluno: ");
					scanf("%d", & matricula);
					Nodo* aux = buscarAluno(lista, matricula);
					if(aux != NULL){
						printf("\n\n============= Dados aluno: %s ================\n", aux->nome);
						printf("\nNOME: %s", aux->nome);
						printf("\nMATRICULA: %d", aux->matricula);
						printf("\nNOTAS:\nNOTA 1: %.2f;\nNOTA 2: %.2f;\nNOTA 3: %.2f;", aux->nota1, aux->nota2, aux->nota3);
						printf("\nMEDIA: %.2f", aux->media);
						printf("\nSITUACAO: %s", aux->nivel);
						printf("\n================================================");
					}
					else{
						printf("\n\nAluno nao encontrado");
					}
					printf("\n===========================================================\n");
				}
				else{
					printf("\n\nA lista esta vazia");
				}
			break;
			
			case 3:
				if(estaVazia(lista) != 0){
					printf("\n================ Imprimindo lista de alunos ==================\n");
					printf("==================================================================\n");
					imprimir(lista);
					printf("==================================================================\n");
				}
				else{
					printf("\n\nA lista esta vazia");
				}
			break;
			
			case 4:
				if(estaVazia(lista) != 0){
					printf("\n===============  Remover aluno =================\n");
					printf("==================================================\n");
					printf("\nInforme a matricula do aluno: ");
					scanf("%d", & matricula);
					Nodo *remove = pop(lista, matricula);
					if(remove != NULL){
						free(remove);
						lista->tam--;
						printf("\n\nAluno removido");
					}
					else{
						printf("\n\nAluno nao encontrado");
					}
					printf("==================================================\n");	
				}
				else{
					printf("\n\nA lista esta vazia");
				}
				system("cls");
			break;
			
			default:
				if(opcao != 0){
					printf("\nValor digitado incorretamente, tente novamente.");
				}
		}
	}while(opcao != 0);
}
