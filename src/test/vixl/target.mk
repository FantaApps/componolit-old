TARGET = vixl_test

VIXL_DIR = $(call select_from_ports,vixl)/vixl/test
vpath %.cc $(VIXL_DIR)
INC_DIR += $(VIXL_DIR)

# MAP_ANONYMOUS in not available in Genode's libc
CC_OPT += -DMAP_ANONYMOUS=0

SRC_CC +=  \
	test-aborts.cc \
	test-code-buffer.cc \
	test-invalset.cc \
	test-runner.cc \
	test-utils.cc \
	test-api.cc \
	test-code-generation-scopes.cc \
	test-operands.cc \
	test-use-scratch-register-scope.cc

SRC_CC += \
aarch32/test-assembler-aarch32.cc \
aarch32/test-assembler-cond-rdlow-operand-imm8-t32.cc \
aarch32/test-assembler-cond-rdlow-operand-imm8-t32-in-it-block.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-imm3.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-imm3-in-it-block.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-imm8.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-imm8-in-it-block.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-zero.cc \
aarch32/test-assembler-cond-rdlow-rnlow-operand-immediate-t32-zero-in-it-block.cc \
aarch32/test-assembler-cond-rdlow-rnlow-rmlow-t32.cc \
aarch32/test-assembler-cond-rdlow-rnlow-rmlow-t32-in-it-block.cc \
aarch32/test-assembler-cond-rd-memop-immediate-512-a32.cc \
aarch32/test-assembler-cond-rd-memop-immediate-8192-a32.cc \
aarch32/test-assembler-cond-rd-memop-rs-a32.cc \
aarch32/test-assembler-cond-rd-memop-rs-shift-amount-1to31-a32.cc \
aarch32/test-assembler-cond-rd-memop-rs-shift-amount-1to32-a32.cc \
aarch32/test-assembler-cond-rd-operand-const-a32-cannot-use-pc.cc \
aarch32/test-assembler-cond-rd-operand-const-a32-can-use-pc.cc \
aarch32/test-assembler-cond-rd-operand-const-t32.cc \
aarch32/test-assembler-cond-rd-operand-imm16-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-a32.cc \
aarch32/test-assembler-cond-rd-operand-rn-ror-amount-a32.cc \
aarch32/test-assembler-cond-rd-operand-rn-ror-amount-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to31-a32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to31-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to31-t32-in-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to32-a32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to32-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-amount-1to32-t32-in-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-rs-a32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-rs-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-rs-t32-in-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-shift-rs-t32-narrow-out-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-t32.cc \
aarch32/test-assembler-cond-rd-operand-rn-t32-identical-low-registers-in-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-t32-in-it-block.cc \
aarch32/test-assembler-cond-rd-operand-rn-t32-low-registers-in-it-block.cc \
aarch32/test-assembler-cond-rd-pc-operand-imm12-t32.cc \
aarch32/test-assembler-cond-rd-pc-operand-imm8-t32.cc \
aarch32/test-assembler-cond-rd-rn-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-const-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-const-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-imm12-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-ror-amount-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-ror-amount-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-shift-amount-1to31-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-shift-amount-1to31-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-shift-amount-1to32-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-shift-amount-1to32-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-shift-rs-a32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32-all-low-in-it-block.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32-all-low-rd-is-rn-in-it-block.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32-rd-is-rn-in-it-block.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32-rd-is-rn-is-sp-in-it-block.cc \
aarch32/test-assembler-cond-rd-rn-operand-rm-t32-rn-is-sp-in-it-block.cc \
aarch32/test-assembler-cond-rd-rn-rm-a32.cc \
aarch32/test-assembler-cond-rd-rn-rm-t32.cc \
aarch32/test-assembler-cond-rd-rn-t32.cc \
aarch32/test-assembler-cond-rd-sp-operand-imm8-t32.cc \
aarch32/test-assembler-cond-sp-sp-operand-imm7-t32.cc \
aarch32/test-assembler-rd-rn-rm-a32.cc \
aarch32/test-assembler-rd-rn-rm-t32.cc \
aarch32/test-disasm-a32.cc \
aarch32/test-macro-assembler-cond-rd-rn-a32.cc \
aarch32/test-macro-assembler-cond-rd-rn-pc-a32.cc \
aarch32/test-macro-assembler-cond-rd-rn-t32.cc \
aarch32/test-simulator-cond-rdlow-operand-imm8-t32.cc \
aarch32/test-simulator-cond-rdlow-rnlow-operand-immediate-t32.cc \
aarch32/test-simulator-cond-rdlow-rnlow-rmlow-t32.cc \
aarch32/test-simulator-cond-rd-memop-immediate-512-a32.cc \
aarch32/test-simulator-cond-rd-memop-immediate-8192-a32.cc \
aarch32/test-simulator-cond-rd-memop-rs-a32.cc \
aarch32/test-simulator-cond-rd-memop-rs-shift-amount-1to31-a32.cc \
aarch32/test-simulator-cond-rd-memop-rs-shift-amount-1to32-a32.cc \
aarch32/test-simulator-cond-rd-operand-const-a32.cc \
aarch32/test-simulator-cond-rd-operand-const-t32.cc \
aarch32/test-simulator-cond-rd-operand-imm16-t32.cc \
aarch32/test-simulator-cond-rd-operand-rn-a32.cc \
aarch32/test-simulator-cond-rd-operand-rn-ror-amount-a32.cc \
aarch32/test-simulator-cond-rd-operand-rn-ror-amount-t32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-amount-1to31-a32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-amount-1to31-t32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-amount-1to32-a32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-amount-1to32-t32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-rs-a32.cc \
aarch32/test-simulator-cond-rd-operand-rn-shift-rs-t32.cc \
aarch32/test-simulator-cond-rd-operand-rn-t32.cc \
aarch32/test-simulator-cond-rd-rn-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-const-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-const-t32.cc \
aarch32/test-simulator-cond-rd-rn-operand-imm12-t32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-ror-amount-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-ror-amount-t32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-shift-amount-1to31-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-shift-amount-1to31-t32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-shift-amount-1to32-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-shift-rs-a32.cc \
aarch32/test-simulator-cond-rd-rn-operand-rm-t32.cc \
aarch32/test-simulator-cond-rd-rn-rm-a32.cc \
aarch32/test-simulator-cond-rd-rn-rm-a32-ge.cc \
aarch32/test-simulator-cond-rd-rn-rm-a32-q.cc \
aarch32/test-simulator-cond-rd-rn-rm-a32-sel.cc \
aarch32/test-simulator-cond-rd-rn-rm-t32.cc \
aarch32/test-simulator-cond-rd-rn-rm-t32-ge.cc \
aarch32/test-simulator-cond-rd-rn-rm-t32-q.cc \
aarch32/test-simulator-cond-rd-rn-rm-t32-sel.cc \
aarch32/test-simulator-cond-rd-rn-t32.cc \
aarch32/test-simulator-rd-rn-rm-a32.cc \
aarch32/test-simulator-rd-rn-rm-t32.cc \
aarch32/test-utils-aarch32.cc

SRC_CC +=  \
	aarch64/test-abi.cc \
	aarch64/test-disasm-aarch64.cc \
	aarch64/test-simulator-aarch64.cc \
	aarch64/test-utils-aarch64.cc \
	aarch64/test-assembler-aarch64.cc \
	aarch64/test-fuzz-aarch64.cc \
	aarch64/test-trace-aarch64.cc

LIBS += stdcxx libargv vixl

CC_CXX_WARN_STRICT =
