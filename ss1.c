#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#define _GNU_SOURCE

#define N 19
#define M 9
#define SIZE 100 
int dir_list[150];
int I = 0;
int mno;

// maze of m*n matrix 
int n = N, m = M; 

int fx, fy; 
int visited[M][N]; 


struct node { 

	int x, y; 
	int dir; 
}; 

struct stack
{
    struct node items[SIZE];
    int top;
};


        
struct node pop(struct stack *s)
{
    if(s->top==-1)
    {
        printf("Stack underflow\n");
        exit(-1);
    }
    return s->items[s->top--];
}
void push(struct stack *s,struct node n)
{
    
    if(s->top == SIZE-1)
    {
        printf("Stack Overflow\n");
        exit(-1);
    }
    s->items[++s->top] = n;
}

void display(struct stack s)
{
    //int i=0;
    struct stack tmp;
    struct node tmp2;
    int ctr = 1;
    tmp.top=-1;
    while(s.top!=-1)
    {
       push(&tmp,pop(&s));
    }
    while(tmp.top!=-1)
    {
	tmp2=pop(&tmp);
    dir_list[I++] = tmp2.dir;
	//printf("\n%d. x = %d, y = %d, dir = %d\n",ctr,tmp2.x,tmp2.y,tmp2.dir);
        ctr++;
    }
}

void create_node(struct node *temp,int i,int j)
{
    temp->x = i;
    temp->y = j;
    temp->dir = 0;
}



int isReachable(int maze[M][N]) 
{ 
	// Initially starting at (0, 0). 
	int i = 0, j = 0; 
	
	struct stack s;
    s.top = -1; 
	struct node temp,temp1;
	create_node(&temp,i, j); 
    //printf("\n\nbMIDWAY x = %d, y = %d\n\n",temp.x,temp.y);
	
	push(&s,temp); 

	while (s.top != -1) { 
        //printf("HELLO3");

		// Pop the top node and move to the 
		// left, right, top, down or retract 
		// back according the value of node's 
		// dir variable. 
		temp = pop(&s);//s.items[s.top]; 
		int d = temp.dir; 
		i = temp.x, j = temp.y; 
        //printf("\n\nMIDWAY i = %d, j = %d\n\n",i,j);

		// Increment the direction and 
		// push the node in the stack again. 
		temp.dir++; 
		//pop(&s); 
		push(&s,temp); 

		
		// return 1 
		if (i == fx && j == fy) {
            display(s); 
			return 1; 
		} 

		// Checking the Up direction. 
		if (d == 0) { 
			if (i - 1 >= 0 && maze[i - 1][j] && visited[i - 1][j]) { 
				create_node(&temp1,i - 1, j); 
				visited[i - 1][j] = 0; 
				push(&s,temp1); 
			} 
		} 

		// Checking the left direction 
		else if (d == 1) { 
			if (j - 1 >= 0 && maze[i][j - 1] &&	visited[i][j - 1]) { 
				create_node(&temp1,i, j - 1); 
				visited[i][j - 1] = 0; 
				push(&s,temp1); 
			} 
		} 

		// Checking the down direction 
		else if (d == 2) { 
			if (i + 1 < m && maze[i + 1][j] && visited[i + 1][j]) { 
				create_node(&temp1,i + 1, j); 
				visited[i + 1][j] = 0; 
				push(&s,temp1); 
			} 
		} 
		// Checking the right direction 
		else if (d == 3) { 
			if (j + 1 < n && maze[i][j + 1] &&	visited[i][j + 1]) { 
				create_node(&temp1,i, j + 1); 
				visited[i][j + 1] = 0; 
				push(&s,temp1); 
			} 
		} 

		// If none of the direction , retract back 
        
		else { 
           
            visited[temp.x][temp.y] = 1; 
			pop(&s); 
		} 
	} 

	return 0; 
} 

void save_path()
{
   
    
    int k;
    char buf[10],full_str[100]="",new_buf[50];
    for(k=0;k<I;k++)
    {
        
        sprintf(buf,"%d",dir_list[k]);
        strcat(full_str,buf);

    }

    sprintf(new_buf,"./maze_solver.py solution %s %d",full_str,mno);
    system(new_buf);

}

int get_x(int n)
{
   if(n>=40 && n<=49)
    return 0;
    if(n>=30 && n<=39)
    return 2;
    if(n>=20 && n<=29)
    return 4;
    if(n>=10 && n<=19)
    return 6;
    if(n>=0 && n<=9)
    return 8;
}

int get_y(int n)
{
    return (n%10)* 2;
}



int main(int argc,char *argv[]) 
{ 
    int ch;
    char new_buf[50];
    printf("Enter maze no: ");
    scanf("%d",&mno);
    printf("\nEnter 0 to display the unsolved maze, 1 to continue: ");
    scanf("%d",&ch);
    if(ch==0)
    {
        sprintf(new_buf,"./maze_solver.py empty %d",mno);
        system(new_buf);
     
    }
    int x,y;
    int maze[M][N];
    FILE * fp;
    char *line; 
    
    size_t len = 0;
    ssize_t read;
    int i=0;
    char lines[500][20];

    fp = fopen("./maze.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    
        strcpy(lines[i],line);
    
        i++;
    }
    strcpy(lines[i], "");

    fclose(fp);
    if (line)
        free(line);
   
    int num_digits = 0,digits[3],this_num;
    char this_line[5],this_chr[2],direction;
    int j=0;
    i = 0;
    while(lines[i][0]!='\0' && lines[i][0]!=' ')
    {
        //printf("Processing \"%s\" (i = %d)....\n", lines[i], i);
        j=0;
        strcpy(this_line,lines[i]);
        num_digits = 0;
        while(this_line[j]!='\n'&&this_line[j]!=' '&&this_line[j]!='\0' && j<5)
        {
          
            this_chr[0] = this_line[j];
            this_chr[1] = '\0';
            if(isdigit(this_line[j]))
            {
                digits[num_digits] = atoi(this_chr);
                num_digits++;
                
            }
            else{
                direction = this_line[j];

            }
                
            j++;
        }
        if(num_digits == 2)
           this_num = digits[0] * 10 + digits[1];
        else if(num_digits == 1)
           this_num = digits[0];
        
        //printf("\tthis num is %d, direction is %c\t",this_num,direction);
        x = get_x(this_num);
        y = get_y(this_num);
        if(direction == 'd')
        {
            maze[x+1][y] = 1;
            maze[x+2][y] = 1;
            
        }
        if(direction == 'u')
        {
            maze[x-1][y] = 1;
            maze[x-2][y] = 1;
            
        }
        if(direction == 'l')
        {
            maze[x][y-1] = 1;
            maze[x][y-2] = 1;
            
        }
        if(direction == 'r')
        {
            maze[x][y+1] = 1;
            maze[x][y+2] = 1;
            
        }
        
        
        
            
        i++;
        
       
    }
    
    
    
    
    
	// Initially setting the visited 
	// array to 1 (unvisited) 
	
/*
	
	// Maze matrix 
	int maze[N][M] = { 
		{1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,1,0,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0},
		{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
		{0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
		{1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1},
		{1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0},
		{1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1}
	}; 
    
1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 
1 0 0 0 1 0 1 0 0 0 1 0 1 0 0 0 0 0 1 
1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 0 1 1 1 
1 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0 0 
1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 0 1 
0 0 1 0 1 0 0 0 1 0 1 0 0 0 0 0 1 0 1 
1 1 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 1 1 
1 0 0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 
1 1 1 1 1 1 1 0 1 1 1 0 1 1 1 1 1 1 1
*/


    memset(visited,1, sizeof(visited)); 
	fx = 8; 
	fy = 18; 

	if (isReachable(maze)) { 
		printf("Path Found!\n");
         
       
        save_path();
        
        
        
	} 
	else
		printf("No Path Found!\n"); 
    printf("\nmaze.txt has been deleted\n");
	unlink("maze.txt");	
	return 0; 
} 
