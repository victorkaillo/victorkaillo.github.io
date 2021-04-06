---
layout: page
title: Progrmação Paralela
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


## Programação Concorrente e Distribuída

Conceitos obeservados no livro-texto: [An Introduction to Parallel Programming by Peter Pacheco](https://www.cs.usfca.edu/~peter/ipp/index.html) 



### Primeiro programa usando MPI:

```cpp
/* File:       
 *    mpi_hello.c
 *
 * Purpose:    
 *    A "hello,world" program that uses MPI
 *
 * Compile:    
 *    mpicc -g -Wall -std=C99 -o mpi_hello mpi_hello.c
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
   int        my_rank;               /* My process rank        */

   /* Start up MPI */
   MPI_Init(NULL, NULL); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank != 0) { 
      /* Create message */
      sprintf(greeting, "Greetings from process %d of %d!", 
            my_rank, comm_sz);
      /* Send message to process 0 */
      MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,
            MPI_COMM_WORLD); 
   } else {  
      /* Print my message */
      printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
      for (int q = 1; q < comm_sz; q++) {
         /* Receive message from process q */
         MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,
            0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         /* Print message from process q */
         printf("%s\n", greeting);
      } 
   }

   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */

```
