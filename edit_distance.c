
//Prajwal Rana
//1001531196

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "edit_distance.h"


void free_table(char** table,int n)  //free table
{
  int i=0;
  while(i<n)
  {
    free(table[i]); //free every index
    i++;
  }
  free(table); //free address of table
}

int minimum(int a,int b,int c) //compare all values here
{
  int small=0;
  if(a<b)
  {
    small=a;
  }
  else if(a>b)
  {
    small=b;
  }
  else
  {
    small=a;
  }
  if(small>c)
  {
    small=c;
  }

  return small;
}

int edit_distance(char * first_string, char * second_string, int print_table)
{
  int row=strlen(first_string)+1;
  int column=strlen(second_string)+1;

  int store[row][column];
  int max1,max2;
  int i,j,k,l;

  for(i=0;i<row;i++)
  {
    for(j=0;j<column;j++)
    {
      if(i==0 && j==0)  //put zero on first index of both row and column
      {
        store[i][j]=0;
      }
      else if(i==0)  //gve values to first row and all column
      {
        store[i][j]=j;
      }
      else if(j==0)  //give values to all row sand first column
      {
        store[i][j]=i;
      }
      else if(i!=0 && j!=0)  //initialize other rows and columns
      {
        if(first_string[i-1]==second_string[j-1])
        {
          store[i][j]=minimum(1+store[i-1][j],1+store[i][j-1],store[i-1][j-1]);
        }
        else
        {
          store[i][j]=minimum(1+store[i-1][j],1+store[i][j-1],1+store[i-1][j-1]);
        }
      }
      max1=j;  //record the last column
    }
    max2=i; //record the last row
  }

  if(print_table==1)
  {
    int row_length=row+1;            //increase length of row to print strings
    int column_length=column+1;       //increase lenght of column to print strings
    int p=0;
    int z=0;

    printf("\n");

    for(k=0;k<row_length;k++)     //it keeps track of rows
    {
      for(l=0;l<column_length;l++) //it keeps track of column
      {
        if(k==0)   //if row is zero
        {
          if(l==0)      //and if the column is 0 or 1
          {
            printf("%2c|",' ');//keep changing these numbers
          }
          else if(l==1)
          {
            printf("%3c|",' ');
          }
          else
          {
            printf("%3c|",second_string[p]);  //row iz zero but colum is not 0 or 1 print character
            p++;
          }
        }
        else if(k==1)  //if row is 1
        {
          if(l==0)    //if column is zero
          {
            printf("%2c|",' ');
          }
          else         //else print value from the 2d array in that index
          {
            printf("%3d|",store[k-1][l-1]);    //substract 1 from index to get to the actual index because we added 1 to add strings on the
          }                                    //outer side
        }
        else   //if row is not 0 or 1
        {
          if(l==0)
          {
            printf("%2c|",first_string[z]);  //if column is zero print character
            z++;
          }
          else       //row is not zero, print data from array
          {
            printf("%3d|",store[k-1][l-1]); //substract 1 from index to get to the actual index because we added 1 to add strings on the
          }                                  //outer side
        }
      }
      printf("\n");

      for(j=0;j<column_length;j++)   //print dashed horizontal lines after every row
      {
        if(j==0)
        {
          printf("---");
        }
        else
        {
          printf("----");
        }
      }
      printf("\n");
    }
    printf("\n");
  }

  return store[max2][max1];  //return the last index
}

void spellcheck(char * dictname, char * testname)
{
  FILE* fp;
  FILE* fp2;
  char name[20];
  char name2[20];
  int size;
  int counter=0;
  int n=0;
  char* token;
  char* token2;
  int i=0;
  int l=0;

  printf("\n");
  printf("Loading the dictionary file:%s\n",dictname);
  printf("Loading the test file:%s\n",testname);

  fp=fopen(dictname,"r");  //open first file

  if(fp==NULL)
  {
    printf("File could not be opened\n");
  }
  else
  {
    while(fgets(name,20,fp)!=NULL)
    {
      counter++;
    }
  }

  char **table = malloc(sizeof(char *) * counter); //make an array equal to lines in a file

  int allocated=0;
  int length=0;
  fseek(fp,0,SEEK_SET);

  while(fgets(name,20,fp)!=NULL)
  {
    token = strtok(name, "\n"); //get rid of new line at the end
    length = strlen(token)+1; //add +1 to malloc 1 more than actual size
    allocated = length + allocated; //it calculates total memory allocated for all words
    (table[i]) = malloc(length); //malloc inside array to store data
    strcpy(table[i],token); //copy data to array
    i++;
  }
  fclose(fp); //close first file

  printf("\n");

  fp2=fopen(testname,"r"); //open second file
  if(fp2==NULL)
  {
    printf("File could not be opened\n");
  }
  else
  {
    while(fgets(name2,20,fp2)!=NULL)
    {
      n++;
    }
  }

  char **table2 = malloc(sizeof(char *) * n);  //make an array equal to lines in a file

  int allocated2=0;
  int length2=0;

  fseek(fp2,0,SEEK_SET);

  while(fgets(name2,20,fp2)!=NULL)
  {
    token2 = strtok(name2, "\n"); //get rid of new line at the end
    length2 = strlen(token2)+1; //add +1 to malloc 1 more than actual size
    allocated2 = length2 + allocated2; //it calculates total memory allocated for all words
    (table2[l]) = malloc(length2); //malloc inside array to store data
    strcpy(table2[l],token2); //copy data to array
    l++;
  }
  fclose(fp2);//close second file


  int len,len2,y;
  int min_dist=0;
  int found=0;

  for(len=1;len<n;len++) //runs till the length of data4 file
  {
    printf("-------current test word:%s\n",table2[len]);
    for(len2=0;len2<counter;len2++) //runs till the length of dictionary file
    {
      found=edit_distance(table2[len],table[len2],2); //returns minimum distance
      if(min_dist==0)       //store the first value as minimum
      {
        min_dist=found;
      }
      else
      {
        if(min_dist>found)  //store the smallest value as minimum
        {
          min_dist=found;
        }
      }
    }
    printf("Minimum distance:%d\n",min_dist);
    printf("Words that give minimum distance:\n");
    for(y=0;y<counter;y++) //runs till the length of dictionary file
    {
      found=edit_distance(table2[len],table[y],2);  //returns minimum distance
      if(found==min_dist)  //if mimum distances are equal print the words
      {
        printf("%s\n",table[y]);
      }
    }
    min_dist=0; //reset min_dist value to store the first distance at every iteration
    printf("\n");
  }

  free_table(table,counter);  //free memory
  free_table(table2,n);     //free memory
}
