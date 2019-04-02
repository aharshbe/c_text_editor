#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000

/*
  Forward declarations
*/
char *sighand(char* buffer);
int write(char *buffer);
char *filename(char *buffer);
char *strcoppy(char *original);
char **tokenize(char *buffer, char token);
int free_tokens(char **tokens);
char *input();

/*
  Main function
*/
int main(void){
  char* release = sighand(input());
  int val = write(release);
  return val;
}


/*
  Get name of document, write it to a file and save contents
  Free buffers
*/
int write(char *buffer){
  char **tokens = tokenize(buffer, '\n');
  char *name = tokens[0];
  FILE *ptr = fopen(name,"w");
  int size = strlen(name)+1;

  if (!tokens || !name || !ptr || !size)
    return 1;

  fputs(buffer+size,ptr);

  fclose(ptr);
  free_tokens(tokens);

  return 0;
}

char **tokenize(char *buffer, char token){
  char*copy=malloc(sizeof(char*)*MAX);
  char**copies=malloc(sizeof(char*)*MAX);

  if (!copy || !copies)
    return NULL;

  copies[0] = malloc(MAX);
  for (int i = 0, c = 0, s = 0; buffer[i]; i++){
    if (buffer[i] != '\n')
      copies[c][s++] = buffer[i];
    else {
      copies[++c] = malloc(MAX);
      s = 0;
    }
  }
  return copies;
}

char *strcoppy(char *original){
  char *copy = malloc(sizeof(char*)*MAX);
  if (!copy)
    return NULL;

  for (int i = 0; original[i]; i++){
    copy[i] = original[i];
  }
  return copy;
}

char* sighand(char*buffer){
  if (strcmp(buffer, "^D"))
    printf("Saving and exiting...\n");
  return buffer;
};

char* input(void){
  int i = 0, x = 0;
  char *ptr = malloc(sizeof(char*)*MAX);
  if (!ptr)
    return NULL;

  while((x = getchar())){
    if (x == EOF)
      break;
    ptr[i++] = x;
  }
  return ptr;
}

int free_tokens(char **tokens){
  if (!tokens)
    return 1;
  for (int i = 0; tokens[i]; i++){
    free(tokens[i]);
  }
  free(tokens);
  return 0;
}
