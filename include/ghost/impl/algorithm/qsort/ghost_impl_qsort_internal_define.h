/*
 * MIT No Attribution
 *
 * Copyright (c) 2022 Fraser Heavy Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GHOST_IMPL_QSORT_INTERNAL_DEFINE_H_INCLUDED
#define GHOST_IMPL_QSORT_INTERNAL_DEFINE_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * Defines Ghost's internal qsort_r().
 */

#if !GHOST_EMIT_DEFS && !GHOST_IMPL_AMALGAMATED
    #error "This file is not supposed to be included if Ghost is not emitting function definitions."
#endif

#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"
#include "ghost/impl/ghost_impl_always_inline.h"
#include "ghost/impl/ghost_impl_function.h"
#include "ghost/language/ghost_expect_false.h"
#include "ghost/language/ghost_optimize_for_size_opt.h"
#include "ghost/language/ghost_discard.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/language/ghost_unreachable.h"
#include "ghost/preprocessor/ghost_msvc_traditional.h"
#include "ghost/preprocessor/ghost_blank.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/type/size_t/ghost_size_width.h"
#include "ghost/type/size_t/ghost_size_max.h"
#include "ghost/type/char/ghost_char_width.h"
#include "ghost/type/bool/ghost_bool.h"
#include "ghost/type/bool/ghost_true.h"
#include "ghost/type/bool/ghost_false.h"
#include "ghost/math/min/ghost_min_z.h"
#include "ghost/debug/ghost_assert.h"

#if GHOST_OPTIMIZE_FOR_SIZE_OPT
#include "ghost/language/ghost_array_count.h"
#include "ghost/debug/ghost_static_assert.h"
#include "ghost/math/checked_mul/ghost_checked_mul_z.h"
#endif

/*
 * This file contains two implementations of qsort() and friends: one using a
 * fast introsort and one using shellsort.
 */

/*
 * Introsort is used when optimizing for speed. The implementation is virtually
 * identical to Pottery's utility qsort() which is competitive in performance
 * with the fastest platform qsorts. This code was generated by literally
 * running the preprocessor on the following implementation and cleaning it up
 * by hand:
 *
 *     https://github.com/ludocode/pottery/tree/develop/util/pottery/qsort
 *
 * Introsort will compile to several kilobytes of machine code depending on CPU
 * architecture. Though this is quite large, it has several desirable
 * properties that we don't really want to compromise on for a safe and fast
 * qsort function:
 *
 * - memory usage is O(1) because it does not recurse or allocate;
 *
 * - speed and number of comparisons are both excellent in the average case due
 *   to quicksort with insertion sort optimization for short partitions;
 *
 * - speed approaches O(n) for mostly sorted arrays due to median-of-medians
 *   pivot selection for large partitions;
 *
 * - guaranteed worst time is still O(nlogn) due to heapsort depth fallback.
 *
 * Making the implementation smaller would require compromising on at least
 * one of these properties. Any other implementation would compromise on too
 * many of the above properties. In particular:
 *
 * - timsort and mergesort require memory allocation;
 *
 * - heapsort alone is slow and performs badly on mostly sorted arrays;
 *
 * - smoothsort is way slower than its proponents claim (I'm looking at you
 *   musl.)
 *
 * At least for C, introsort is still king.
 */

/*
 * When optimizing for size, we assume compromises are desired for smaller code
 * size so Shellsort is used.
 *
 * It uses the Ciura gap sequence extended by *2.25 which gives great average
 * performance. The compiled code is quite small, yet it still implements all
 * the qsort_r() variations and still provides nice swap optimizations for
 * 32-bit and 64-bit elements.
 *
 * The downside is that the worst case complexity of Shellsort is not O(nlogn).
 * It should be a lot better than O(n^2) though. Our 2.25^k extension sequence
 * is probably something like O(n^x) where x is around 3/2 or 4/3 (the
 * literature is not clear on this.)
 */

/* TODO more cleanup is needed and we should port comments over from Pottery's
 * templates. This still looks quite a bit like generated code. There's also a
 * bunch of added braces hacked in to avoid mixed declarations and code to make
 * this compile as C89. */

/* TODO if GHOST_MANUAL_DEFS is enabled, all the below inline functions should
 * be static. */

GHOST_IMPL_FUNCTION_OPEN

ghost_impl_inline
int ghost_impl_qsort_compare(ghost_impl_qsort_state_t* state, void* left, void* right) {
    switch (state->variant) {
        case ghost_impl_qsort_variant_nocontext: return state->compare.nocontext(left, right);
        case ghost_impl_qsort_variant_gnu: return state->compare.gnu(left, right, state->user_context);
        case ghost_impl_qsort_variant_bsd: return state->compare.bsd(state->user_context, left, right);
        #if GHOST_WIN_QSORT_S_USE_CDECL
        case ghost_impl_qsort_variant_windows: return state->compare.windows(state->user_context, left, right);
        #endif
    }
    ghost_unreachable(0);
}

ghost_impl_inline
void ghost_impl_qsort_swap_restrict(ghost_impl_qsort_state_t* state, void* vleft, void* vright) {
    /* TODO add ghost_restrict here, make sure it works before and after */
    switch (state->size_class) {
        case ghost_impl_qsort_size_class_4: {
            ghost_uint32_t* left = ghost_static_cast(ghost_uint32_t*, vleft);
            ghost_uint32_t* right = ghost_static_cast(ghost_uint32_t*, vright);
            ghost_uint32_t temp = *left;
            *left = *right;
            *right = temp;
        } return;
        case ghost_impl_qsort_size_class_8: {
            ghost_uint64_t* left = ghost_static_cast(ghost_uint64_t*, vleft);
            ghost_uint64_t* right = ghost_static_cast(ghost_uint64_t*, vright);
            ghost_uint64_t temp = *left;
            *left = *right;
            *right = temp;
        } return;
        case ghost_impl_qsort_size_class_any: {
            char* left = ghost_static_cast(char*, vleft);
            char* right = ghost_static_cast(char*, vright);
            char* end = right + state->element_size;
            while (right != end) {
                char temp = *left;
                *left++ = *right;
                *right++ = temp;
            }
        } return;
    }
    ghost_unreachable();
}

ghost_impl_inline
void* ghost_impl_qsort_select( ghost_impl_qsort_state_t* context, void* base, ghost_size_t ghost_impl_v_index) {
    return ghost_static_cast(char*, base) + ghost_impl_v_index * context->element_size;
}

ghost_impl_inline
ghost_bool ghost_impl_qsort_compare_less(ghost_impl_qsort_state_t* context, void* left, void* right) {
    return 0 > ghost_impl_qsort_compare(context, left, right);
}

#if GHOST_OPTIMIZE_FOR_SIZE_OPT

/*
 * We use ghost_impl_noinline to discourage the compiler from inlining this so
 * that the definition of qsort can be merged across translation units. (It
 * will be a weak/comdat symbol if supported, and it may otherwise be merged
 * via identical code folding.) Use GHOST_MANUAL_DEFS if you want to ensure
 * that only one definition exists.
 */
ghost_impl_noinline
void ghost_impl_qsort_shellsort(ghost_impl_qsort_state_t* state, void* base, ghost_size_t count) {

    /*
     * Calculate gaps based on Ciura sequence extended by *2.25 (A102549).
     *
     *     https://en.wikipedia.org/wiki/Shellsort#Gap_sequences
     *
     * The Ciura gap sequence needs 20 elements on 32-bit or 47 elements on
     * 64-bit (not counting our overflow check or limit below, so actually
     * slightly less.) If we don't know the exact width of size_t, we use some
     * slight overestimates to guarantee that it fits.
     */
    #ifdef GHOST_SIZE_WIDTH
        #if GHOST_SIZE_WIDTH == 32
            ghost_size_t gaps[20];
        #elif GHOST_SIZE_WIDTH == 64
            ghost_size_t gaps[47];
        #else
            ghost_size_t gaps[GHOST_SIZE_WIDTH];
        #endif
    #else
        ghost_size_t gaps[sizeof(ghost_size_t) * GHOST_CHAR_WIDTH];
    #endif
    ghost_size_t gap_index;

    /* Start with hardcoded Ciura gaps */
    gaps[0] = 1;
    gaps[1] = 4;
    gaps[2] = 10;
    gaps[3] = 23;
    gaps[4] = 57;
    gaps[5] = 132;
    gaps[6] = 301;
    gaps[7] = 701;
    gap_index = (sizeof(ghost_size_t) > 1) ? 7 : 5;

    if (gaps[gap_index] > count / 2) {
        /* Figure out where to start */
        while (gaps[gap_index] > count / 2 && gap_index > 0) {
            --gap_index;
        }
    } else {
        while (gaps[gap_index] < count / 2) {
            /* This shouldn't be possible but we check anyway */
            if (ghost_expect_false(gap_index == ghost_array_count(gaps) - 1))
                break;

            /* Extend gap sequence by *2.25 (9/4) */
            if (ghost_checked_mul_z(&gaps[gap_index + 1], gaps[gap_index], 9))
                break;
            ++gap_index;
            gaps[gap_index] /= 4;
        }
    }

    /* Perform successive insertion sorts based on gap sequence */
    for (;;) {
        ghost_size_t gap = gaps[gap_index];
        ghost_size_t i;
        for (i = gap; i < count; ++i) {
            ghost_size_t j = i;
            while (j >= gap && ghost_impl_qsort_compare_less(state,
                            ghost_impl_qsort_select(state, base, j),
                            ghost_impl_qsort_select(state, base, j - gap)))
            {
                ghost_impl_qsort_swap_restrict(state,
                        ghost_impl_qsort_select(state, base, j),
                        ghost_impl_qsort_select(state, base, j - gap));
                j -= gap;
            }
        }
        if (gap_index == 0)
            break;
        --gap_index;
    }
}

#else /* !GHOST_OPTIMIZE_FOR_SIZE_OPT */

ghost_impl_always_inline
void ghost_impl_qsort_swap(ghost_impl_qsort_state_t* context,
        void* left, void* right)
{
    if (left != right)
        ghost_impl_qsort_swap_restrict(context, left, right);
}

ghost_impl_always_inline
ghost_bool ghost_impl_qsort_compare_greater(ghost_impl_qsort_state_t* context, void* left, void* right) {
    return 0 < ghost_impl_qsort_compare(context, left, right);
}

ghost_impl_always_inline
ghost_bool ghost_impl_qsort_compare_greater_or_equal(ghost_impl_qsort_state_t* context, void* left, void* right) {
    return 0 <= ghost_impl_qsort_compare(context, left, right);
}

ghost_impl_always_inline
void* ghost_impl_qsort_compare_min(ghost_impl_qsort_state_t* context, void* left, void* right) {
    return ghost_impl_qsort_compare_less(context, left, right) ? left : right;
}

ghost_impl_always_inline
void* ghost_impl_qsort_compare_max(ghost_impl_qsort_state_t* context, void* left, void* right) {
    return ghost_impl_qsort_compare_greater(context, left, right) ? left : right;
}

ghost_impl_inline
void* ghost_impl_qsort_compare_median(ghost_impl_qsort_state_t* context, void* a, void* b, void* c) {
    if (ghost_impl_qsort_compare_less(context, a, b)) {
        if (ghost_impl_qsort_compare_less(context, a, c))
            return ghost_impl_qsort_compare_min(context, b, c);
        return a;
    }
    if (ghost_impl_qsort_compare_less(context, a, c))
        return a;
    return ghost_impl_qsort_compare_max(context, b, c);
}



ghost_impl_always_inline
ghost_size_t ghost_impl_qsort_array_access_index(ghost_impl_qsort_state_t* context, void* base, void* entry) {
    return ghost_static_cast(ghost_size_t, (ghost_static_cast(char*, entry) - ghost_static_cast(char*, base))) / context->element_size;
}

ghost_impl_always_inline
void* ghost_impl_qsort_array_access_next(ghost_impl_qsort_state_t* context, void* base, void* entry) {
    ghost_discard(base);
    return ghost_static_cast(char*, entry) + context->element_size;
}

ghost_impl_always_inline
void* ghost_impl_qsort_array_access_previous(ghost_impl_qsort_state_t* context, void* base, void* entry) {
    ghost_discard(base);
    return ghost_static_cast(char*, entry) - context->element_size;
}




ghost_impl_always_inline
ghost_size_t ghost_impl_qsort_heap_sort_heap_parent(ghost_size_t offset, ghost_size_t ghost_impl_v_index) {
    return offset + ((ghost_impl_v_index - offset) - 1) / 2;
}

ghost_impl_always_inline
ghost_size_t ghost_impl_qsort_heap_sort_heap_child_left(ghost_size_t offset, ghost_size_t ghost_impl_v_index) {
    return offset + 2 * (ghost_impl_v_index - offset) + 1;
}

ghost_impl_always_inline
ghost_size_t ghost_impl_qsort_heap_sort_heap_child_right(ghost_size_t offset, ghost_size_t ghost_impl_v_index) {
    return offset + 2 * (ghost_impl_v_index - offset) + 2;
}

ghost_impl_function
void ghost_impl_qsort_heap_sort_heap_sift_down(ghost_impl_qsort_state_t* context, void* base, ghost_size_t offset, ghost_size_t count, ghost_size_t ghost_impl_v_index) {
    for (;;) {

        ghost_size_t child_index = ghost_impl_qsort_heap_sort_heap_child_left(offset, ghost_impl_v_index);
        if (child_index >= offset + count) {

            break;
        }

        {
        void* current_ref = ghost_impl_qsort_select(context, base, ghost_impl_v_index);
        void* child_ref = ghost_impl_qsort_select(context, base, child_index);

        ghost_size_t right_index = ghost_impl_qsort_heap_sort_heap_child_right(offset, ghost_impl_v_index);
        if (right_index < offset + count) {
            void* right_child_ref = ghost_impl_qsort_array_access_next(context, base, child_ref);
            if (ghost_impl_qsort_compare_greater(context, right_child_ref, child_ref)) {
                child_ref = right_child_ref;
                child_index = right_index;
            }
        }

        if (ghost_impl_qsort_compare_greater_or_equal(context, current_ref, child_ref))
            break;

        ghost_impl_qsort_swap_restrict(context, current_ref, child_ref);
        ghost_impl_v_index = child_index;
        }
    }
}

/* TODO looks like this one is unused */
#if 0
ghost_impl_function
void ghost_impl_qsort_heap_sort_heap_sift_up(ghost_impl_qsort_state_t* context, void* base, ghost_size_t offset, ghost_size_t ghost_impl_v_index) {


    while (ghost_impl_v_index != offset) {
        ghost_size_t parent_index = ghost_impl_qsort_heap_sort_heap_parent(offset, ghost_impl_v_index);

        void* current_ref = ghost_impl_qsort_select(context, base, ghost_impl_v_index);
        void* parent_ref = ghost_impl_qsort_select(context, base, parent_index);

        if (ghost_impl_qsort_compare_greater_or_equal(context, parent_ref, current_ref))
            break;

        ghost_impl_qsort_swap_restrict(context, parent_ref, current_ref);
        ghost_impl_v_index = parent_index;
    }
}
#endif

ghost_impl_inline
void ghost_impl_qsort_heap_sort_heap_build_range(ghost_impl_qsort_state_t* context, void* base, ghost_size_t offset, ghost_size_t count) {
    ghost_size_t ghost_impl_v_index;

    if (count <= 1)
        return;

    #if ghost_has(GHOST_SIZE_MAX)
    ghost_assert(count <= GHOST_SIZE_MAX / 4, "");
    #endif

    ghost_impl_v_index = ghost_impl_qsort_heap_sort_heap_parent(offset, offset + count - 1) + 1;

    while (ghost_impl_v_index > offset) {
        --ghost_impl_v_index;
        ghost_impl_qsort_heap_sort_heap_sift_down(context, base, offset, count, ghost_impl_v_index);
    }
}

ghost_impl_inline
void ghost_impl_qsort_heap_sort_heap_contract_bulk_range(ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t offset, ghost_size_t current_count, ghost_size_t contract_count)
{
    void* first_ref;
    void* last_ref;

    #if ghost_has(GHOST_SIZE_MAX)
    ghost_assert(current_count <= GHOST_SIZE_MAX / 4, "");
    #endif

    first_ref = ghost_impl_qsort_select(context, base, offset);
    last_ref = ghost_impl_qsort_select(context, base, offset + current_count - 1);

    for (; contract_count > 0; --contract_count) {
        if (--current_count == 0)
            return;
        ghost_impl_qsort_swap_restrict(context,
                first_ref,
                (last_ref));
        last_ref = ghost_impl_qsort_array_access_previous(context, base, last_ref);
        ghost_impl_qsort_heap_sort_heap_sift_down(context, base, offset, current_count, offset);
    }
}

ghost_impl_inline
void ghost_impl_qsort_heap_sort_range(
        ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t offset,
        ghost_size_t range_count)
{
    ghost_impl_qsort_heap_sort_heap_build_range(context, base,
            offset, range_count);
    ghost_impl_qsort_heap_sort_heap_contract_bulk_range(context, base,
            offset, range_count, range_count);
}

ghost_impl_inline
void ghost_impl_qsort_insertion_sort_range(
        ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t offset,
        ghost_size_t range_count)
{
    ghost_size_t i;
    for (i = offset + 1; i < offset + range_count; ++i) {
        void* current_ref = ghost_impl_qsort_select(context, base, i);

        ghost_size_t j;
        for (j = i; j > 0; --j) {
            void* previous_ref = ghost_impl_qsort_select(context, base, j - 1);
            if (!ghost_impl_qsort_compare_less(context, current_ref, previous_ref))
                break;
            ghost_impl_qsort_swap_restrict(context, current_ref, previous_ref);
            current_ref = previous_ref;
        }
    }
}

ghost_impl_always_inline
void* ghost_impl_qsort_choose_pivot(
        ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t start_index, ghost_size_t end_index)
{
    ghost_size_t half = (end_index - start_index) / 2;
    ghost_size_t a_i = start_index;
    ghost_size_t e_i = start_index + half;
    ghost_size_t i_i = end_index;

    void* a_e = ghost_impl_qsort_select(context, base, a_i);
    void* e_e = ghost_impl_qsort_select(context, base, e_i);
    void* i_e = ghost_impl_qsort_select(context, base, i_i);

    void* a_r = (a_e);
    void* e_r = (e_e);
    void* i_r = (i_e);

    if (end_index - start_index + 1 <= 32) {
        void* m_r = ghost_impl_qsort_compare_median(
                context, a_r, e_r, i_r);
        return m_r;
    }

    {
    ghost_size_t quarter = half / 2;
    ghost_size_t eighth = quarter / 2;
    ghost_size_t b_i = a_i + eighth;
    ghost_size_t c_i = a_i + quarter;
    ghost_size_t d_i = e_i - eighth;
    ghost_size_t f_i = e_i + eighth;
    ghost_size_t g_i = i_i - quarter;
    ghost_size_t h_i = i_i - eighth;

    void* b_e = ghost_impl_qsort_select(context, base, b_i);
    void* c_e = ghost_impl_qsort_select(context, base, c_i);
    void* d_e = ghost_impl_qsort_select(context, base, d_i);
    void* f_e = ghost_impl_qsort_select(context, base, f_i);
    void* g_e = ghost_impl_qsort_select(context, base, g_i);
    void* h_e = ghost_impl_qsort_select(context, base, h_i);

    void* b_r = (b_e);
    void* c_r = (c_e);
    void* d_r = (d_e);
    void* f_r = (f_e);
    void* g_r = (g_e);
    void* h_r = (h_e);

    void* m_r =
            ghost_impl_qsort_compare_median(context,
                ghost_impl_qsort_compare_median(context, a_r, b_r, c_r),
                ghost_impl_qsort_compare_median(context, d_r, e_r, f_r),
                ghost_impl_qsort_compare_median(context, g_r, h_r, i_r));

    return m_r;
    }
}

ghost_impl_inline
void ghost_impl_qsort_partition(
        ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t* first_index, ghost_size_t* last_index)
{
    ghost_size_t old_first_index = *first_index;
    ghost_size_t old_last_index = *last_index;


    void* first_entry = ghost_impl_qsort_select(
            context, base, old_first_index);
    void* last_entry = ghost_impl_qsort_select(
                context, base, old_last_index);


    void* original_pivot_ref =
            ghost_impl_qsort_choose_pivot(context, base, old_first_index, old_last_index);

    void* first_ref = (first_entry);
    void* pivot_ref = first_ref;
    ghost_impl_qsort_swap(context, original_pivot_ref, pivot_ref);

    {
    void* left_entry = first_entry;
    void* right_entry = ghost_impl_qsort_array_access_next(
            context, base, last_entry);

    void* left_equal_entry = left_entry;
    void* right_equal_entry = right_entry;

    for (;;) {

        for (;;) {
            right_entry = ghost_impl_qsort_array_access_previous(context, base, right_entry);

            if (left_entry == right_entry)
                goto done_inversions;

            {
            int three_way = ghost_impl_qsort_compare(context,
                        (right_entry),
                        pivot_ref);
            ghost_bool greater = three_way > 0;

            if (!greater) {
                ghost_bool less = three_way < 0;
                if (less)
                    break;

                right_equal_entry = ghost_impl_qsort_array_access_previous(context, base, right_equal_entry);
                ghost_impl_qsort_swap(context,
                        (right_entry),
                        (right_equal_entry));
            }
            }

        }

        for (;;) {
            left_entry = ghost_impl_qsort_array_access_next(context, base, left_entry);

            if (left_entry == right_entry)
                goto done_inversions;

            {
            int three_way = ghost_impl_qsort_compare(context,
                        (left_entry),
                        pivot_ref);

            ghost_bool less = three_way < 0;
            if (!less) {
                ghost_bool greater = three_way > 0;
                if (greater)
                    break;

                left_equal_entry = ghost_impl_qsort_array_access_next(context, base, left_equal_entry);
                ghost_impl_qsort_swap(context,
                        (left_entry),
                        (left_equal_entry));
            }
            }
        }

        ghost_impl_qsort_swap_restrict(context,
                (left_entry),
                (right_entry));

    }

done_inversions:;
    ghost_impl_qsort_swap(context,
            (right_entry),
            pivot_ref);

    {
    ghost_size_t left_equal_index = ghost_impl_qsort_array_access_index(context, base, left_equal_entry);
    ghost_size_t pivot_index = ghost_impl_qsort_array_access_index(context, base, left_entry);

    ghost_size_t first_less_index = left_equal_index + 1;
    ghost_size_t end_less_index = pivot_index + 1;

    ghost_size_t first_greater_index = pivot_index + 1;
    ghost_size_t end_greater_index = ghost_impl_qsort_array_access_index(context, base, right_equal_entry);
    ghost_size_t i;

    ghost_size_t left_swap_count = ghost_min_z(left_equal_index - old_first_index,
                end_less_index - first_less_index - 1);
    ghost_size_t right_swap_count = ghost_min_z(end_greater_index - first_greater_index,
            old_last_index + 1 - end_greater_index);

    for (i = 0; i < left_swap_count; ++i) {
        first_entry = ghost_impl_qsort_array_access_next(context, base, first_entry);
        left_entry = ghost_impl_qsort_array_access_previous(context, base, left_entry);
        ghost_impl_qsort_swap_restrict(context,
                (left_entry),
                (first_entry));
    }

    for (i = 0; i < right_swap_count; ++i) {
        right_entry = ghost_impl_qsort_array_access_next(context, base, right_entry);
        ghost_impl_qsort_swap_restrict(context,
                (right_entry),
                (last_entry));
        last_entry = ghost_impl_qsort_array_access_previous(context, base, last_entry);
    }

    *first_index = old_first_index + end_less_index - first_less_index;
    *last_index = old_last_index - end_greater_index + first_greater_index;
    }}
}

ghost_impl_inline
ghost_bool ghost_impl_qsort_fallback(
        ghost_impl_qsort_state_t* context, void* base,
        ghost_size_t first, ghost_size_t count, ghost_size_t depth, ghost_size_t depth_limit
) {
    ghost_size_t count_limit = 8;

    if (count <= count_limit) {
        ghost_impl_qsort_insertion_sort_range(context, base, first, count);
        return ghost_true;
    }

    if (depth == depth_limit) {
        ghost_impl_qsort_heap_sort_range(context, base, first, count);
        return ghost_true;
    }

    return ghost_false;
}

/*
 * As above, we use ghost_impl_noinline to reduce the risk of duplicates
 * existing in the final link.
 */
ghost_impl_noinline
void ghost_impl_qsort_introsort(
    ghost_impl_qsort_state_t* context, void* base,
    ghost_size_t range_count
) {
    struct {
        ghost_size_t first;
        ghost_size_t last;
        ghost_size_t depth;
    } stack[sizeof(ghost_size_t) * GHOST_CHAR_WIDTH];

    if (range_count <= 1)
        return;

    {
    ghost_size_t pos = 0;
    stack[0].first = 0;
    stack[0].last = range_count - 1;
    stack[0].depth = 0;

    {
    ghost_size_t n = 1;
    ghost_size_t depth_limit = 2;
    while (n < range_count) {
        n *= 2;
        depth_limit += 2;
    }

    for (;;) {
        ghost_size_t first = stack[pos].first;
        ghost_size_t last = stack[pos].last;
        ghost_size_t step_count = last - first + 1;

        if (ghost_impl_qsort_fallback(context, base, first, step_count,
                stack[pos].depth, depth_limit))
        {
            if (pos == 0)
                break;
            --pos;
            continue;
        }

        {
        ghost_size_t equal_first = first;
        ghost_size_t equal_last = last;
        ghost_impl_qsort_partition(context, base, &equal_first, &equal_last);
        {
        ghost_size_t left_count = equal_first - first;
        ghost_size_t right_count = last - equal_last;

        if (left_count <= 1 && right_count <= 1) {
            if (pos == 0)
                break;
            --pos;
            continue;
        }

        {
        ghost_size_t depth = stack[pos].depth + 1;

        if (left_count < right_count) {
            stack[pos].first = last - right_count + 1;
            stack[pos].last = last;
            stack[pos].depth = depth;
            if (left_count > 1) {
                ++pos;
                stack[pos].first = first;
                stack[pos].last = first + left_count - 1;
                stack[pos].depth = depth;
            }
        } else {
            stack[pos].first = first;
            stack[pos].last = first + left_count - 1;
            stack[pos].depth = depth;
            if (right_count > 1) {
                ++pos;
                stack[pos].first = last - right_count + 1;
                stack[pos].last = last;
                stack[pos].depth = depth;
            }
        }
        }}}
    }
    }}
}

#endif

GHOST_IMPL_FUNCTION_CLOSE

#endif
