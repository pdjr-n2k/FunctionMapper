#include <FunctionMapper.h>

FunctionMapper::FunctionMapper(FunctionMap *functionMapArray, unsigned int size) {
  unsigned int fmaSize = 0;

  if (functionMapArray != 0) {
    while (functionMapArray[fmaSize].handler != 0) fmaSize++;
    if (size < fmaSize) size = fmaSize;
  } else {
    size = (size == 0)?10:size;
  }

  this->arraySize = size;
  this->functionMapArray = new FunctionMap[this->arraySize + 1];

  for (unsigned int i = 0; i < (this->arraySize + 1); i++) {
    this->functionMapArray[i].functionCode = (i < fmaSize)?functionMapArray[i].functionCode:0;
    this->functionMapArray[i].handler = (i < fmaSize)?functionMapArray[i].handler:0;
  }
}

bool FunctionMapper::addHandler(unsigned char functionCode, bool (*handler)(unsigned char, unsigned char)) {
  int slot = -1;
  for (unsigned int i = 0; i < this->arraySize; i++) {
    if (this->functionMapArray[i].handler == 0) slot = i;
  }
  if (slot != -1) {
    this->functionMapArray[slot].functionCode = functionCode;
    this->functionMapArray[slot].handler = handler;
  }
  return(slot != -1);
}

bool FunctionMapper::validateAddress(unsigned int functionCode) {
  bool retval = false;

  for (unsigned int i = 0; this->functionMapArray[i].handler != 0; i++) {
    if (this->functionMapArray[i].functionCode == functionCode) {
      retval = true;
      break;
    }
  }
  return(retval);
}

bool FunctionMapper::processValue(unsigned int functionCode, unsigned char value) {
  bool retval = false;

  for (unsigned int i = 0; this->functionMapArray[i].handler != 0; i++) {
    if (this->functionMapArray[i].functionCode == functionCode) {
      retval = this->functionMapArray[i].handler(functionCode, value);
      break;
    }
  }
  return(retval);
}
