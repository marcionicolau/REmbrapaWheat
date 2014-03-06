#include "auth.h"
  
struct pam_response *reply;  
  
//function used to get user input  
int function_conversation(int num_msg, const struct pam_message **msg, 
  struct pam_response **resp, 
	void *appdata_ptr)  
{  
    *resp = reply;  
        return PAM_SUCCESS;  
}  

int authenticate_system(const char *service, const char *username, const char *password)   
{  
    const struct pam_conv local_conversation = { function_conversation, NULL };  
    pam_handle_t *local_auth_handle = NULL; // this gets set by pam_start  
  
    int retval;  
    retval = pam_start(service, username, &local_conversation, &local_auth_handle);  
  
    if (retval != PAM_SUCCESS)  
    {  
            Rprintf("pam_start returned: %d\n ", retval);  
            return 0;  
    }  
#if __DEBUG__
    Rprintf("pam_start started.\n");
#endif  

    reply = (struct pam_response *)malloc(sizeof(struct pam_response));  

#if __DEBUG__
    Rprintf("User: %s, Password: %s.\n", username, strdup(password));
#endif

    reply[0].resp = strdup(password);  
    reply[0].resp_retcode = 0;  
    retval = pam_authenticate(local_auth_handle, 0);  
  
    if (retval != PAM_SUCCESS)  
    {  
#if __DEBUG__
            if (retval == PAM_AUTH_ERR)  
            {  
                Rprintf("Authentication failure.\n");  
            }  
            else  
            {  
                Rprintf("pam_authenticate returned %d\n", retval);  
            }
#endif
            return 0;  
    }  
#if __DEBUG__  
    Rprintf("Authenticated.\n");  
#endif
    retval = pam_end(local_auth_handle, retval);  
  
    if (retval != PAM_SUCCESS)  
    {  
            Rprintf("pam_end returned\n");  
            return 0;  
    }  
      
    return 1;  
}  

SEXP rew_auth(SEXP login, SEXP password){
   SEXP is_ok = PROTECT(allocVector(LGLSXP, 1)); 
   LOGICAL(is_ok)[0] = 0;
   
  const char *user = CHAR(asChar(login));
  const char *passwd = CHAR(asChar(password));
  
  if (authenticate_system("common-auth", user, passwd) == 1)  
    {  
#if __DEBUG__
        Rprintf("Authenticate with %s through system\n", user);  
#endif
        LOGICAL(is_ok)[0] = 1;
    }     
  UNPROTECT(1);
  return is_ok;
}
