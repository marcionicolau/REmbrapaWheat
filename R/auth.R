#' Auth user.
#'
#' Auth user to system using pam module
#'
#' This function is used to auth user to system using pam module.
#'
#' @export
rew_auth <- function(login, password) {
  .Call('auth', PACKAGE = 'REmbrapaWheat', login=as.character(login),
        password=as.character(password))
}