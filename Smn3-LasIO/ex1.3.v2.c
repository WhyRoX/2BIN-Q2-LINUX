#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
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
// READ FUNCTIONS
//*****************************************************************************//

typedef struct {
  int idx;
  int size;
  char buffer[MAX];
} ReaderState;

void readBlock(ReaderState *state) {
  if (state->size != 0 && state->idx == state->size) {
    state->size = read(0, state->buffer, MAX);
    checkNeg(state->size, "Error READ");
    state->idx = 0;
  }
}

bool eof(ReaderState *state) {
  readBlock(state);
  return state->size == 0;
}

char readChar(ReaderState *state) {
  char res = state->buffer[state->idx];
  state->idx++;
  return res;
}

/**
 * Reads a line from the input managed by the given ReaderState and stores it in the output ReaderState.
 * PRE: inputState: pointer to a ReaderState structure containing the current read state
 *      outputState: pointer to a ReaderState structure to store the read line
 * POST: a string of at most outputState->idx (<=MAX) characters has been read from the input
 *       and placed in outputState->buffer (including '\n' if present); if '\n' is not among the MAX read characters,
 *       the buffer is emptied and outputState->size indicates the number of read characters
 */
void sreadLine(ReaderState *inputState, ReaderState *outputState) {
  outputState->idx = 0;
  outputState->size = 0;

  bool eol = false;
  while(!eof(inputState) && !eol) {
    char current = readChar(inputState);
    eol = current == '\n';
    outputState->size++;

    if (outputState->idx < MAX) {
      outputState->buffer[outputState->idx] = current;
      outputState->idx++;
    }
  }
}

//*****************************************************************************//
// MAIN
//*****************************************************************************//

int main (int argc, char *argv[]) {

  checkUsage(argc, argv);
  int r;

  int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd1, "Error OPEN");
  int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd2, "Error OPEN");

  ReaderState inputState = {-1, -1, ""};
  ReaderState outputState;

  while(!eof(&inputState)) {
    sreadLine(&inputState, &outputState);

    if (outputState.size <= MAX && isupper(outputState.buffer[0])) { // OU 'A' <= line[0] && line[0] <= 'Z'
      r = write(fd1, outputState.buffer, outputState.idx);
      checkCond(r != outputState.idx, "Error WRITE");
    } else if (outputState.size <= MAX && islower(outputState.buffer[0])) { // OU 'a' <= line[0] && line[0] <= 'z'
      r = write(fd2, outputState.buffer, outputState.idx);
      checkCond(r != outputState.idx, "Error WRITE");
    }
  }

  r = close(fd1);
  checkNeg(r, "Error CLOSE");
  r = close(fd2);
  checkNeg(r, "Error CLOSE");
}
