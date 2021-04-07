---
layout: page
title: Programação Paralela
permalink: /pcd/
show_meta: true
# imagefeature path is relative to images/ directory.
imagefeature: tutoriais.jpg
published: true
description: "Vamos aqui apresentar conceitos referentes a programação paralela. "
category: views
comments: false
mathjax: true
noindex: false
sitemap:
    priority: 0.7
    changefreq: 'monthly'
    lastmod: 2021-03-31
# tags will be used as html meta keywords.    
tags:
  - "pcd"
---


# Programação Concorrente e Distribuída

Conceitos obeservados no livro-texto: [An Introduction to Parallel Programming by Peter Pacheco](https://www.cs.usfca.edu/~peter/ipp/index.html) 

## MPI

### Programas MPI:
* São escritos em linguagem C
* Têm a função main
* Precisão adicionar o arquivo cabeçário mpi.h
* Podem ter outros cabeçarios
* Todas as funções MPI começão com "MPI_" a letra segiunte é maiúscula e as demais não são. 


### Compilação 
Todo ambiente de compilação MPI tem um compilador específico para MPI. 

```terminal 
mpicc -g -Wall -o mpi_hello mpi_hello.c
``` 
* mpicc é um envelope que pode chamar por exemplo gcc, icc, PGI Compiler.

Este envelope pode passar outras flags embutidas. O restante das flags comportação normalmemte como em uma compilação padrão: 
* -g para depuração
* -Wall para aparesentar todos os warnings
* -o para criar executavel com nome do argumento seguinte
* {}.c código fonte

### Execução

```terminal 
mpiexec -n <número de processos> <exeutável> 
``` 
Exemplos a partir do código mpi_hello.c:
* <code> mpiexec -n 1 ./mpi_hello </code> ->
Não executa o if, executa o else e execulta apenas a linha "printf"
Não haverá nem envio, nem recebimento de mensagens
Variável "q" começa em 1 e não será menor que <code> comm_sz </code> 
* <code>mpiexec -n 4 ./mpi_hello</code> ->
Executa o programa com envios e recebimentos de mensagens


### Meu primeiro programa usando MPI:

```cpp
/* File:       
 *    mpi_hello.c
 *
 * Purpose:    
 *    A "hello,world" program that uses MPI
 *
 * Compile:    
 *    mpicc -g -Wall -std=c99 -o mpi_hello mpi_hello.c
 * Usage:        
 *    mpiexec -n<number of processes> ./mpi_hello
 *
 * Input:      
 *    None
 * Output:     
 *    A greeting from each process
 *
 * Algorithm:  
 *    Each process sends a message to process 0, which prints 
 *    the messages it has received, as well as its own message.
 *
 * IPP:  Section 3.1 (pp. 84 and ff.)
 */
#include <stdio.h> /*biblioteca de entrada e saida da ling. C, precisa carregar quando se usa funcoes com printf, sprintf*/
#include <string.h> /* For strlen -> para manipulacao de string, esse "hello word" eh uma troca de saudacoes entre os processos e essas saudacoes sao vetores de caracteres que sao strings em C*/
#include <mpi.h> /*For MPI functions, etc - responsavel por estabelecer a comunicao entre os diversos programas diferentes */

const int MAX_STRING = 100; /* poderia ser um DEFINE */

int main(void) {
   char       greeting[MAX_STRING];  /* String storing message */
   int        comm_sz;               /* Number of processes -> tamanho do comunicador   */
   int        my_rank;               /* My process rank     -> equivalente ao indice do processo   */

   /* Start up MPI -> sempre inicia o programa MPI*/
   MPI_Init(NULL, NULL); 

   /* Get the number of processes -> inicializa a variavel comm_sz com o numero de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* MPI_COMM_WORLD (e uma MACRO) -> e um comunicador padrao global MPI, onde todos os processos participao da comunicacao; sempre usamos em programas MPI*/

   /* Get my rank among all the processes -> inicializa a variavel my_rank com o numero do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   /*Quando o programa entra em execucao em si, cada chamada tera um rank diferente*/

   if (my_rank != 0) { /*todos os ranks que nao sejam zero vao entrar nesse "if" e execultar estas intrucoes*/
      /* Create message */
      /*escreve a string referenciada entre aspas no buffer de caracteres declarado previamente*/
      sprintf(greeting, "Greetings from process %d of %d!", 
            my_rank, comm_sz);
      /* Send message to process 0 */
      /* MPI_Send -> envia o ponteiro greeting de tamanho strlen(greeting)+1 e tipo MPI_CHAR  */
      MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, 
            MPI_COMM_WORLD);                                 /* MPI_COMM_WORLD -> comunicador */
   } else {  /*se o rank for zero:*/
      /* Print my message */
      printf("Greetings from process %d of %d!\n", my_rank, comm_sz); /* ao inves de armazenar a string no buffer, ja o imprime na saida/tela */
      for (int q = 1; q < comm_sz; q++) {
         /* Receive message from process q */
         /* MPI_Recv -> recebe o ponteiro greeting de tamanho MAX_STRING e tipo MPI_CHAR, q -> indice do processo */
         MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 
            0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /*MPI_COMM_WORLD -> comunicador; MPI_STATUS_IGNORE -> ignora a variavel de status */
         /* Print message from process q */
         printf("%s\n", greeting);
      } 
   }

   /* Shut down MPI -> sempre finaliza o programa MPI*/
   MPI_Finalize(); 

   return 0;
}  /* main */
```

### Componentes importantes: 
* MPI_Init(argc_p,argv_p): Setup todo programa MPI. Informa através de ponteiros os argumentos da main para o programa MPI quando houver necessidade.
* MPI_Finalize(void): Finaliza o programa MPI e limpa tudo que foi alocado.

### Esqueleto Básico de um programa MPI:

```cpp
#include <mpi.h> 
int main(int argc, char* argv[]) {
   /* Chamadas que não são MPI */
   MPI_Init(&argc, &argv); 
   /* Chamadas que são MPI */
   MPI_Finalize(); 
   /* Chamadas que não são MPI */
   return 0;
}
```
### Comunicadores:
* Uma coleção de processos que enviam mensagens uns para os outros.
* <code> MPI_COMM_WORLD </code> -> Comunicador global
* Comunicador tem uma estrutura de dados que sabe quais processos estão em execução e qual o endereço de cada processo afim de ficar transparente para os processos a comunicação.
* MPI_Init define o comunicador e é executado assim que o programa inicial.
* MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); define o numero de processos que estão participando.
* MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); define cada processo com um índice.
* comm_sz -> Informa para o processo o número total de processos.
* my_rank -> Informa qual o processo atual.

### SPMD
* Simple Program, Multiple Data
* Único Programa (código fonte), Múltiplos Dados.
* Compilação de um único código.
* Normalmente o processo 0 executa uma tarefa diferente dos demais.

### Comunicação
##### MPI_Send
* MPI_Send(msg_buf_p, msg_size, msg_type, dest, tag, comunicator)
* msg_buf_p -> ponteiro para o buffer de envio (onde está guardada a mensagem).
* msg_size -> tamanho do buffer que será enviado.
* msg_type -> tipo do dado.
* dest -> numero do rank (índice) de destino.
* tag -> etiqueta para identificar a mensagem.
* comunicator -> utilizamos o Comunicador global. Mas se pode criar comunicadores próprios.

##### MPI_Recv

* MPI_Recv(msg_buf_p, msg_size, msg_type, source, tag, comunicator, status_p)
* msg_buf_p -> ponteiro para o buffer de envio (onde está guardada a mensagem).
* msg_size -> tamanho do buffer de recebimento em bits.
* msg_type -> tipo do dado esperado.
* source -> numero do rank (índice) de origem.
* tag -> etiqueta para identificar a mensagem.
* comunicator -> utilizamos o Comunicador global. Mas se pode criar comunicadores próprios.
* status_p -> pode-se colher informações do recebimento. Número de dados recebidos, por exemplo.
* há tags que possibilitam que o programa receba a mensagem de qualquer origem (MPI_ANY_SOURCE) ou qualquer tag (MPI_ANY_TAG)
* nesse caso, usa-se o campo status para saber qual a origem (status.MPI_SOURCE) ou qual a tag (status.MPI_TAG).

##### MPI_Get_count 

* Usada pela MPI_Status para saber quantos dados foram recebidos.
* MPI_Get_count(status_p, type, count_p).
* count_p -> variável que retorna quantos dados foram recebidos.

##### Comportamento de Send e Recv

* Quando não há bloqueio no MPI_Send, voçê pode alterar o dado do buffer antes de ser enviado.
* Sempre há bloqueio no MPI_Recv. Nunca passará de um ponto sem que a mensagem seja recebida.

### Aproximação de integral

Dadas estas informações vamos avançar para um programa MPI mais útil que apenas um Hello.


```cpp
/* File:    trap.c
 * Purpose: Calculate definite integral using trapezoidal 
 *          rule.
 *
 * Input:   a, b, n
 * Output:  Estimate of integral from a to b of f(x)
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -o trap trap.c
 * Usage:   ./trap
 *
 * Note:    The function f(x) is hardwired.
 *
 * IPP:     Section 3.2.1 (pp. 94 and ff.) and 5.2 (p. 216)
 */

#include <stdio.h>

double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n, double h);

int main(void) {
   double  integral;   /* Store result in integral   */
   double  a, b;       /* Left and right endpoints   */
   int     n;          /* Number of trapezoids       */
   double  h;          /* Height of trapezoids       */

   printf("Enter a, b, and n\n");
   scanf("%lf", &a);
   scanf("%lf", &b);
   scanf("%d", &n);

   h = (b-a)/n;
   integral = Trap(a, b, n, h);
   
   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %.15f\n",
      a, b, integral);

   return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Estimate integral from a to b of f using trap rule and
 *              n trapezoids
 * Input args:  a, b, n, h
 * Return val:  Estimate of the integral 
 */
double Trap(double a, double b, int n, double h) {
   double integral;
   int k;

   integral = (f(a) + f(b))/2.0;
   for (k = 1; k <= n-1; k++) {
     integral += f(a+k*h);
   }
   integral = integral*h;

   return integral;
}  /* Trap */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  /* f */

```