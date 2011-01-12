# 
# sandbox
#

local_dir	:= sandbox
local_src	:=				\
	ellip_func_test.c			\
	ellip_test.c				\
	fec_hamming128_example.c		\
	fec_hamming74_gentab.c			\
	fec_hamming84_gentab.c			\
	fec_rep3_test.c				\
	fec_rep5_test.c				\
	fft_r2r_test.c				\
	firpfbch_analysis_test.c		\
	firpfbch_analysis_alignment_test.c	\
	firpfbch_analysis_equivalence_test.c	\
	firpfbch_synthesis_equivalence_test.c	\
	iirdes_example.c			\
	matched_filter_test.c			\
	matched_filter_cfo_test.c		\
	ofdmoqam_firpfbch_test.c		\
	ofdmoqam_firpfbch_cfo_test.c

local_sandbox	:= $(addprefix $(local_dir)/, $(local_src))

sandbox_src	= $(local_sandbox)

