context("test-create_epitopeome")

test_that("use", {

  testit::assert(tmhmm::is_tmhmm_installed())
  testit::assert(netmhc2pan::is_netmhc2pan_installed())

  fasta_filename <- system.file(
    "extdata", "proteome.fasta", package = "epitopeome"
  )
  tmhmm_filename <- tempfile(fileext = "txt")
  netmhc2pan_filename <- tempfile(fileext = ".csv")
  epitopeome_filename <- tempfile(fileext = ".fasta")
  binding_strength_threshold <- 5.0
  alleles <- "DRB1_0101"

  epitopeome <- create_epitopeome(
    fasta_filename = fasta_filename,
    alleles = alleles,
    binding_strength_threshold = binding_strength_threshold,
    tmhmm_filename = tmhmm_filename,
    netmhc2pan_filename = netmhc2pan_filename,
    epitopeome_filename = epitopeome_filename
  )
  expect_equal(2, length(epitopeome))
  expect_equal(epitopeome[1], ">tr|I6WZ58|I6WZ58_MYCTU")
  expect_equal(epitopeome[2], "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiimmmmmmmmmmmmmmmmmmmmmmmooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMMMIIIIIIIIIIiimmmmMMMMMMMMMMMMMMOOOOOooooooooommmmmmmmmmmmmmmmmmmmiiiii") # nolint indeed a long line
})
