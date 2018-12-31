context("test-create_epitopeome_cpp")

test_that("use", {
  skip("WIP")
  epitopeome_filename <- tempfile()

  create_epitopeome_file_cpp(
    tmhs_filename = system.file(
    "extdata", "tmhmm.txt", package = "epitopeome"
    ),
    netmhc2pan_filename = system.file(
    "extdata", "netmhc2pan.csv", package = "epitopeome"
    ),
    epitopeome_filename = epitopeome_filename
  )
  expect_true(file.exists(epitopeome_filename))
})
