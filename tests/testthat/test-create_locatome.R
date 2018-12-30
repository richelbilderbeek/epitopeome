context("test-create_locatome")

test_that("use", {
  if (!tmhmm::is_tmhmm_installed()) return()
  skip("WIP")
  fasta_filename <- system.file(
    "extdata", "proteome.fasta", package = "epitopeome"
  )
  raw <- tmhmm::run_tmhmm(
    fasta_filename = fasta_filename,
    folder_name = tmhmm::get_default_tmhmm_folder()
  )
  two_liner <- c(
    raw[1],
    paste0(raw[2:6], collapse = "")
  )
  expected <- stringr::str_to_lower(two_liner[2])
  created <- create_locatome(fasta_filename)
  expect_equal(created, expected)
})
