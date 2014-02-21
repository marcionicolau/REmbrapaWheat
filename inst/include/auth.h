#ifndef __AUTH_H_
#define __AUTH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <R.h>
#include <Rdefines.h>

//#include <stdio.h>  
#include <security/pam_appl.h>  
//#include <unistd.h>  
//#include <stdlib.h>  
//#include <string.h>  

int function_conversation(int, const struct pam_message **, struct pam_response **, void *);
int authenticate_system(const char *, const char *, const char *);
  

SEXP auth(const char *, const char *);

#ifdef __cplusplus
}
#endif

#endif /* __AUTH_H_ */