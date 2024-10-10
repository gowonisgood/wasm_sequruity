/*
 * Copyright (C) 2020 TU Bergakademie Freiberg Karl Fessel
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*provide some test program*/
//#include "blob/heap_overflow_large.wasm.h"
#include "blob/stack_buffer_overflow.wasm.h"
#include "blob/sanity_check_pure_c.wasm.h"
#include "blob/global_overflow.wasm.h"
#include "blob/deep_stack_uaf.wasm.h"
#include "blob/huge_negative_hea_oob.wasm.h"
#include "blob/invalid_free.wasm.h"
#include "blob/stack_buffer_overflow_with_position.wasm.h"
#include "blob/stack_frame_demangle.wasm.h"
#include "blob/coverage.wasm.h"
#include "blob/use_after_scope.wasm.h"
#include "blob/alloca_overflow_partial.wasm.h"
#include "blob/alloca_big_alignment.wasm.h"
#include "blob/alloca_overflow_right.wasm.h"
#include "blob/alloca_underflow_left.wasm.h"
#include "blob/atoi_strict.wasm.h"
#include "blob/atol_strict.wasm.h"
#include "blob/atoll_strict.wasm.h"
#include "blob/calloc_overflow.wasm.h"
#include "blob/deep_tail_call.wasm.h"
#include "blob/double_free.wasm.h"
#include "blob/frexp_interceptor.wasm.h"
#include "blob/global_demangle.wasm.h"
#include "blob/global_location.wasm.h"
#include "blob/global_underflow.wasm.h"
#include "blob/halt_on_error_1.wasm.h"
#include "blob/heavy_uar_test.wasm.h"
#include "blob/ignorelist.wasm.h"
#include "blob/interception_failure_test.wasm.h"
#include "blob/intra_object_overflow.wasm.h"
//#include "blob/large_func_test.wasm.h"
#include "blob/log_path_test.wasm.h"
#include "blob/malloc_context_size.wasm.h"
#include "blob/memcmp_strict_test.wasm.h"
#include "blob/memcmp_test.wasm.h"
#include "blob/partial_right.wasm.h"
#include "blob/pass_object_byval.wasm.h"
#include "blob/pass_struct_byval.wasm.h"
#include "blob/poison_partial.wasm.h"
#include "blob/printf_2.wasm.h"
#include "blob/printf_3.wasm.h"
#include "blob/printf_5.wasm.h"
#include "blob/printf_m.wasm.h"
#include "blob/vla_chrome_testcase.wasm.h"
#include "blob/vla_condition_overflow.wasm.h"
#include "blob/vla_loop_overflow.wasm.h"
#include "blob/stack_oob_frames.wasm.h"
#include "blob/strcat_strict.wasm.h"
#include "blob/strcmp_strict.wasm.h"
#include "blob/strspn_strict.wasm.h"
#include "blob/strstr_strict.wasm.h"
#include "blob/suppressions_interceptor.wasm.h"
#include "blob/time_interceptor.wasm.h"
#include "blob/use_after_conversion.wasm.h"
#include "blob/use_after_free.wasm.h"
#include "blob/use_after_free_right.wasm.h"
#include "blob/use_after_scope_dtor_order.wasm.h"
#include "blob/use_after_scope_goto.wasm.h"
#include "blob/use_after_scope_if.wasm.h"
#include "blob/use_after_scope_inlined.wasm.h"
#include "blob/use_after_scope_loop.wasm.h"
#include "blob/use_after_scope_loop_bug.wasm.h"
#include "blob/use_after_scope_loop_removed.wasm.h"
#include "blob/use_after_scope_nodebug.wasm.h"
#include "blob/use_after_scope_temp.wasm.h"
#include "blob/use_after_scope_temp2.wasm.h"
#include "blob/use_after_scope_types.wasm.h"
#include "blob/verbose_log_path_test.wasm.h"

bool iwasm_runtime_init(void);
void iwasm_runtime_destroy(void);

/* wamr_run is a very direct interpretation of "i like to have a wamr_run" */
int wamr_run(void *bytecode, size_t bytecode_len, int argc, char **argv);

/* wamr_run_cp creates a copy bytecode and argv
 * if argc is 0 it is set to 1 and argv[0] is set to ""
 * to create some space for a return value */
int wamr_run_cp(const void *bytecode, size_t bytecode_len, int argc, const char **argv);

#define telltruth(X) ((X) ? "true" : "false")

int main(void)
{

    /*heap_overflow_large*/
    //printf("iwasm_initilised: %s\n", telltruth(iwasm_runtime_init()));
    //int ret = wamr_run_cp(heap_overflow_large_wasm, heap_overflow_large_wasm_len, 1, 0);
    //printf("ret = %d\n", ret);
    //iwasm_runtime_destroy();
    /*end heap_overflow_large*/
	int ret = 0;
    /*stack_buffer_overflow*/
     printf("iwasm_initilised: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(stack_buffer_overflow_wasm, stack_buffer_overflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end stack_buffer_overflow*/

    /*sanity_check_pure_c*/
    printf("iwasm_initilised_sanity_check_pure_c: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(sanity_check_pure_c_wasm, sanity_check_pure_c_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end sanity_check_pure_c*/


    /*global_overflow*/
     printf("iwasm_initialized_global_overflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(global_overflow_wasm, global_overflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end global_overflow*/

    /*deep_stack_uaf*/
    printf("iwasm_initialized_deep_stack_uaf: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(deep_stack_uaf_wasm, deep_stack_uaf_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end deep_stack_uaf*/

    /*huge_negative_hea_oob*/
    printf("iwasm_initialized_huge_negative_hea_oob: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(huge_negative_hea_oob_wasm, huge_negative_hea_oob_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end huge_negative_hea_oob*/

    /*invalid_free*/
    printf("iwasm_initialized_invalid_free: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(invalid_free_wasm, invalid_free_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end invalid_free*/

    /*stack_buffer_overflow_with_position*/
    int argc1 = 1;
    const char *argv1[] = {"10"};
    printf("iwasm_initialized_stack_buffer_overflow_with_position: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(stack_buffer_overflow_with_position_wasm, stack_buffer_overflow_with_position_wasm_len, argc1, argv1);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end stack_buffer_overflow_with_position*/

    /*stack_frame_demangle*/
    printf("iwasm_initialized_stack_frame_demangle: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(stack_frame_demangle_wasm, stack_frame_demangle_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end stack_frame_demangle*/

    /*stack_frame_demangle*/
    int argc2 = 6;
    const char *argv2[] = {"arg1", "arg2", "arg3", "foo", "bar", "arg6"};
    printf("iwasm_initialized_coverage: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(coverage_wasm, coverage_wasm_len, argc2, argv2);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end stack_frame_demangle*/

    /*use_after_scope*/
    printf("iwasm_initialized_use_after_scope: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_wasm, use_after_scope_wasm_len, argc2, argv2);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope*/

    /*use_after_scope*/
    printf("iwasm_initialized_use_after_scope: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_wasm, use_after_scope_wasm_len, argc2, argv2);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope*/

    /*alloca_overflow_partial*/
    printf("iwasm_initialized_alloca_overflow_partial: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(alloca_overflow_partial_wasm, alloca_overflow_partial_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end alloca_overflow_partial*/

    /*alloca_big_alignment*/
    printf("iwasm_initialized_alloca_big_alignment: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(alloca_big_alignment_wasm, alloca_big_alignment_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end alloca_big_alignment*/

    /*alloca_overflow_right*/
    printf("iwasm_initialized_alloca_overflow_right: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(alloca_overflow_right_wasm, alloca_overflow_right_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end alloca_overflow_right*/

    /*alloca_underflow_left*/
    printf("iwasm_initialized_alloca_underflow_left: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(alloca_underflow_left_wasm, alloca_underflow_left_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end alloca_underflow_left*/

    /*atoi_strict*/
    int argc3 = 1;
    const char *argv3[] = {"test1"};
    printf("iwasm_initialized_atoi_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(atoi_strict_wasm, atoi_strict_wasm_len, argc3, argv3);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end atoi_strict*/

    /*atol_strict*/
    int argc4 = 1;
    const char *argv4[] = {"test1"};
    printf("iwasm_initialized_atol_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(atol_strict_wasm, atol_strict_wasm_len, argc4, argv4);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end atol_strict*/

    /*atol_strict*/
    int argc5 = 1;
    const char *argv5[] = {"test1"};
    printf("iwasm_initialized_atoll_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(atoll_strict_wasm, atoll_strict_wasm_len, argc5, argv5);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end atol_strict*/

    /*calloc_overflow*/
    printf("iwasm_initialized_calloc_overflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(calloc_overflow_wasm, calloc_overflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end calloc_overflow*/

    /*deep_tail_call*/
    printf("iwasm_initialized_deep_tail_call: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(deep_tail_call_wasm, deep_tail_call_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end deep_tail_call*/

    /*double_free*/
    printf("iwasm_initialized_double_free: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(double_free_wasm, double_free_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end double_free*/

    /*frexp_interceptor fail: failed to link*/
    /*printf("iwasm_initialized_frexp_interceptor: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(frexp_interceptor_wasm, frexp_interceptor_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end frexp_interceptor*/

    /*global_demangle*/
    printf("iwasm_initialized_global_demangle: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(global_demangle_wasm, global_demangle_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end global_demangle*/

    /*global_location*/
    int argc6 = 3;
    const char *argv6[]={"aaaa","bbbb","ccc"};
    printf("iwasm_initialized_global_location: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(global_location_wasm, global_location_wasm_len, argc6, argv6);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end global_location*/

    /*global_underflow bad: out of bounds*/
    /*printf("iwasm_initialized_global_underflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(global_underflow_wasm, global_underflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end global_underflow*/

    /*halt_on_error_1*/
    printf("iwasm_initialized_halt_on_error_1: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(halt_on_error_1_wasm, halt_on_error_1_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end halt_on_error_1*/
   
    /*heavy_uar_test bad: linear memory is too small.*/
    /*int argc7 = 2;
    const char *argv7[]={"5","5"};

    printf("iwasm_initialized_heavy_uar_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(heavy_uar_test_wasm, heavy_uar_test_wasm_len, argc7, argv7);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end heavy_uar_test*/

    /*ignorelist*/
    int argc8 = 10;
    const char *argv8[] = {"aa","aa","aa","aa","aa","aa","aa","aa","aa","aa"};
    printf("iwasm_initialized_ignorelist: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(ignorelist_wasm, ignorelist_wasm_len, argc8, argv8);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end ignorelist*/

    /*interception_failure_test*/
    printf("iwasm_initialized_interception_failure_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(interception_failure_test_wasm, interception_failure_test_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end interception_failure_test*/

    /*intra-object-overflow.cpp*/
    int argc9 = 1;
    const char *argv9[] = {"11"};
    printf("iwasm_initialized_intra_object_overflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(intra_object_overflow_wasm, intra_object_overflow_wasm_len, argc9, argv9);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*intra-object-overflow*/

    /*large_func_test*/
    /*printf("iwasm_initialized_large_func_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(large_func_test_wasm, large_func_test_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*large_func_test*/

    /*log_path_test*/
    printf("iwasm_initialized_log_path_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(log_path_test_wasm, log_path_test_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*log_path_test*/

    /*malloc_context_size bad:fail to link*/
    /*printf("iwasm_initialized_malloc_context_size: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(malloc_context_size_wasm, malloc_context_size_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*malloc_context_size*/

    /*memcmp_strict_test*/
    printf("iwasm_initialized_memcmp_strict_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(memcmp_strict_test_wasm, memcmp_strict_test_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*memcmp_strict_test*/

    /*memcmp_test*/
    int argc10 = 1;
    const char *argv10[] = {"any_value"};
    printf("iwasm_initialized_memcmp_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(memcmp_test_wasm, memcmp_test_wasm_len, argc10, argv10);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*memcmp_test*/

    /*partial_right*/
     printf("iwasm_initialized_partial_right: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(partial_right_wasm, partial_right_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*partial_right*/
    
    /*pass_object_byval*/
    printf("iwasm_initialized_pass_object_byval: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(pass_object_byval_wasm, pass_object_byval_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*pass_object_byval*/ 

    /*pass_struct_bybal*/
    printf("iwasm_initialized_pass_struct__byval: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(pass_struct_byval_wasm, pass_struct_byval_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*pass_struct_byval*/

    /*poison_partial bad: fail to link*/
     /*printf("iwasm_initialized_poison_partial: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(poison_partial_wasm, poison_partial_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*poison_partial*/

    /*printf_2*/
    printf("iwasm_initialized_pass_printf_2: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(printf_2_wasm, printf_2_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*printf_2*/

    /*printf_3*/
    printf("iwasm_initialized_pass_printf_3: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(printf_3_wasm, printf_3_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*printf_3*/

    /*printf_5*/
    printf("iwasm_initialized_pass_printf_5: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(printf_5_wasm, printf_5_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*printf_5*/

   /*printf_m*/
    printf("iwasm_initialized_pass_printf_m: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(printf_m_wasm, printf_m_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*printf_m*/

    /*vla_chrome_testcase*/
    printf("iwasm_initialized_vla_chrome_testcase: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(vla_chrome_testcase_wasm, vla_chrome_testcase_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*vla_chrome_testcase*/

    /*vla_condition_overflow*/
    printf("iwasm_initialized_vla_condition_overflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(vla_condition_overflow_wasm, vla_condition_overflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*vla_condition_overflow*/

    /*vla_loop_overflow*/
    printf("iwasm_initialized_vla_loop_overflow: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(vla_loop_overflow_wasm, vla_loop_overflow_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*vla_loop_overflow*/
    

    /*stack_oob_frames*/
    printf("iwasm_initialized_stack_oob_frames: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(stack_oob_frames_wasm, stack_oob_frames_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*stack_oob_frames*/

    /*strcat_strict*/
    int argc11 = 1;
    const char *argv11[] = {"test1"};
    printf("iwasm_initialized_strcat_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(strcat_strict_wasm, strcat_strict_wasm_len, argc11,argv11);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*stack_oob_frames*/


    /*strcmp_strict*/
    printf("iwasm_initialized_strcmp_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(strcmp_strict_wasm, strcmp_strict_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end strcmp_strict*/

/*use_after_free_right*/
    printf("iwasm_initialized_use_after_free_right: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_free_right_wasm, use_after_free_right_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_free_right*/

/*use_after_scope_loop_removed*/
    printf("iwasm_initialized_use_after_scope_loop_removed: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_loop_removed_wasm, use_after_scope_loop_removed_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_loop_removed*/

/*strspn_strict*/
    printf("iwasm_initialized_strspn_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(strspn_strict_wasm, strspn_strict_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end strspn_strict*/

/*use_after_scope_dtor_order*/
    printf("iwasm_initialized_use_after_scope_dtor_order: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_dtor_order_wasm, use_after_scope_dtor_order_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_dtor_order*/

/*use_after_scope_nodebug*/
    printf("iwasm_initialized_use_after_scope_nodebug: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_nodebug_wasm, use_after_scope_nodebug_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_nodebug*/

/*strstr_strict*/
    printf("iwasm_initialized_strstr_strict: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(strstr_strict_wasm, strstr_strict_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end strstr_strict*/

/*use_after_scope_goto*/
    printf("iwasm_initialized_use_after_scope_goto: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_goto_wasm, use_after_scope_goto_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_goto*/

/*use_after_scope_temp2*/
    printf("iwasm_initialized_use_after_scope_temp2: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_temp2_wasm, use_after_scope_temp2_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_temp2*/

/*suppressions_interceptor bad: fail to link*/
    /*printf("iwasm_initialized_suppressions_interceptor: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(suppressions_interceptor_wasm, suppressions_interceptor_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end suppressions_interceptor*/

/*use_after_scope_if*/
    printf("iwasm_initialized_use_after_scope_if: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_if_wasm, use_after_scope_if_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_if*/

/*use_after_scope_temp*/
    printf("iwasm_initialized_use_after_scope_temp: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_temp_wasm, use_after_scope_temp_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_temp*/

/*time_interceptor bad: fali to link*/
    /*printf("iwasm_initialized_time_interceptor: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(time_interceptor_wasm, time_interceptor_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end time_interceptor*/

/*use_after_scope_inlined*/
    printf("iwasm_initialized_use_after_scope_inlined: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_inlined_wasm, use_after_scope_inlined_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_inlined*/

/*use_after_scope_types bad: fali to link*/
    /*printf("iwasm_initialized_use_after_scope_types: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_types_wasm, use_after_scope_types_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();*/
    /*end use_after_scope_types*/

/*use_after_conversion*/
    printf("iwasm_initialized_use_after_conversion: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_conversion_wasm, use_after_conversion_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_conversion*/

/*use_after_scope_loop_bug*/
    printf("iwasm_initialized_use_after_scope_loop_bug: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_loop_bug_wasm, use_after_scope_loop_bug_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_loop_bug*/

/*verbose_log_path_test*/
    printf("iwasm_initialized_verbose_log_path_test: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(verbose_log_path_test_wasm, verbose_log_path_test_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end verbose_log_path_test*/

/*use_after_free*/
    printf("iwasm_initialized_use_after_free: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_free_wasm, use_after_free_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_free*/

/*use_after_scope_loop*/
    printf("iwasm_initialized_use_after_scope_loop: %s\n", telltruth(iwasm_runtime_init()));
    ret = wamr_run_cp(use_after_scope_loop_wasm, use_after_scope_loop_wasm_len, 0, 0);
    printf("ret = %d\n", ret);
    iwasm_runtime_destroy();
    /*end use_after_scope_loop*/


    return 0;
}
