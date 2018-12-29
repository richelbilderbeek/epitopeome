// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// create_epitopeome_cpp
std::map<std::string, std::string> create_epitopeome_cpp(const std::string& tmhs_filename, const std::string& netmhc2pan_filename);
RcppExport SEXP _epitopeome_create_epitopeome_cpp(SEXP tmhs_filenameSEXP, SEXP netmhc2pan_filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type tmhs_filename(tmhs_filenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type netmhc2pan_filename(netmhc2pan_filenameSEXP);
    rcpp_result_gen = Rcpp::wrap(create_epitopeome_cpp(tmhs_filename, netmhc2pan_filename));
    return rcpp_result_gen;
END_RCPP
}
// create_epitopeome_file_cpp
void create_epitopeome_file_cpp(const std::string& tmhs_filename, const std::string& netmhc2pan_filename, const std::string& epitopeome_filename);
RcppExport SEXP _epitopeome_create_epitopeome_file_cpp(SEXP tmhs_filenameSEXP, SEXP netmhc2pan_filenameSEXP, SEXP epitopeome_filenameSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type tmhs_filename(tmhs_filenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type netmhc2pan_filename(netmhc2pan_filenameSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type epitopeome_filename(epitopeome_filenameSEXP);
    create_epitopeome_file_cpp(tmhs_filename, netmhc2pan_filename, epitopeome_filename);
    return R_NilValue;
END_RCPP
}
// create_locatome_cpp
std::map<std::string, std::string> create_locatome_cpp(const std::string& tmhs_filename);
RcppExport SEXP _epitopeome_create_locatome_cpp(SEXP tmhs_filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type tmhs_filename(tmhs_filenameSEXP);
    rcpp_result_gen = Rcpp::wrap(create_locatome_cpp(tmhs_filename));
    return rcpp_result_gen;
END_RCPP
}
// split_str
std::vector<std::string> split_str(const std::string& input, const char seperator);
RcppExport SEXP _epitopeome_split_str(SEXP inputSEXP, SEXP seperatorSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type input(inputSEXP);
    Rcpp::traits::input_parameter< const char >::type seperator(seperatorSEXP);
    rcpp_result_gen = Rcpp::wrap(split_str(input, seperator));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_epitopeome_create_epitopeome_cpp", (DL_FUNC) &_epitopeome_create_epitopeome_cpp, 2},
    {"_epitopeome_create_epitopeome_file_cpp", (DL_FUNC) &_epitopeome_create_epitopeome_file_cpp, 3},
    {"_epitopeome_create_locatome_cpp", (DL_FUNC) &_epitopeome_create_locatome_cpp, 1},
    {"_epitopeome_split_str", (DL_FUNC) &_epitopeome_split_str, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_epitopeome(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
