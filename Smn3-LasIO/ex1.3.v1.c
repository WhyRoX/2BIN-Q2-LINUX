#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../utils_v1.h"

#define MAX 80

//*****************************************************************************//
// USAGE
//*****************************************************************************//

void checkUsage(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s file1 file2\n", argv[0]);
  }
}


//*****************************************************************************//
// READ FUNCTION
//*****************************************************************************//

/**
 * Reads a line from the given file descriptor and copies it into the buffer line.
 * PRE: fd: file descriptor from which to read
 *      line: char array of size max
 *      lengthLine: pointer to an integer to store the length of the read line
 *      lengthTot: pointer to an integer to store the total length of the read characters
 * POST: a string of at lengthLine (<=max) characters has been read from fd and 
 *       placed in line (including '\n'); if '\n' is not among the max read characters,
 *       the keyboard buffer is emptied and lengthTot indicates the number of read characters
 */
// version avec lecture caractère par caractère
void sreadLine(int fd, char *line, int *lengthLine, int *lengthTot, int max) {
  *lengthLine = 0;
  *lengthTot = 0;
  char current;
  ssize_t bytesRead;
  
  bool eol = false;
  while (!eol && (bytesRead = read(fd, &current, 1)) > 0) {
    eol = current == '\n';
    (*lengthTot)++;
    
    if (*lengthLine < max) {
      line[*lengthLine] = current;
      (*lengthLine)++;
    }
  }
  checkNeg(bytesRead, "Error READ");
} 

//*****************************************************************************//
// MAIN
//*****************************************************************************//

int main(int argc, char *argv[]) {
  checkUsage(argc, argv);
  int r;
  
  int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd1, "Error OPEN");
  int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd2, "Error OPEN");
   
  while (1) {
    int tot;
    int length;
    char line[MAX];
    
    sreadLine(STDIN_FILENO, line, &length, &tot, MAX);
    
    if (tot == 0) break;
    
    if (tot <= MAX && 'A' <= line[0] && line[0] <= 'Z') { // OU isupper(line[0])
      r = write(fd1, line, length);
      checkCond(r != length, "Error WRITE");
    } else if (tot <= MAX && 'a' <= line[0] && line[0] <= 'z') { // OU islower(line[0])
      r = write(fd2, line, length);
      checkCond(r != length, "Error WRITE");
    } 
  }
  
  r = close(fd1);
  checkNeg(r, "Error CLOSE");
  r = close(fd2);
  checkNeg(r, "Error CLOSE");
}
