#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define BUFFERSIZE 10
#define FILENAME "test"

ssize_t writeSOut(char *msg, int l);

int main(int argc, char **argv)
{
  char bufRd[BUFFERSIZE];

  char *msg = "Enter text lines (Ctrl-D to terminate):\n";
  int len = strlen(msg);
  int nbCharWr = write(1, msg, len);

  checkCond(nbCharWr != len, "Error writing on stdout");

  ssize_t rd = read(0, bufRd, BUFFERSIZE);
  while (rd > 0)
  {

    nbCharWr = write(1, bufRd, rd);
    checkCond(nbCharWr != rd, "Error writing file");
    rd = read(0, bufRd, BUFFERSIZE);
  }
  checkNeg(rd, "Error reading stdin");
}
