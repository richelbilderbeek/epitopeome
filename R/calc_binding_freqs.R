#' Calculate the binding frequencies
#' @param epitopeome an epitopeome
#' @return a map of binding distance to fraction of binds at that
#'   distance
#' @author Richel J.C. Bilderbeek
#' @export
calc_binding_freqs <- function(
  epitopeome
) {
  calc_binding_freqs_cpp(epitopeome)
}
