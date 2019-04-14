context("test-calc_binding_freqs")

test_that("use", {

  epitopeome <- c(
    ">name",
    "imo"
  )
  expect_silent(
    calc_binding_freqs(epitopeome)
  )
})
