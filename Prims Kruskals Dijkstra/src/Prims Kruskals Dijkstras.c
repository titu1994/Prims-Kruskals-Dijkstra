/*
 ============================================================================
 Name        : Prims.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define N 4
#define INFINITY 32767

typedef struct Edge{
	int p,c,w;
}Edge;

void createWeightedGraph(int a[N][N]);
void Prims(int a[N][N]);
void Dijkstra(int a[N][N]);
void Kruskals(int a[N][N]);

int main(void) {
	int ch, a[N][N];

	setbuf(stdout,NULL);
	printf("Enter choice : \n1 for Create Graph\n2 for Prims\n3 For Kruskals\n4 for Dijkstras\n");

	do{
		printf("Enter choice : ");
		scanf("%d",&ch);

		switch(ch){
		case 1:{
			createWeightedGraph(a);
			break;
		}
		case 2:{
			Prims(a);
			break;
		}
		case 3:{
			Kruskals(a);
			break;
		}
		case 4:{

			Dijkstra(a);
			break;
		}
		default:{
			ch = -1;
		}
		}

	} while(ch != -1);

	return EXIT_SUCCESS;
}

void createWeightedGraph(int a[N][N]){
	int i,j,w,ch;
	char x,y;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			a[i][j] = INFINITY;
		}
	}

	do{
		fflush(stdin);

		printf("Enter the edge names : ");
		scanf("%c%c", &x,&y);

		x = toupper(x);
		y = toupper(y);

		printf("Enter the weight of this edge : ");
		scanf("%d", &w);

		a[x-65][y-65] = w;
		a[y-65][x-65] = w;

		printf("Enter 1 to continue adding edges : ");
		scanf("%d", &ch);

	}while(ch == 1);
}

void Prims(int a[N][N]){
	int dist[N], previous[N], selected[N] = {0};
	int i,c,x;
	int sum = 0, d, m, min;
	int start = 65;
	x = 0;

	for(i = 0; i < N; i++)
		dist[i] = INFINITY;

	start -= 65;

	dist[start] = 0;
	selected[start] = 1;

	for(c = 1; c < N; c++) {
		for(i = 0; i < N; i++) {
			d = a[start][i];

			if(!selected[i] && d < dist[i]){
				dist[i] = d;
				previous[i] = start;
			}
		}

		min = INFINITY;
		m = start;

		for(i = 0; i < N; i++){
			if(!selected[i] && dist[i] < min){
				min = dist[i];
				m = i;
			}
		}

		start = m;
		selected[start] = 1;
	}

	// To Print Edges
	printf("Selected edges are : \n");
	for(i = 0; i < N; i++){
		if(i != x){
			printf("%c\t%c\n", previous[i] + 65, i+65);
		}

		sum += dist[i];
	}

	printf("Cost of tree : %d\n", sum);
}

void Dijkstra(int a[N][N]){
	int dist[N], previous[N], selected[N] = {0};
	int i,j,c,x;
	int sum = 0, d, m, min;
	char p[N] = {0};
	int k;
	int start = 65;
	x = 0;


	for(i = 0; i < N; i++)
		dist[i] = INFINITY;

	start -= 65;

	dist[start] = 0;
	selected[start] = 1;

	for(c = 1; c < N; c++){
		for(i = 0; i < N; i++){
			d = dist[start] + a[start][i];

			if(!selected[i] && d < dist[i]){
				dist[i] = d;
				previous[i] = start;
			}
		}

		min = INFINITY;
		m = start;

		for(i = 0; i < N; i++){
			if(!selected[i] && dist[i] < min){
				min = dist[i];
				m = i;
			}
		}

		start = m;
		selected[start] = 1;
	}

	// To Print Edges
	printf("Selected edges are : \n");
	for(i = 0; i < N; i++){
		if(i != x){
			printf("%c\t%c\n", previous[i] + 65, i+65);
		}

		sum += dist[i];
	}

	printf("Cost of tree : %d\n", sum);

	printf("Paths : \n");

	for(i = 0; i < N; i++){
		k = 0;

		if(i != x){
			j = i;
			p[k++] = j+65;

			while(j != x){
				j = previous[j];
				p[k++] = j+65;
			}

			p[k] = '\0';
			strrev(p);

			printf("%s\n", p);
		}
	}

}


void Kruskals(int a[N][N]){
	int i,j, sum = 0;
	int previous[N];
	int edgecount = 0;

	Edge e[50], t;

	for(i = 0; i < N; i++){
		for(j = i+1; j < N; j++){
			if(a[i][j] != INFINITY){
				e[edgecount].p = i;
				e[edgecount].c = j;
				e[edgecount].w = a[i][j];
				edgecount++;
			}
		}
	}

	for(i = 1; i < edgecount; i++){
		for(j = 0; j < edgecount - i; j++){
			if(e[j].w > e[j+1].w){
				t = e[j];
				e[j] = e[j+1];
				e[j+1] = t;
			}
		}
	}

	for(i = 0; i < N; i++)
		previous[i] = -1;

	int ec = 0;

	for(i = 0; i < edgecount && ec < N-1; i++){
		int p,c;
		p = e[i].p;
		c = e[i].c;

		while(previous[p] != -1)
			p = previous[p];

		while(previous[c] != -1)
			c = previous[c];

		if(p != c){
			printf("%c\t%c\n", e[i].p + 65, e[i].c + 65);

			sum += e[i].w;

			previous[c] = p;
			ec++;
		}

	}

	printf("Weight of tree is : %d",sum);

}
