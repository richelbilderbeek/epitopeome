context("test-create_epitopeome")

test_that("use", {
  fasta_filename <- system.file(
    "extdata", "proteome.fasta", package = "epitopeome"
  )
  tmhmm_filename <- tempfile(fileext = "txt")
  netmhc2pan_filename <- tempfile(fileext = ".csv")

  epitopeome <- create_epitopeome(
    fasta_filename,
    tmhmm_filename = tmhmm_filename,
    netmhc2pan_filename = netmhc2pan_filename
  )

  readLines(tmhmm_filename)
  readLines(netmhc2pan_filename)
})
