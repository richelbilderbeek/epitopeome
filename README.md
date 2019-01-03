# epitopeome

Branch|[![Travis CI logo](pics/TravisCI.png)](https://travis-ci.org)|[![Codecov logo](pics/Codecov.png)](https://www.codecov.io)
---|---|---
master|[![Build Status](https://travis-ci.org/richelbilderbeek/epitopeome.svg?branch=master)](https://travis-ci.org/richelbilderbeek/epitopeome)|[![codecov.io](https://codecov.io/github/richelbilderbeek/epitopeome/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/epitopeome/branch/master)
develop|[![Build Status](https://travis-ci.org/richelbilderbeek/epitopeome.svg?branch=develop)](https://travis-ci.org/richelbilderbeek/epitopeome)|[![codecov.io](https://codecov.io/github/richelbilderbeek/epitopeome/coverage.svg?branch=develop)](https://codecov.io/github/richelbilderbeek/epitopeome/branch/develop)

Create an 'epitopeome' from one or more protein sequences.

> Please note that TMHMM and NetMHCIIpan are intended for academic users only. 
> Other users are requested TMHMM and NetMHC2IIpan 
> Software Package Manager at software@cbs.dtu.dk

 * [YouTube video](https://youtu.be/AqT2JOjxnCU) or [download video](http://richelbilderbeek.nl/epitopeome.ogv)

`epitopeome` depends on:

 * [netmhc2pan](https://github.com/richelbilderbeek/netmhc2pan): 
   obtain MHC2 epitopes for a proteome
 * [tmhmm](https://github.com/richelbilderbeek/tmhmm):
   obtain the topology of a transmembrane protein

## Install

The `epitopeome` package depends on the `tmhmm` package, which needs
to be installed first:

```{r}
devtools::install_github("richelbilderbeek/tmhmm")
```

The `tmhmm` package relies on TMHMM that needs to be installed:

```{r}
tmhmm::install_tmhmm("http://www.cbs.dtu.dk/download/D3198788-0F1D-11E9-883C-84B3B9CD16B5/")
```

The URL can be obtained by requesting a download link at 
the [TMHMM](http://www.cbs.dtu.dk/services/TMHMM) website 
at [http://www.cbs.dtu.dk/services/TMHMM](http://www.cbs.dtu.dk/services/TMHMM).
As this URL expires after four hours, `tmhmm` cannot do this for you.

The installation of NetMHC2pan is checked, with the goal of giving
a helpful error message:

```{r}
tmhmm::check_tmhmm_installation()
```

Additionall, The `epitopeome` package depends on the `netmhc2pan` package, which needs
to be installed as well:

```{r}
devtools::install_github("richelbilderbeek/netmhc2pan")
```

The `netmhc2pan` package relies on NetMHCIIpan that needs to be installed:

```{r}
netmhc2pan::install_netmhc2pan("http://www.cbs.dtu.dk/download/33A6B0AC-0F2E-11E9-B4D1-8ABCB9CD16B5/")
```

The URL can be obtained by requesting a download link at
the [NetMHCIIpan](www.cbs.dtu.dk/services/NetMHCIIpan) website 
at [www.cbs.dtu.dk/services/NetMHCIIpan]www.cbs.dtu.dk/services/NetMHCIIpan).
As this URL expires after four hours, `netmhc2pan` cannot do this for you.

The installation of NetMHC2pan is checked, with the goal of giving
a helpful error message:

```{r}
netmhc2pan::check_netmhc2pan_installation()
```

Installing the `epitopeome` package:

```{r}
devtools::install_github("richelbilderbeek/epitopeome")
```

## Usage

We need a FASTA file to work on:

```{r}
fasta_filename <- system.file("extdata", "tmhmm.fasta", package = "tmhmm")
```

The FASTA file should contain the protein sequences of one or more
genes. Reading the file ...

```{r}
cat(readLines(fasta_filename), sep = "\n")
```

results in:

```
>5H2A_CRIGR you can have comments after the ID
MEILCEDNTSLSSIPNSLMQVDGDSGLYRNDFNSRDANSSDASNWTIDGENRTNLSFEGYLPPTCLSILHL
QEKNWSALLTAVVIILTIAGNILVIMAVSLEKKLQNATNYFLMSLAIADMLLGFLVMPVSMLTILYGYRWP
LPSKLCAVWIYLDVLFSTASIMHLCAISLDRYVAIQNPIHHSRFNSRTKAFLKIIAVWTISVGVSMPIPVF
GLQDDSKVFKQGSCLLADDNFVLIGSFVAFFIPLTIMVITYFLTIKSLQKEATLCVSDLSTRAKLASFSFL
PQSSLSSEKLFQRSIHREPGSYTGRRTMQSISNEQKACKVLGIVFFLFVVMWCPFFITNIMAVICKESCNE
HVIGALLNVFVWIGYLSSAVNPLVYTLFNKTYRSAFSRYIQCQYKENRKPLQLILVNTIPALAYKSSQLQA
GQNKDSKEDAEPTDNDCSMVTLGKQQSEETCTDNINTVNEKVSCV
```

Use `create_epitopeome` to obtain the epitopeome:

```{r}
epitopeome <- epitopeome::create_epitopeome(fasta_filename)
```

`epitopeome` will return an 'epitopeome': the location
of each amino acid:

Epitopeum|Location|Binds strongly to MHC2 allele 
---|---|---
'o'|Outside|No
'i'|Inside|No
'm'|Membrance|No
'O'|Outside|Yes
'I'|Inside|Yes
'M'|Membrance|Yes

Here is how it looks like:

```{r}
cat(epitopeome, sep = "\n")
```

```
>5H2A_CRIGR
oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooommmmmmmmmmmmmmmmmmmmmmmiiiiiiiIIIIIMMMMMMMMMMMMMMMMMMMMMMMOOOOoooooooooommmmmmmmmmmmmmmmmmmmMMMIIIIIIIIIIIIIIIIiiiimmmmmmmmmmmmmmmmmmmmmmmooooooooooooooooooommmmmmmmmmmmmmmMMMMMMMMIIIIIIIIIIIIiiiiiiiIIIIIIIIIIIIIIIIIIIIIiiiiiiiiiiiiiiiiiiiiiiiiiiiimmmmmmmmmmmmmmmmmmmmmmmooooooooommmmmmmMMMMMMMMMMMMMMMMIIIIIIIIIIIIIIIIIIIIIiiIIIIIIIIIIIIIIIIIIIIiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
```

## Dependencies

Package|Build status
---|---
`netmhc2pan`|[![Build Status](https://travis-ci.org/richelbilderbeek/netmhc2pan.svg?branch=master)](https://travis-ci.org/richelbilderbeek/netmhc2pan)
`tmhmm`|[![Build Status](https://travis-ci.org/richelbilderbeek/tmhmm.svg?branch=master)](https://travis-ci.org/richelbilderbeek/tmhmm)

## FAQ

### Under which operating systems does `epitopeome` work?

`epitopeome` can only work on the set of operating systems 
that both TMHMM and NetMHCIIpan work on. 
Therefore, `epitopeome` works under Linux only. 

Operating system|Supported by TMHMM|NetMHCIIpan|Supported by `epitopeome`
---|---|---|---
AIX|Y|N|N
IRIX32|Y|N|N
IRIX64|Y|N|N
Darwin|N|Y|N
Linux|Y|Y|Y
MacOS|N|N|N
OSF1|Y|N|N
SunOS|Y|N|N
Windows|N|N|N

