#sometimes there might not be a wasm-ld (Ubuntu:focal)
#lets check if we can find a specific version

#this is a kind of crazy which from
#https://www.gnu.org/software/make/manual/html_node/Call-Function.html#Call-Function
#see https://github.com/RIOT-OS/RIOT/pull/16806 and /16807 and /16776 for why
search_fn = $(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))

ifneq ($(call search_fn,wasm-ld),)
  WASM-LD ?= wasm-ld
  else
    ifneq ($(call search_fn,wasm-ld-11),)
    LLVM_VERSION := 11
    else
      ifneq ($(call search_fn,wasm-ld-10),)
      LLVM_VERSION := 10
      else
        ifneq ($(call search_fn,wasm-ld-9),)
        LLVM_VERSION := 9
        else
          ifneq ($(call search_fn,wasm-ld-8),)
          LLVM_VERSION := 8
          endif
      endif
    endif
  endif
endif

ifneq ($(LLVM_VERSION),)
  CLANG ?= clang-$(LLVM_VERSION)
  CLANGPP ?= clang++-$(LLVM_VERSION)
  WASM-LD ?= wasm-ld-$(LLVM_VERSION)
else
  CLANG ?= clang
  CLANGPP ?= clang++
endif

ifeq ($(WASM-LD),)
  WASM-LD ?= echo "!! NO wasm-ld(-VERSION) found !!"; false
  COPY_HELLO := YES
endif

LINK_FLAGS := -z stack-size=4096 \
		--export main \
		--export=__heap_base \
		--export=__data_end \
		--allow-undefined \
		--strip-all \
		--export-dynamic \
		-error-limit=0 \
		--lto-O0 \
		-O0 \
		--gc-sections\
		--initial-memory=65536 \
		--no-entry \
		-L/home/cha/wasi-sdk-12.0/share/wasi-sysroot/lib/wasm32-wasi -lwasi-emulated-signal \
		#

# --initial-memory may only be set in 64kB steps (pagesize of WASM)
# even though this one page is 64kB
#	- data starts at 0, (1024 is chosen by lld)
#	- stack starts at 4kB growing down
#	- heap at 4kB growing up (see stack-size option)
#	-> memory can be smaller than first page
# without stack-size option stack will start at 64kB
#	-> heap needs a second page
# wasm-ld 8 and 11 do not need --initial-memory=64kB

COMPILE_FLAGS := -Wall \
		--target=wasm32-wasi \
		-emit-llvm \
		-Os \
		-flto \
		-fvisibility=hidden \
		-ffunction-sections \
		-fdata-sections \
		--sysroot=/home/cha/wasi-sdk-12.0/share/wasi-sysroot \
                -I/home/cha/wasi-sdk-12.0/share/wasi-sysroot/include/c++/v1 \
		-I/home/cha/wasi-sdk-12.0/share/wasi-sysroot/include \
		-Wno-error=unused-function \


#one might consider adding these
#		-nostartfiles \
#		--nostdlib \
#		--nostdinc \
#		-std=c++14 \

%.show: %.wasm
	wasm2wat $<

%.wasm: %.o Makefile
	$(WASM-LD) -o $@ $(LINK_FLAGS) $<


%.o: %.cpp Makefile FORCE
	$(CLANGPP) \
		-c \
		$(COMPILE_FLAGS) \
		-o $@ \
		$<

%.o: %.c Makefile FORCE
	$(CLANG)\
		-c \
		$(COMPILE_FLAGS) \
		-o $@ \
		$<

%.wat: %.wasm Makefile
	wasm2wat -o $@ $<

heap_overflow_large.wasm:

ifeq ($(COPY_HELLO),YES)
heap_overflow_large.wasm: heap_overflow_large.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying heap_overflow_large.wasm !! "
	cp heap_overflow_large_prebuild.wasm heap_overflow_large.wasm
else
heap_overflow_large_prebuild.wasm: heap_overflow_large.wasm
	cp heap_overflow_large.wasm heap_overflow_large_prebuild.wasm
endif




stack_buffer_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
stack_buffer_overflow.wasm: stack_buffer_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying stack_buffer_overflow_prebuild.wasm !! "
	cp stack_buffer_overflow_prebuild.wasm stack_buffer_overflow.wasm
else
stack_buffer_overflow_prebuild.wasm: stack_buffer_overflow.wasm
	cp stack_buffer_overflow.wasm stack_buffer_overflow_prebuild.wasm
endif

sanity_check_pure_c.wasm:

ifeq ($(COPY_HELLO),YES)
sanity_check_pure_c.wasm: sanity_check_pure_c_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying sanity_check_pure_c_prebuild.wasm !! "
	cp sanity_check_pure_c_prebuild.wasm sanity_check_pure_c.wasm
else
sanity_check_pure_c_prebuild.wasm: stack_buffer_overflow.wasm
	cp sanity_check_pure_c.wasm sanity_check_pure_c_prebuild.wasm
endif

global_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
global_overflow.wasm: global_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying global_overflow_prebuild.wasm !! "
	cp global_overflow_prebuild.wasm global_overflow.wasm
else
global_overflow_prebuild.wasm: global_overflow.wasm
	cp global_overflow.wasm global_overflow_prebuild.wasm
endif

deep_stack_uaf.wasm:
# deep_stack_uaf.wasm rules
ifeq ($(COPY_HELLO),YES)
deep_stack_uaf.wasm: deep_stack_uaf_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying deep_stack_uaf_prebuild.wasm !!"
	cp deep_stack_uaf_prebuild.wasm deep_stack_uaf.wasm
else
deep_stack_uaf_prebuild.wasm: deep_stack_uaf.wasm
	cp deep_stack_uaf.wasm deep_stack_uaf_prebuild.wasm
endif

huge_negative_hea_oob.wasm:
# huge_negative_hea_oob.wasm rules
ifeq ($(COPY_HELLO),YES)
huge_negative_hea_oob.wasm: huge_negative_hea_oob_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying huge_negative_hea_oob_prebuild.wasm !!"
	cp huge_negative_hea_oob_prebuild.wasm huge_negative_hea_oob.wasm
else
huge_negative_hea_oob_prebuild.wasm: huge_negative_hea_oob.wasm
	cp huge_negative_hea_oob.wasm huge_negative_hea_oob_prebuild.wasm
endif

invalid_free.wasm: 
# invalid_free.wasm rules
ifeq ($(COPY_HELLO),YES)
invalid_free.wasm: invalid_free_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying invalid_free_prebuild.wasm !!"
	cp invalid_free_prebuild.wasm invalid_free.wasm
else
invalid_free_prebuild.wasm: invalid_free.wasm
	cp invalid_free.wasm invalid_free_prebuild.wasm
endif

stack_buffer_overflow_with_position.wasm:
# stack_buffer_overflow_with_position.wasm rules
ifeq ($(COPY_HELLO),YES)
stack_buffer_overflow_with_position.wasm: stack_buffer_overflow_with_position_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying stack_buffer_overflow_with_position_prebuild.wasm !!"
	cp stack_buffer_overflow_with_position_prebuild.wasm stack_buffer_overflow_with_position.wasm
else
stack_buffer_overflow_with_position_prebuild.wasm: stack_buffer_overflow_with_position.wasm
	cp stack_buffer_overflow_with_position.wasm stack_buffer_overflow_with_position_prebuild.wasm
endif

stack_frame_demangle.wasm:
# stack_frame_demangle.wasm rules
ifeq ($(COPY_HELLO),YES)
stack_frame_demangle.wasm: stack_frame_demangle_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying stack_frame_demangle_prebuild.wasm !!"
	cp stack_frame_demangle_prebuild.wasm stack_frame_demangle.wasm
else
stack_frame_demangle_prebuild.wasm: stack_frame_demangle.wasm
	cp stack_frame_demangle.wasm stack_frame_demangle_prebuild.wasm
endif

coverage.cpp:

ifeq ($(COPY_HELLO),YES)
coverage.wasm: coverage_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying coverage_prebuild.wasm !!"
	cp coverage_prebuild.wasm coverage.wasm
else
coverage_prebuild.wasm: coverage.wasm
	cp coverage.wasm coverage_prebuild.wasm
endif

use_after_scope.cpp:

ifeq ($(COPY_HELLO),YES)
use_after_scope.wasm: use_after_scope_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_prebuild.wasm !!"
	cp use_after_scope_prebuild.wasm use_after_scope.wasm
else
use_after_scope_prebuild.wasm: use_after_scope.wasm
	cp use_after_scope.wasm use_after_scope_prebuild.wasm
endif


alloca_overflow_partial.cpp:

ifeq ($(COPY_HELLO),YES)
alloca_overflow_partial.wasm: alloca_overflow_partial_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying alloca_overflow_partial_prebuild.wasm !!"
	cp alloca_overflow_partial_prebuild.wasm alloca_overflow_partial.wasm
else
alloca_overflow_partial_prebuild.wasm: alloca_overflow_partial.wasm
	cp alloca_overflow_partial.wasm alloca_overflow_partial_prebuild.wasm
endif

alloca_big_alignment.cpp:

ifeq ($(COPY_HELLO),YES)
alloca_big_alignment.wasm: alloca_big_alignment_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying alloca_big_alignment_prebuild.wasm !!"
	cp alloca_big_alignment_prebuild.wasm alloca_big_alignment.wasm
else
alloca_big_alignment_prebuild.wasm: alloca_big_alignment.wasm
	cp alloca_big_alignment.wasm alloca_big_alignment_prebuild.wasm
endif

alloca_overflow_right.wasm:

ifeq ($(COPY_HELLO),YES)
alloca_overflow_right.wasm: alloca_overflow_right_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying alloca_overflow_right_prebuild.wasm !!"
	cp alloca_overflow_right_prebuild.wasm alloca_overflow_right.wasm
else
alloca_overflow_right_prebuild.wasm: alloca_overflow_right.wasm
	cp alloca_overflow_right.wasm alloca_overflow_right_prebuild.wasm
endif


alloca_underflow_left.wasm:

ifeq ($(COPY_HELLO),YES)
alloca_underflow_left.wasm: alloca_underflow_left_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying alloca_underflow_left_prebuild.wasm !!"
	cp alloca_underflow_left_prebuild.wasm alloca_underflow_left.wasm
else
alloca_underflow_left_prebuild.wasm: alloca_underflow_left.wasm
	cp alloca_underflow_left.wasm alloca_underflow_left_prebuild.wasm
endif


atoi_strict.wasm:

ifeq ($(COPY_HELLO),YES)
atoi_strict.wasm: atoi_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying atoi_strict_prebuild.wasm !!"
	cp atoi_strict_prebuild.wasm atoi_strict.wasm
else
atoi_strict_prebuild.wasm: atoi_strict.wasm
	cp atoi_strict.wasm atoi_strict_prebuild.wasm
endif

atol_strict.wasm:

ifeq ($(COPY_HELLO),YES)
atol_strict.wasm: atol_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying atol_strict_prebuild.wasm !!"
	cp atol_strict_prebuild.wasm atol_strict.wasm
else
atol_strict_prebuild.wasm: atol_strict.wasm
	cp atol_strict.wasm atol_strict_prebuild.wasm
endif

atoll_strict.wasm:

ifeq ($(COPY_HELLO),YES)
atoll_strict.wasm: atoll_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying atoll_strict_prebuild.wasm !!"
	cp atoll_strict_prebuild.wasm atoll_strict.wasm
else
atoll_strict_prebuild.wasm: atoll_strict.wasm
	cp atoll_strict.wasm atoll_strict_prebuild.wasm
endif

calloc_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
calloc_overflow.wasm: calloc_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying calloc_overflow_prebuild.wasm !!"
	cp calloc_overflow_prebuild.wasm calloc_overflow.wasm
else
calloc_overflow_prebuild.wasm: calloc_overflow.wasm
	cp calloc_overflow.wasm calloc_overflow_prebuild.wasm
endif

deep_tail_call.wasm:

ifeq ($(COPY_HELLO),YES)
deep_tail_call.wasm: deep_tail_call_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying deep_tail_call_prebuild.wasm !!"
	cp deep_tail_call_prebuild.wasm deep_tail_call.wasm
else
deep_tail_call_prebuild.wasm: deep_tail_call.wasm
	cp deep_tail_call.wasm deep_tail_call_prebuild.wasm
endif

double_free.wasm:

ifeq ($(COPY_HELLO),YES)
double_free.wasm: double_free_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying double_free_prebuild.wasm !!"
	cp double_free_prebuild.wasm double_free.wasm
else
double_free_prebuild.wasm: double_free.wasm
	cp double_free.wasm double_free_prebuild.wasm
endif

frexp_interceptor.wasm:

ifeq ($(COPY_HELLO),YES)
frexp_interceptor.wasm: frexp_interceptor_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying frexp_interceptor_prebuild.wasm !!"
	cp frexp_interceptor_prebuild.wasm frexp_interceptor.wasm
else
frexp_interceptor_prebuild.wasm: frexp_interceptor.wasm
	cp frexp_interceptor.wasm frexp_interceptor_prebuild.wasm
endif

global_demangle.wasm:

ifeq ($(COPY_HELLO),YES)
global_demangle.wasm: global_demangle_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying global_demangle_prebuild.wasm !!"
	cp global_demangle_prebuild.wasm global_demangle.wasm
else
global_demangle_prebuild.wasm: global_demangle.wasm

endif

global_location.wasm:

ifeq ($(COPY_HELLO),YES)
global_location.wasm: global_location_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying global_location_prebuild.wasm !!"
	cp global_location_prebuild.wasm global_location.wasm
else
global_location_prebuild.wasm: global_location.wasm

endif

global_underflow.wasm:

ifeq ($(COPY_HELLO),YES)
global_underflow.wasm: global_underflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying global_underflow_prebuild.wasm !!"
	cp global_underflow_prebuild.wasm global_underflow.wasm
else
global_underflow_prebuild.wasm: global_underflow.wasm

endif

halt_on_error_1.wasm:

ifeq ($(COPY_HELLO),YES)
halt_on_error_1.wasm: halt_on_error_1_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying halt_on_error_1_prebuild.wasm !!"
	cp halt_on_error_1_prebuild.wasm halt_on_error_1.wasm
else
halt_on_error_1_prebuild.wasm: halt_on_error_1.wasm

endif

heavy_uar_test.wasm:

ifeq ($(COPY_HELLO),YES)
heavy_uar_test.wasm: heavy_uar_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying heavy_uar_test_prebuild.wasm !!"
	cp heavy_uar_test_prebuild.wasm heavy_uar_test.wasm
else
heavy_uar_test_prebuild.wasm: heavy_uar_test.wasm

endif

ignorelist.wasm:

ifeq ($(COPY_HELLO),YES)
ignorelist.wasm: ignorelist_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying ignorelist_prebuild.wasm !!"
	cp ignorelist_prebuild.wasm ignorelist.wasm
else
ignorelist_prebuild.wasm: ignorelist.wasm

endif

interception_failure_test.wasm:

ifeq ($(COPY_HELLO),YES)
interception_failure_test.wasm: interception_failure_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying interception_failure_test_prebuild.wasm !!"
	cp interception_failure_test_prebuild.wasm interception_failure_test.wasm
else
interception_failure_test_prebuild.wasm: interception_failure_test.wasm

endif

intra_object_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
intra_object_overflow.wasm: intra_object_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying intra_object_overflow_prebuild.wasm !!"
	cp intra_object_overflow_prebuild.wasm intra_object_overflow.wasm
else
intra_object_overflow_prebuild.wasm: intra_object_overflow.wasm

endif

#large_func_test.wasm:

#ifeq ($(COPY_HELLO),YES)
#large_func_test.wasm: large_func_test_prebuild.wasm
#	@echo "!! NO wasm-ld(-VERSION) found  !!"
#	@echo "!! copying large_func_test_prebuild.wasm !!"
#	cp large_func_test_prebuild.wasm large_func_test.wasm
#else
#large_func_test_prebuild.wasm: large_func_test.wasm
#
#endif

log_path_test.wasm:

ifeq ($(COPY_HELLO),YES)
log_path_test.wasm: log_path_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying log_path_test_prebuild.wasm !!"
	cp log_path_test_prebuild.wasm log_path_test.wasm
else
log_path_test_prebuild.wasm: log_path_test.wasm

endif

malloc_context_size.wasm:

ifeq ($(COPY_HELLO),YES)
malloc_context_size.wasm: malloc_context_size_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying malloc_context_size_prebuild.wasm !!"
	cp malloc_context_size_prebuild.wasm malloc_context_size.wasm
else
malloc_context_size_prebuild.wasm: malloc_context_size.wasm

endif

memcmp_strict_test.wasm:

ifeq ($(COPY_HELLO),YES)
memcmp_strict_test.wasm: memcmp_strict_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying memcmp_strict_test_prebuild.wasm !!"
	cp memcmp_strict_test_prebuild.wasm memcmp_strict_test.wasm
else
memcmp_strict_test_prebuild.wasm: memcmp_strict_test.wasm

endif

memcmp_test.wasm:

ifeq ($(COPY_HELLO),YES)
memcmp_test.wasm: memcmp_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying memcmp_test_prebuild.wasm !!"
	cp memcmp_test_prebuild.wasm memcmp_strict_test.wasm
else
memcmp_test_prebuild.wasm: memcmp_test.wasm

endif

partial_right.wasm:

ifeq ($(COPY_HELLO),YES)
partial_right.wasm: partial_right_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying partial_right_prebuild.wasm !!"
	cp partial_right_prebuild.wasm partial_right.wasm
else
partial_right_prebuild.wasm: partial_right.wasm

endif

pass_object_byval.wasm:

ifeq ($(COPY_HELLO),YES)
pass_object_byval.wasm: pass_object_byval_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying pass_object_byval_prebuild.wasm !!"
	cp pass_object_byval_prebuild.wasm pass_object_byval.wasm
else
pass_object_byval_prebuild.wasm: pass_object_byval.wasm

endif

pass_struct_byval.wasm:

ifeq ($(COPY_HELLO),YES)
pass_struct_byval.wasm: pass_struct_byval_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying pass_struct_byval_prebuild.wasm !!"
	cp pass_struct_byval_prebuild.wasm pass_struct_byval.wasm
else
pass_struct_byval_prebuild.wasm: pass_struct_byval.wasm

endif

poison_partial.wasm:

ifeq ($(COPY_HELLO),YES)
poison_partial.wasm: poison_partial_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying poison_partial_prebuild.wasm !!"
	cp poison_partial_prebuild.wasm poison_partial.wasm
else
poison_partial_prebuild.wasm: poison_partial.wasm

endif

printf_2.wasm:

ifeq ($(COPY_HELLO),YES)
printf_2.wasm: printf_2_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying printf_2_prebuild.wasm !!"
	cp printf_2_prebuild.wasm printf_2.wasm
else
printf_2_prebuild.wasm: printf_2.wasm

endif

printf_3.wasm:

ifeq ($(COPY_HELLO),YES)
printf_3.wasm: printf_3_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying printf_3_prebuild.wasm !!"
	cp printf_3_prebuild.wasm printf_3.wasm
else
printf_3_prebuild.wasm: printf_3.wasm

endif

printf_5.wasm:

ifeq ($(COPY_HELLO),YES)
printf_5.wasm: printf_5_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying printf_5_prebuild.wasm !!"
	cp printf_5_prebuild.wasm printf_5_.wasm
else
printf_5_prebuild.wasm: printf_5.wasm

endif

printf_m.wasm:

ifeq ($(COPY_HELLO),YES)
printf_m.wasm: printf_m_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying printf_m_prebuild.wasm !!"
	cp printf_m_prebuild.wasm printf_m_.wasm
else
printf_m_prebuild.wasm: printf_m.wasm

endif

vla_chrome_testcase.wasm:

ifeq ($(COPY_HELLO),YES)
vla_chrome_testcase.wasm: vla_chrome_testcase_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying vla_chrome_testcase_prebuild.wasm !!"
	cp vla_chrome_testcase_prebuild.wasm vla_chrome_testcase.wasm
else
vla_chrome_testcase_prebuild.wasm: vla_chrome_testcase.wasm

endif

vla_condition_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
vla_condition_overflow.wasm: vla_condition_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying vla_condition_overflow_prebuild.wasm !!"
	cp vla_condition_overflow_prebuild.wasm vla_condition_overflow.wasm
else
vla_condition_overflow_prebuild.wasm: vla_condition_overflow.wasm

endif

vla_loop_overflow.wasm:

ifeq ($(COPY_HELLO),YES)
vla_loop_overflow.wasm: vla_loop_overflow_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying vla_loop_overflow_prebuild.wasm !!"
	cp vla_loop_overflow_prebuild.wasm vla_loop_overflow.wasm
else
vla_loop_overflow_prebuild.wasm: vla_loop_overflow.wasm

endif

stack_oob_frames.wasm:

ifeq ($(COPY_HELLO),YES)
stack_oob_frames.wasm: stack_oob_frames_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying stack_oob_frames_prebuild.wasm !!"
	cp stack_oob_frames_prebuild.wasm vla_loop_overflow.wasm
else
stack_oob_frames_prebuild.wasm: stack_oob_frames.wasm

endif

strcat_strict.wasm:

ifeq ($(COPY_HELLO),YES)
strcat_strict.wasm: strcat_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying strcat_strict_prebuild.wasm !!"
	cp strcat_strict_prebuild.wasm strcat_strict.wasm
else
strcat_strict_prebuild.wasm: strcat_strict.wasm

endif

# strcmp_strict.wasm
strcmp_strict.wasm:

ifeq ($(COPY_HELLO),YES)
strcmp_strict.wasm: strcmp_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying strcmp_strict_prebuild.wasm !!"
	cp strcmp_strict_prebuild.wasm strcmp_strict.wasm
else
strcmp_strict_prebuild.wasm: strcmp_strict.wasm
endif

# strspn_strict.wasm
strspn_strict.wasm:

ifeq ($(COPY_HELLO),YES)
strspn_strict.wasm: strspn_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying strspn_strict_prebuild.wasm !!"
	cp strspn_strict_prebuild.wasm strspn_strict.wasm
else
strspn_strict_prebuild.wasm: strspn_strict.wasm
endif

# strstr_strict.wasm
strstr_strict.wasm:

ifeq ($(COPY_HELLO),YES)
strstr_strict.wasm: strstr_strict_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying strstr_strict_prebuild.wasm !!"
	cp strstr_strict_prebuild.wasm strstr_strict.wasm
else
strstr_strict_prebuild.wasm: strstr_strict.wasm
endif

# suppressions_interceptor.wasm
suppressions_interceptor.wasm:

ifeq ($(COPY_HELLO),YES)
suppressions_interceptor.wasm: suppressions_interceptor_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying suppressions_interceptor_prebuild.wasm !!"
	cp suppressions_interceptor_prebuild.wasm suppressions_interceptor.wasm
else
suppressions_interceptor_prebuild.wasm: suppressions_interceptor.wasm
endif

# time_interceptor.wasm
time_interceptor.wasm:

ifeq ($(COPY_HELLO),YES)
time_interceptor.wasm: time_interceptor_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying time_interceptor_prebuild.wasm !!"
	cp time_interceptor_prebuild.wasm time_interceptor.wasm
else
time_interceptor_prebuild.wasm: time_interceptor.wasm
endif

# use_after_conversion.wasm
use_after_conversion.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_conversion.wasm: use_after_conversion_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_conversion_prebuild.wasm !!"
	cp use_after_conversion_prebuild.wasm use_after_conversion.wasm
else
use_after_conversion_prebuild.wasm: use_after_conversion.wasm
endif

# use_after_free.wasm
use_after_free.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_free.wasm: use_after_free_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_free_prebuild.wasm !!"
	cp use_after_free_prebuild.wasm use_after_free.wasm
else
use_after_free_prebuild.wasm: use_after_free.wasm
endif

# use_after_free_right.wasm
use_after_free_right.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_free_right.wasm: use_after_free_right_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_free_right_prebuild.wasm !!"
	cp use_after_free_right_prebuild.wasm use_after_free_right.wasm
else
use_after_free_right_prebuild.wasm: use_after_free_right.wasm
endif

# use_after_scope_dtor_order.wasm
use_after_scope_dtor_order.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_dtor_order.wasm: use_after_scope_dtor_order_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_dtor_order_prebuild.wasm !!"
	cp use_after_scope_dtor_order_prebuild.wasm use_after_scope_dtor_order.wasm
else
use_after_scope_dtor_order_prebuild.wasm: use_after_scope_dtor_order.wasm
endif

# use_after_scope_goto.wasm
use_after_scope_goto.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_goto.wasm: use_after_scope_goto_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_goto_prebuild.wasm !!"
	cp use_after_scope_goto_prebuild.wasm use_after_scope_goto.wasm
else
use_after_scope_goto_prebuild.wasm: use_after_scope_goto.wasm
endif

# use_after_scope_if.wasm
use_after_scope_if.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_if.wasm: use_after_scope_if_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_if_prebuild.wasm !!"
	cp use_after_scope_if_prebuild.wasm use_after_scope_if.wasm
else
use_after_scope_if_prebuild.wasm: use_after_scope_if.wasm
endif

# use_after_scope_inlined.wasm
use_after_scope_inlined.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_inlined.wasm: use_after_scope_inlined_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_inlined_prebuild.wasm !!"
	cp use_after_scope_inlined_prebuild.wasm use_after_scope_inlined.wasm
else
use_after_scope_inlined_prebuild.wasm: use_after_scope_inlined.wasm
endif

# use_after_scope_loop.wasm
use_after_scope_loop.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_loop.wasm: use_after_scope_loop_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_loop_prebuild.wasm !!"
	cp use_after_scope_loop_prebuild.wasm use_after_scope_loop.wasm
else
use_after_scope_loop_prebuild.wasm: use_after_scope_loop.wasm
endif

# use_after_scope_loop_bug.wasm
use_after_scope_loop_bug.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_loop_bug.wasm: use_after_scope_loop_bug_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_loop_bug_prebuild.wasm !!"
	cp use_after_scope_loop_bug_prebuild.wasm use_after_scope_loop_bug.wasm
else
use_after_scope_loop_bug_prebuild.wasm: use_after_scope_loop_bug.wasm
endif

# use_after_scope_nodebug.wasm
use_after_scope_nodebug.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_nodebug.wasm: use_after_scope_nodebug_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_nodebug_prebuild.wasm !!"
	cp use_after_scope_nodebug_prebuild.wasm use_after_scope_nodebug.wasm
else
use_after_scope_nodebug_prebuild.wasm: use_after_scope_nodebug.wasm
endif

# use_after_scope_temp.wasm
use_after_scope_temp.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_temp.wasm: use_after_scope_temp_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_temp_prebuild.wasm !!"
	cp use_after_scope_temp_prebuild.wasm use_after_scope_temp.wasm
else
use_after_scope_temp_prebuild.wasm: use_after_scope_temp.wasm
endif

# use_after_scope_temp2.wasm
use_after_scope_temp2.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_temp2.wasm: use_after_scope_temp2_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_temp2_prebuild.wasm !!"
	cp use_after_scope_temp2_prebuild.wasm use_after_scope_temp2.wasm
else
use_after_scope_temp2_prebuild.wasm: use_after_scope_temp2.wasm
endif

# use_after_scope_types.wasm
use_after_scope_types.wasm:

ifeq ($(COPY_HELLO),YES)
use_after_scope_types.wasm: use_after_scope_types_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying use_after_scope_types_prebuild.wasm !!"
	cp use_after_scope_types_prebuild.wasm use_after_scope_types.wasm
else
use_after_scope_types_prebuild.wasm: use_after_scope_types.wasm
endif

# verbose_log_path_test.wasm
verbose_log_path_test.wasm:

ifeq ($(COPY_HELLO),YES)
verbose_log_path_test.wasm: verbose_log_path_test_prebuild.wasm
	@echo "!! NO wasm-ld(-VERSION) found  !!"
	@echo "!! copying verbose_log_path_test_prebuild.wasm !!"
	cp verbose_log_path_test_prebuild.wasm verbose_log_path_test.wasm
else
verbose_log_path_test_prebuild.wasm: verbose_log_path_test.wasm
endif




.PHONY: FORCE
