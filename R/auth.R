#' Auth user.
#'
#' Auth user to system using pam module
#'
#' This function is used to auth user to system using pam module.
#' 
#' @param login Login user to auth.
#' @param password Password to auth user in the system.
#'
#' @useDynLib REmbrapaWheat
#' @export
auth <- function(login, password) {
  .Call('rew_auth', PACKAGE = 'REmbrapaWheat', login=as.character(login),
        password=as.character(password))
}