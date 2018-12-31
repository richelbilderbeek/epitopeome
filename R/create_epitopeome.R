#' Create epitopeome indicating strong MHC2 binders
#' @inheritParams default_params_doc
#' @author Richel J.C. Bilderbeek
#' @export
create_epitopeome <- function(
  fasta_filename,
  alleles = "DRB1_0101",
  tmhmm_filename = tempfile(fileext = "txt"),
  netmhc2pan_filename = tempfile(fileext = ".csv")
) {
  # TMHH
  df_tmh <- tmhmm::run_tmhmm(fasta_filename)
  utils::write.csv(
    x = df_tmh,
    file = tmhmm_filename,
    row.names = FALSE
  )
  # NetMHC2pan
  df_bindings <- netmhc2pan::run_netmhc2pan(
    fasta_filename = fasta_filename,
    alleles = alleles
  )
  utils::write.csv(
    x = df_bindings,
    file = netmhc2pan_filename,
    row.names = FALSE
  )
  return()
  epitopeome::create_epitopeome_cpp(
    tmhs_filename = tmhmm_filename,
    netmhc2pan_filename = netmhc2pan_filename
  )
}
