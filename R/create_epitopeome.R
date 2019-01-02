#' Create epitopeome indicating strong MHC2 binders
#' @inheritParams default_params_doc
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
  readLines(tmhmm_filename)
  # NetMHC2pan
  df_bindings <- netmhc2pan::run_netmhc2pan(
    fasta_filename = fasta_filename,
    alleles = alleles
  )
  testit::assert(!is.character(df_bindings$Pos))
  df_strong_bindings <- df_bindings[
    df_bindings$Rank <= binding_strength_threshold,
  ]
  utils::write.csv(
    x = df_strong_bindings,
    file = netmhc2pan_filename,
    row.names = FALSE
  )
  head(read.csv(netmhc2pan_filename))
  create_epitopeome_file_cpp(
    tmhs_filename = tmhmm_filename,
    netmhc2pan_filename = netmhc2pan_filename,
    epitopeome_filename = epitopeome_filename
  )
  testit::assert(file.exists(epitopeome_filename))
  readLines(epitopeome_filename)
}
