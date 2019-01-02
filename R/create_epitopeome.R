#' Create epitopeome indicating strong MHC2 binders
#' @inheritParams default_params_doc
#' @return the epitopeome as text
#' @examples
#'   fasta_filename <- system.file(
#'     "extdata", "proteome.fasta", package = "epitopeome"
#'   )
#'   epitopeome <- create_epitopeome(fasta_filename)
#'   testit::assert(length(epitopeome) == 2)
#'   testit::assert(epitopeome[1] == ">tr|I6WZ58|I6WZ58_MYCTU")
#'   testit::assert(stringr::str_length(epitopeome[2]) == 313)
#'   testit::assert(stringr::str_count(epitopeome[2], "i") == 39)
#'   testit::assert(stringr::str_count(epitopeome[2], "m") == 47)
#'   testit::assert(stringr::str_count(epitopeome[2], "o") == 163)
#'   testit::assert(stringr::str_count(epitopeome[2], "I") == 10)
#'   testit::assert(stringr::str_count(epitopeome[2], "M") == 37)
#'   testit::assert(stringr::str_count(epitopeome[2], "O") == 17)
#' @author Richel J.C. Bilderbeek
#' @export
create_epitopeome <- function(
  fasta_filename,
  alleles = "DRB1_0101",
  binding_strength_threshold = 0.05,
  tmhmm_filename = tempfile(fileext = "txt"),
  netmhc2pan_filename = tempfile(fileext = ".csv"),
  epitopeome_filename = tempfile(fileext = ".fasta")
) {
  testit::assert(file.exists(fasta_filename))
  testit::assert(tmhmm::is_tmhmm_installed())
  testit::assert(netmhc2pan::is_netmhc2pan_installed())
  testit::assert(all(alleles %in% netmhc2pan::get_netmhc2pan_alleles()))
  # TMHH
  locatome <- tmhmm::run_tmhmm(fasta_filename)
  writeLines(
    text = locatome,
    con = tmhmm_filename
  )
  # NetMHC2pan
  df_bindings <- netmhc2pan::run_netmhc2pan(
    fasta_filename = fasta_filename,
    alleles = alleles
  )
  df_strong_bindings <- df_bindings[
    df_bindings$Rank <= binding_strength_threshold,
  ]
  utils::write.csv(
    x = df_strong_bindings,
    file = netmhc2pan_filename,
    row.names = FALSE
  )
  create_epitopeome_file_cpp(
    tmhs_filename = tmhmm_filename,
    netmhc2pan_filename = netmhc2pan_filename,
    epitopeome_filename = epitopeome_filename
  )
  testit::assert(file.exists(epitopeome_filename))
  readLines(epitopeome_filename)
}
