#!/bin/bash
# Script to install epitopeome and its dependencies
# on the Peregrine computer cluster
#
# Usage:
#
# * To install master:
#
# sbatch 1_install_epitopeome.sh
#
# * To install a branch, e.g. develop:
#
# sbatch 1_install_epitopeome.sh develop
#
#SBATCH --time=1:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --mem=1G
#SBATCH --job-name=install_epitopeome
#SBATCH --output=install_epitopeome.log
module load GCCcore/4.9.3 
module load XZ/5.2.2-foss-2016a
module load R
module load Perl

branch=$1
if [ "$#" -ne 1 ]; then
  branch=master
fi


################################################################################
# netmhc2pan
################################################################################
echo "Installing netmhc2pan GitHub"
Rscript -e "devtools::install_github(\"richelbilderbeek/netmhc2pan\", ref = \"$branch\")" 

echo "Installing NetMHC2pan"
Rscript -e 'netmhc2pan::install_netmhc2pan()'

echo "NetMHC2pan binary installed:"
Rscript -e 'netmhc2pan::is_netmhc2pan_bin_installed()' 

echo "NetMHC2pan data installed:"
Rscript -e 'netmhc2pan::is_netmhc2pan_data_installed()'

echo "NetMHC2pan set up:"
Rscript -e 'netmhc2pan::is_netmhc2pan_set_up()'

echo "TCSH installed:"
Rscript -e 'netmhc2pan::is_tcsh_installed()'

echo "NetMHC2pan run:"
Rscript -e 'netmhc2pan::run_netmhc2pan(fasta_filename = system.file("extdata", "example.fasta", package = "netmhc2pan"))'

################################################################################
# tmhmm
################################################################################

echo "Installing TMHMM GitHub"
Rscript -e "devtools::install_github(\"richelbilderbeek/tmhmm\", ref = \"$branch\")" 

echo "Installing TMHMM"
Rscript -e 'tmhmm::install_tmhmm()'

echo "TMHMM binary installed:"
Rscript -e 'tmhmm::is_tmhmm_bin_installed()' 

echo "TMHMM set up:"
Rscript -e 'tmhmm::is_tmhmm_set_up()'

echo "TMHMM run:"
Rscript -e 'tmhmm::run_tmhmm(system.file("extdata", "tmhmm.fasta", package = "tmhmm"))'

################################################################################
# epitopeome
################################################################################

echo "Installing epitopeome GitHub"
Rscript -e "devtools::install_github(\"richelbilderbeek/epitopeome\", ref = \"$branch\")" 

echo "epitopeome run:"
Rscript -e 'epitopeome::create_epitopeome(system.file("extdata", "proteome.fasta", package = "epitopeome"))'
