context("test-create_epitopeome")

test_that("use", {
  fasta_filename <- system.file(
    "extdata", "proteome.fasta", package = "epitopeome"
  )
  epitopeome <- create_epitopeome(fasta_filename)
})
