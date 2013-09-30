
#ifndef RUNTIME_ERROR_STUB_H
#define RUNTIME_ERROR_STUB_H

void RuntimeErrorStub_reset(void);
const char * RuntimeErrorStub_getLastError(void);
int RuntimeErrorStub_getLastParameter(void);

#endif
