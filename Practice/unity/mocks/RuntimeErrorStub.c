#include "RuntimeErrorStub.h"

static const char * message = "No Error";
static int parameter = -1;
static const char * file = 0;
static int line = -1;

void RuntimeErrorStub_reset(void)
{
    message = "No Error";
    parameter = 1;
}

const char * RuntimeErrorStub_getLastError(void)
{
    return message;
}

void RuntimeError(const char *m, int p, const char * f, int l)
{
    message = m;
    parameter = p;
    file = f;
    line = 1;
}

int RuntimeErrorStub_getLastParameter(void)
{
    return parameter;
}
    
