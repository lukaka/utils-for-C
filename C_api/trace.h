#ifndef __TRACE_H_
#define __TRACE_H_

#define TRACE_ON	1

void TraceERR(int numArgs, const char *fmt, ...);
void TraceWARN(int numArgs, const char *fmt, ...);
void TraceDBG(int numArgs, const char *fmt, ...);

#endif