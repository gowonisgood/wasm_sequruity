APPLICATION = wasm-example
# If no BOARD is defined in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

USEPKG += wamr

ifeq (,$(filter native native64,$(BOARD)))
CFLAGS += -DTHREAD_STACKSIZE_MAIN='(6 * 1024)'
endif
CFLAGS += -Wno-error=unused-function
export WAMR_CONFIG := $(abspath config.cmake)
FEATURES_REQUIRED += cpp


BLOBS += heap_overflow_large.wasm
BLOBS += stack_buffer_overflow.wasm
BLOBS += sanity_check_pure_c.wasm
BLOBS += global_overflow.wasm
BLOBS += deep_stack_uaf.wasm
BLOBS += huge_negative_hea_oob.wasm
BLOBS += invalid_free.wasm
BLOBS += stack_buffer_overflow_with_position.wasm
BLOBS += stack_frame_demangle.wasm
BLOBS += coverage.wasm
BLOBS += use_after_scope.wasm
BLOBS += alloca_overflow_partial.wasm
BLOBS += alloca_big_alignment.wasm 
BLOBS += alloca_overflow_right.wasm
BLOBS += alloca_underflow_left.wasm
BLOBS += atoi_strict.wasm
BLOBS += atol_strict.wasm
BLOBS += atoll_strict.wasm
BLOBS += calloc_overflow.wasm
BLOBS += deep_tail_call.wasm
BLOBS += double_free.wasm
BLOBS += frexp_interceptor.wasm
BLOBS += global_demangle.wasm
BLOBS += global_location.wasm
BLOBS += global_underflow.wasm
BLOBS += halt_on_error_1.wasm
BLOBS += heavy_uar_test.wasm
BLOBS += ignorelist.wasm
BLOBS += interception_failure_test.wasm
BLOBS += intra_object_overflow.wasm
#BLOBS += large_func_test.wasm
BLOBS += log_path_test.wasm
BLOBS += malloc_context_size.wasm
BLOBS += memcmp_strict_test.wasm
BLOBS += memcmp_test.wasm
BLOBS += partial_right.wasm
BLOBS += pass_object_byval.wasm
BLOBS += pass_struct_byval.wasm
BLOBS += poison_partial.wasm
BLOBS += printf_2.wasm
BLOBS += printf_3.wasm
BLOBS += printf_5.wasm
BLOBS += printf_m.wasm
BLOBS += vla_chrome_testcase.wasm
BLOBS += vla_condition_overflow.wasm
BLOBS += vla_loop_overflow.wasm
BLOBS += stack_oob_frames.wasm
BLOBS += strcat_strict.wasm
BLOBS += strcmp_strict.wasm
BLOBS += use_after_free_right.wasm
BLOBS += use_after_scope_loop_removed.wasm
BLOBS += strspn_strict.wasm
BLOBS += use_after_scope_dtor_order.wasm
BLOBS += use_after_scope_nodebug.wasm
BLOBS += strstr_strict.wasm
BLOBS += use_after_scope_goto.wasm
BLOBS += use_after_scope_temp2.wasm
BLOBS += suppressions_interceptor.wasm
BLOBS += use_after_scope_if.wasm
BLOBS += use_after_scope_temp.wasm
BLOBS += time_interceptor.wasm
BLOBS += use_after_scope_inlined.wasm
BLOBS += use_after_scope_types.wasm
BLOBS += use_after_conversion.wasm
BLOBS += use_after_scope_loop_bug.wasm
BLOBS += verbose_log_path_test.wasm
BLOBS += use_after_free.wasm
BLOBS += use_after_scope_loop.wasm

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1
.PHONY: update-wamr #what is this

all: update-wamr $(BLOBS)

heap_overflow_large.wasm: wasm_sample/heap_overflow_large.cpp wasm_sample/Makefile
	make -C wasm_sample heap_overflow_large.wasm
	mv wasm_sample/heap_overflow_large.wasm .

stack_buffer_overflow.wasm: wasm_sample/stack_buffer_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample stack_buffer_overflow.wasm
	mv wasm_sample/stack_buffer_overflow.wasm .

sanity_check_pure_c.wasm: wasm_sample/sanity_check_pure_c.c wasm_sample/Makefile
	make -C wasm_sample sanity_check_pure_c.wasm
	mv wasm_sample/sanity_check_pure_c.wasm .


global_overflow.wasm: wasm_sample/global_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample global_overflow.wasm
	mv wasm_sample/global_overflow.wasm .


deep_stack_uaf.wasm: wasm_sample/deep_stack_uaf.cpp wasm_sample/Makefile
	make -C wasm_sample deep_stack_uaf.wasm
	mv wasm_sample/deep_stack_uaf.wasm .

huge_negative_hea_oob.wasm: wasm_sample/huge_negative_hea_oob.cpp wasm_sample/Makefile
	make -C wasm_sample huge_negative_hea_oob.wasm
	mv wasm_sample/huge_negative_hea_oob.wasm .

invalid_free.wasm: wasm_sample/invalid_free.cpp wasm_sample/Makefile
	make -C wasm_sample invalid_free.wasm
	mv wasm_sample/invalid_free.wasm .

stack_buffer_overflow_with_position.wasm: wasm_sample/stack_buffer_overflow_with_position.cpp wasm_sample/Makefile
	make -C wasm_sample stack_buffer_overflow_with_position.wasm
	mv wasm_sample/stack_buffer_overflow_with_position.wasm .

stack_frame_demangle.wasm: wasm_sample/stack_frame_demangle.cpp wasm_sample/Makefile
	make -C wasm_sample stack_frame_demangle.wasm
	mv wasm_sample/stack_frame_demangle.wasm .

coverage.wasm: wasm_sample/coverage.cpp wasm_sample/Makefile
	make -C wasm_sample coverage.wasm
	mv wasm_sample/coverage.wasm .

use_after_scope.wasm: wasm_sample/use_after_scope.cpp wasm_sample/Makefile
	make -C wasm_sample use_after_scope.wasm
	mv wasm_sample/use_after_scope.wasm .

alloca_overflow_partial.wasm: wasm_sample/alloca_overflow_partial.cpp wasm_sample/Makefile
	make -C wasm_sample alloca_overflow_partial.wasm
	mv wasm_sample/alloca_overflow_partial.wasm .

alloca_big_alignment.wasm: wasm_sample/alloca_big_alignment.cpp wasm_sample/Makefile
	make -C wasm_sample alloca_big_alignment.wasm
	mv wasm_sample/alloca_big_alignment.wasm .

alloca_overflow_right.wasm: wasm_sample/alloca_overflow_right.cpp wasm_sample/Makefile
	make -C wasm_sample alloca_overflow_right.wasm
	mv wasm_sample/alloca_overflow_right.wasm .

alloca_underflow_left.wasm: wasm_sample/alloca_underflow_left.cpp wasm_sample/Makefile
	make -C wasm_sample alloca_underflow_left.wasm
	mv wasm_sample/alloca_underflow_left.wasm .

atoi_strict.wasm: wasm_sample/atoi_strict.c wasm_sample/Makefile
	make -C wasm_sample atoi_strict.wasm
	mv wasm_sample/atoi_strict.wasm .

atol_strict.wasm: wasm_sample/atol_strict.c wasm_sample/Makefile
	make -C wasm_sample atol_strict.wasm
	mv wasm_sample/atol_strict.wasm .

atoll_strict.wasm: wasm_sample/atoll_strict.c wasm_sample/Makefile
	make -C wasm_sample atoll_strict.wasm
	mv wasm_sample/atoll_strict.wasm .

calloc_overflow.wasm: wasm_sample/calloc_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample calloc_overflow.wasm
	mv wasm_sample/calloc_overflow.wasm .

deep_tail_call.wasm: wasm_sample/deep_tail_call.cpp wasm_sample/Makefile
	make -C wasm_sample deep_tail_call.wasm
	mv wasm_sample/deep_tail_call.wasm .

double_free.wasm: wasm_sample/double_free.cpp wasm_sample/Makefile
	make -C wasm_sample double_free.wasm
	mv wasm_sample/double_free.wasm .

frexp_interceptor.wasm: wasm_sample/frexp_interceptor.cpp wasm_sample/Makefile
	make -C wasm_sample frexp_interceptor.wasm
	mv wasm_sample/frexp_interceptor.wasm .

global_demangle.wasm: wasm_sample/global_demangle.cpp wasm_sample/Makefile
	make -C wasm_sample global_demangle.wasm
	mv wasm_sample/global_demangle.wasm .

global_location.wasm: wasm_sample/global_location.cpp wasm_sample/Makefile
	make -C wasm_sample global_location.wasm
	mv wasm_sample/global_location.wasm .

global_underflow.wasm: wasm_sample/global_underflow.cpp wasm_sample/Makefile
	make -C wasm_sample global_underflow.wasm
	mv wasm_sample/global_underflow.wasm .

halt_on_error_1.wasm: wasm_sample/halt_on_error_1.c wasm_sample/Makefile
	make -C wasm_sample halt_on_error_1.wasm
	mv wasm_sample/halt_on_error_1.wasm .

heavy_uar_test.wasm: wasm_sample/heavy_uar_test.cpp wasm_sample/Makefile
	make -C wasm_sample heavy_uar_test.wasm
	mv wasm_sample/heavy_uar_test.wasm .

ignorelist.wasm: wasm_sample/ignorelist.cpp wasm_sample/Makefile
	make -C wasm_sample ignorelist.wasm
	mv wasm_sample/ignorelist.wasm .

interception_failure_test.wasm: wasm_sample/interception_failure_test.cpp wasm_sample/Makefile
	make -C wasm_sample interception_failure_test.wasm
	mv wasm_sample/interception_failure_test.wasm .

intra_object_overflow.wasm: wasm_sample/intra_object_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample intra_object_overflow.wasm
	mv wasm_sample/intra_object_overflow.wasm .

#large_func_test.wasm: wasm_sample/large_func_test.cpp wasm_sample/Makefile
#	make -C wasm_sample large_func_test.wasm
#	mv wasm_sample/large_func_test.wasm .

log_path_test.wasm: wasm_sample/log_path_test.cpp wasm_sample/Makefile
	make -C wasm_sample log_path_test.wasm
	mv wasm_sample/log_path_test.wasm .

malloc_context_size.wasm: wasm_sample/malloc_context_size.cpp wasm_sample/Makefile
	make -C wasm_sample malloc_context_size.wasm
	mv wasm_sample/malloc_context_size.wasm .

memcmp_strict_test.wasm: wasm_sample/memcmp_strict_test.cpp wasm_sample/Makefile
	make -C wasm_sample memcmp_strict_test.wasm
	mv wasm_sample/memcmp_strict_test.wasm .

memcmp_test.wasm: wasm_sample/memcmp_test.cpp wasm_sample/Makefile
	make -C wasm_sample memcmp_test.wasm
	mv wasm_sample/memcmp_test.wasm .

partial_right.wasm: wasm_sample/partial_right.cpp wasm_sample/Makefile
	make -C wasm_sample partial_right.wasm
	mv wasm_sample/partial_right.wasm .

pass_object_byval.wasm: wasm_sample/pass_object_byval.cpp wasm_sample/Makefile
	make -C wasm_sample pass_object_byval.wasm
	mv wasm_sample/pass_object_byval.wasm .

pass_struct_byval.wasm: wasm_sample/pass_struct_byval.cpp wasm_sample/Makefile
	make -C wasm_sample pass_struct_byval.wasm
	mv wasm_sample/pass_struct_byval.wasm .

poison_partial.wasm: wasm_sample/poison_partial.cpp wasm_sample/Makefile
	make -C wasm_sample poison_partial.wasm
	mv wasm_sample/poison_partial.wasm .

printf_2.wasm: wasm_sample/printf_2.c wasm_sample/Makefile
	make -C wasm_sample printf_2.wasm
	mv wasm_sample/printf_2.wasm .

printf_3.wasm: wasm_sample/printf_3.c wasm_sample/Makefile
	make -C wasm_sample printf_3.wasm
	mv wasm_sample/printf_3.wasm .

printf_5.wasm: wasm_sample/printf_5.c wasm_sample/Makefile
	make -C wasm_sample printf_5.wasm
	mv wasm_sample/printf_5.wasm .

printf_m.wasm: wasm_sample/printf_m.c wasm_sample/Makefile
	make -C wasm_sample printf_m.wasm
	mv wasm_sample/printf_m.wasm .

vla_chrome_testcase.wasm: wasm_sample/vla_chrome_testcase.cpp wasm_sample/Makefile
	make -C wasm_sample vla_chrome_testcase.wasm
	mv wasm_sample/vla_chrome_testcase.wasm .

vla_condition_overflow.wasm: wasm_sample/vla_condition_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample vla_condition_overflow.wasm
	mv wasm_sample/vla_condition_overflow.wasm .

vla_loop_overflow.wasm: wasm_sample/vla_loop_overflow.cpp wasm_sample/Makefile
	make -C wasm_sample vla_loop_overflow.wasm
	mv wasm_sample/vla_loop_overflow.wasm .

stack_oob_frames.wasm: wasm_sample/stack_oob_frames.cpp wasm_sample/Makefile
	make -C wasm_sample stack_oob_frames.wasm
	mv wasm_sample/stack_oob_frames.wasm .

strcat_strict.wasm: wasm_sample/strcat_strict.c wasm_sample/Makefile
	make -C wasm_sample strcat_strict.wasm
	mv wasm_sample/strcat_strict.wasm .

# strcmp_strict.wasm
strcmp_strict.wasm: wasm_sample/strcmp_strict.c wasm_sample/Makefile
	@echo "Building strcmp_strict.wasm"
	make -C wasm_sample strcmp_strict.wasm
	mv wasm_sample/strcmp_strict.wasm .

# use_after_free_right.wasm
use_after_free_right.wasm: wasm_sample/use_after_free_right.cpp wasm_sample/Makefile
	@echo "Building use_after_free_right.wasm"
	make -C wasm_sample use_after_free_right.wasm
	mv wasm_sample/use_after_free_right.wasm .

# use_after_scope_loop_removed.wasm
use_after_scope_loop_removed.wasm: wasm_sample/use_after_scope_loop_removed.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_loop_removed.wasm"
	make -C wasm_sample use_after_scope_loop_removed.wasm
	mv wasm_sample/use_after_scope_loop_removed.wasm .

# strspn_strict.wasm
strspn_strict.wasm: wasm_sample/strspn_strict.c wasm_sample/Makefile
	@echo "Building strspn_strict.wasm"
	make -C wasm_sample strspn_strict.wasm
	mv wasm_sample/strspn_strict.wasm .

# use_after_scope_dtor_order.wasm
use_after_scope_dtor_order.wasm: wasm_sample/use_after_scope_dtor_order.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_dtor_order.wasm"
	make -C wasm_sample use_after_scope_dtor_order.wasm
	mv wasm_sample/use_after_scope_dtor_order.wasm .

# use_after_scope_nodebug.wasm
use_after_scope_nodebug.wasm: wasm_sample/use_after_scope_nodebug.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_nodebug.wasm"
	make -C wasm_sample use_after_scope_nodebug.wasm
	mv wasm_sample/use_after_scope_nodebug.wasm .

# strstr_strict.wasm
strstr_strict.wasm: wasm_sample/strstr_strict.c wasm_sample/Makefile
	@echo "Building strstr_strict.wasm"
	make -C wasm_sample strstr_strict.wasm
	mv wasm_sample/strstr_strict.wasm .

# use_after_scope_goto.wasm
use_after_scope_goto.wasm: wasm_sample/use_after_scope_goto.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_goto.wasm"
	make -C wasm_sample use_after_scope_goto.wasm
	mv wasm_sample/use_after_scope_goto.wasm .

# use_after_scope_temp2.wasm
use_after_scope_temp2.wasm: wasm_sample/use_after_scope_temp2.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_temp2.wasm"
	make -C wasm_sample use_after_scope_temp2.wasm
	mv wasm_sample/use_after_scope_temp2.wasm .

# suppressions_interceptor.wasm
suppressions_interceptor.wasm: wasm_sample/suppressions_interceptor.cpp wasm_sample/Makefile
	@echo "Building suppressions_interceptor.wasm"
	make -C wasm_sample suppressions_interceptor.wasm
	mv wasm_sample/suppressions_interceptor.wasm .

# use_after_scope_if.wasm
use_after_scope_if.wasm: wasm_sample/use_after_scope_if.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_if.wasm"
	make -C wasm_sample use_after_scope_if.wasm
	mv wasm_sample/use_after_scope_if.wasm .

# use_after_scope_temp.wasm
use_after_scope_temp.wasm: wasm_sample/use_after_scope_temp.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_temp.wasm"
	make -C wasm_sample use_after_scope_temp.wasm
	mv wasm_sample/use_after_scope_temp.wasm .

# time_interceptor.wasm
time_interceptor.wasm: wasm_sample/time_interceptor.cpp wasm_sample/Makefile
	@echo "Building time_interceptor.wasm"
	make -C wasm_sample time_interceptor.wasm
	mv wasm_sample/time_interceptor.wasm .

# use_after_scope_inlined.wasm
use_after_scope_inlined.wasm: wasm_sample/use_after_scope_inlined.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_inlined.wasm"
	make -C wasm_sample use_after_scope_inlined.wasm
	mv wasm_sample/use_after_scope_inlined.wasm .

# use_after_scope_types.wasm
use_after_scope_types.wasm: wasm_sample/use_after_scope_types.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_types.wasm"
	make -C wasm_sample use_after_scope_types.wasm
	mv wasm_sample/use_after_scope_types.wasm .

# use_after_conversion.wasm
use_after_conversion.wasm: wasm_sample/use_after_conversion.cpp wasm_sample/Makefile
	@echo "Building use_after_conversion.wasm"
	make -C wasm_sample use_after_conversion.wasm
	mv wasm_sample/use_after_conversion.wasm .

# use_after_scope_loop_bug.wasm
use_after_scope_loop_bug.wasm: wasm_sample/use_after_scope_loop_bug.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_loop_bug.wasm"
	make -C wasm_sample use_after_scope_loop_bug.wasm
	mv wasm_sample/use_after_scope_loop_bug.wasm .

# verbose_log_path_test.wasm
verbose_log_path_test.wasm: wasm_sample/verbose_log_path_test.cpp wasm_sample/Makefile
	@echo "Building verbose_log_path_test.wasm"
	make -C wasm_sample verbose_log_path_test.wasm
	mv wasm_sample/verbose_log_path_test.wasm .

# use_after_free.wasm
use_after_free.wasm: wasm_sample/use_after_free.cpp wasm_sample/Makefile
	@echo "Building use_after_free.wasm"
	make -C wasm_sample use_after_free.wasm
	mv wasm_sample/use_after_free.wasm .

# use_after_scope_loop.wasm
use_after_scope_loop.wasm: wasm_sample/use_after_scope_loop.cpp wasm_sample/Makefile
	@echo "Building use_after_scope_loop.wasm"
	make -C wasm_sample use_after_scope_loop.wasm
	mv wasm_sample/use_after_scope_loop.wasm .









#######################################################
# Load the rest of the usual RIOT make infrastructure #
#######################################################

include $(RIOTBASE)/Makefile.include
