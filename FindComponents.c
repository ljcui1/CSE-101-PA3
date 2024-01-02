//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA2
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){

   
   FILE *in, *out;

   //open files for reading and writing 
   //check command line for correct number of arguments
//    if( argc != 3 ){
//       printf("Usage: %s <input file> <output file>\n", argv[0]);
//       exit(1);
//    }
   in = fopen(argv[1], "r");
 //  in = fopen("in1.txt", "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
//   out = fopen("out.txt", "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   //read 1st part

    int n = 0;
    fscanf(in, "%d", &n);
    Graph g = newGraph(n);

    int uVertex = 0;
    int vVertex = 0;
    fscanf(in, "%d %d\n", &uVertex, &vVertex);
    while(uVertex != 0 || vVertex != 0){
        addArc(g, uVertex, vVertex);
        fscanf(in, "%d %d\n", &uVertex, &vVertex);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, g);
    fflush(out);

    List  S = newList();
    for (int i = 1; i <= getOrder(g); i++) append(S, i);
	DFS(g, S);
	Graph T = transpose(g);
	DFS(T, S);

	int num_scc = 0;
	for (moveBack(S); index(S) >= 0; movePrev(S)) {
		int j = get(S);
		if (getParent(T, j) == NIL) {
			num_scc++;
		}
	}
    
    fprintf(out, "\nG contains %d strongly connected components:\n", num_scc);

    num_scc = 1;
	List LT = newList();
	for (moveBack(S); index(S) >= 0; movePrev(S)) {
		int j = get(S);
		prepend(LT, j);
		if (getParent(T, j) == NIL) {
			fprintf(out, "Component %d: ", num_scc);
			printList(out, LT);
			fprintf(out, "\n");
			clear(LT);
			num_scc++;
		}
	}
   //close files 
   fclose(in);
   fclose(out);
   freeGraph(&g);

   return(0);
}