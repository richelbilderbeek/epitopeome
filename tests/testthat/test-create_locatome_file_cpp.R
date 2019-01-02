context("test-create_locatome_file_cpp")

test_that("use", {

  testit::assert(tmhmm::is_tmhmm_installed())
  fasta_filename <- system.file(
    "extdata", "proteome.fasta", package = "epitopeome"
  )

  # Expect
  raw_text <- tmhmm::run_tmhmm(fasta_filename = fasta_filename)
  two_liner_text <- c(
    raw_text[1],
    paste0(raw_text[2:6], collapse = "")
  )
  expected_text <- stringr::str_to_lower(two_liner[2])

  # Created
  locatome_filename <- tempfile()
  create_locatome_file_cpp(
    fasta_filename = fasta_filename,
    locatome_filename = locatome_filename
  )
  created_text <- readLines(expected_text)

  expect_equal(created_text, expected_text)
})
