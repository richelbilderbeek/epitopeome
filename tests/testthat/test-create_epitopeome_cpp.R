context("test-create_epitopeome_cpp")

test_that("use", {
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
  text <- readLines(epitopeome_filename)
  expect_equal(2, length(text))
  expect_equal(">tr|I6WZ58|I6WZ58_MYCTU", text[1])
  expect_equal("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiimmmmmmmmmmmmmmmmmmmmmmmooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooOOOOOOOOOOOOMMMMMMMMMMMMMMMMMMMMMMMIIIIIIIIIIiimmmmMMMMMMMMMMMMMMOOOOOooooooooommmmmmmmmmmmmmmmmmmmiiiii", text[2]) # nolint a epitopeome can be long
})
