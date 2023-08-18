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

#ifndef GHOST_IMPL_THREAD_AUX_H_INCLUDED
#define GHOST_IMPL_THREAD_AUX_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_thread_aux is the auxiliary storage for thread return values that
 * don't fit in the real return value of platform threads.
 *
 * For platform threads that return int (e.g. Windows or C11), if you want to
 * return void* on a 64-bit platform, this auxiliary storage is required.
 */

/* TODO forbid override */

/* Only use this if we have a platform thread type that returns int and not
 * void*. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/impl/thread/ghost_impl_ex_ithread_t.h"
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_t.h"
    #if !ghost_has(ghost_impl_ex_ithread_t) || ghost_has(ghost_impl_ex_vpthread_t)
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

/* Only use this if void* doesn't fit in the int return type. (While
 * ghost_vpthread_t.h checks this itself before including this, we also want
 * this code disabled when unnecessary in amalgamations.) */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/type/intptr_t/ghost_intptr_t.h"
    #include "ghost/type/int/ghost_int_width.h"
    #if GHOST_INT_WIDTH >= GHOST_INTPTR_WIDTH
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

/* We need either ghost_selectany_var or manual emission of definitions in
 * order to define a global variable containing the aux state. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/language/ghost_selectany_var.h"
    #if !ghost_has(ghost_selectany_var) && !GHOST_MANUAL_DEFS
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

/* We need ghost_mutex to implement aux threading. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has(ghost_mutex_t)
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

/* We need either GHOST_MUTEX_INIT or ghost_once() to initialize a mutex. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/thread/mutex/ghost_mutex_init_s.h"
    #if !ghost_has(GHOST_MUTEX_INIT)
        #include "ghost/thread/mutex/ghost_mutex_init.h"
        #include "ghost/thread/once/ghost_once_t.h"
        #include "ghost/thread/once/ghost_once_init_s.h"
        #include "ghost/thread/once/ghost_once_fn.h"
        #if !ghost_has(ghost_once)
            #define ghost_has_ghost_impl_thread_aux 0
        #endif
    #endif
#endif

/* We need malloc. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/malloc/ghost_free.h"
    #include "ghost/malloc/ghost_alloc.h"
    #include "ghost/malloc/ghost_alloc_array.h"
    #if !ghost_has(ghost_alloc) || !ghost_has(ghost_free)
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

/* We need ghost_ensure() for error checking. */
#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/debug/ghost_ensure.h"
    #if !ghost_has(ghost_ensure)
        #define ghost_has_ghost_impl_thread_aux 0
    #endif
#endif

#ifndef ghost_has_ghost_impl_thread_aux
    #include "ghost/debug/ghost_assert.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/string/ghost_memcpy.h"
    #include "ghost/thread/mutex/ghost_mutex_lock.h"
    #include "ghost/thread/mutex/ghost_mutex_unlock.h"
    #include "ghost/thread/thread_options/ghost_thread_options_t.h"
    #include "ghost/thread/thread_id/ghost_thread_id_t.h"
    #include "ghost/thread/thread_id/ghost_thread_id_equal.h"
    #include "ghost/thread/thread_id/ghost_thread_id_current.h"
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/type/size_t/ghost_size_t.h"

    GHOST_IMPL_FUNCTION_OPEN

    /*
     * Our auxiliary storage is a global map of ints to thread storage. The int
     * is passed into and returned from each thread in the map.
     *
     * The map is implemented as a simple growable array. Deleted entries are
     * stored in a linked list.
     */

    typedef struct {
        void* ghost_impl_ret;
        ghost_bool ghost_impl_returned;
        ghost_bool ghost_impl_detached;
        ghost_thread_id_t ghost_v_thread_id; /* thread id used only for exit */
        int ghost_v_next; /* linked list of deleted slots, or -1 if slot in use */
    } ghost_impl_thread_slot_t;

    typedef struct {
        ghost_impl_thread_slot_t* ghost_impl_slots;
        ghost_size_t ghost_impl_count; /* used slots including deleted slots */
        ghost_size_t ghost_impl_capacity;
        int ghost_impl_deleted_first; /* index of first deleted slot, -1 if no deleted slots in count */
        ghost_size_t ghost_impl_deleted_count;
    } ghost_impl_thread_aux_t;

    #if ghost_has(ghost_selectany_var)
        ghost_selectany_var
    #elif !GHOST_EMIT_DEFS
        extern
    #endif
    ghost_impl_thread_aux_t ghost_impl_thread_aux
        #if GHOST_EMIT_DEFS
            = {
                ghost_null,
                0,
                0,
                -1,
                0
            }
        #endif
        ;

    /*
     * We protect the map with a global mutex. We initialize it statically if
     * we can; otherwise we use ghost_once().
     */

    #if ghost_has(ghost_selectany_var)
        ghost_selectany_var
    #elif !GHOST_EMIT_DEFS
        extern
    #endif
    ghost_mutex_t ghost_impl_thread_aux_mutex_s
        #if ghost_has(GHOST_MUTEX_INIT) && GHOST_EMIT_DEFS
            = GHOST_MUTEX_INIT
        #endif
        ;

    #if !ghost_has(GHOST_MUTEX_INIT)
        ghost_selectany_var ghost_once_t ghost_impl_thread_aux_mutex_once = GHOST_ONCE_INIT;

        ghost_impl_function
        void ghost_impl_thread_aux_mutex_once_init(void) GHOST_IMPL_DEF({
            ghost_mutex_init(&ghost_impl_thread_aux_mutex_s);
        })
    #endif

    ghost_impl_inline
    ghost_mutex_t* ghost_impl_thread_aux_mutex(void) {
        #if !ghost_has(GHOST_MUTEX_INIT)
            ghost_once(&ghost_impl_thread_aux_mutex_once, &ghost_impl_thread_aux_mutex_once_init);
        #endif
        return &ghost_impl_thread_aux_mutex_s;
    }

    /* helper function to remove a thread slot; don't call this */
    ghost_impl_function
    void ghost_impl_thread_aux_impl_remove_locked(int ghost_v_index) GHOST_IMPL_DEF({
        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_v_next =
                ghost_impl_thread_aux.ghost_impl_deleted_first;
        ghost_impl_thread_aux.ghost_impl_deleted_first = ghost_v_index;
        ++ghost_impl_thread_aux.ghost_impl_deleted_count;

        /* If all threads have been cleared, free the auxiliary storage. */
        if (ghost_impl_thread_aux.ghost_impl_count == ghost_impl_thread_aux.ghost_impl_deleted_count) {
            ghost_free(ghost_impl_thread_aux.ghost_impl_slots);
            ghost_impl_thread_aux.ghost_impl_count = 0;
            ghost_impl_thread_aux.ghost_impl_capacity = 0;
            ghost_impl_thread_aux.ghost_impl_deleted_first = -1;
            ghost_impl_thread_aux.ghost_impl_deleted_count = 0;
        }
    })

    /* helper function to assign a return value; don't call this */
    ghost_impl_function
    void ghost_impl_thread_aux_return_locked(int ghost_v_index, void* ghost_impl_return_value) GHOST_IMPL_DEF({
        ghost_assert(ghost_static_cast(ghost_size_t, ghost_v_index) < ghost_impl_thread_aux.ghost_impl_count, "invalid index");
        ghost_assert(!ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_returned, "thread has already returned");
        if (ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_detached) {
            ghost_impl_thread_aux_impl_remove_locked(ghost_v_index);
        } else {
            ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_ret = ghost_impl_return_value;
        }
    })

    /*
     * Add a thread to the map, returning its index.
     */
    ghost_impl_inline
    int ghost_impl_thread_aux_create(void) {
        int ghost_v_index;
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);

        /* see if we have a deleted slot */
        if (ghost_impl_thread_aux.ghost_impl_deleted_first != -1) {
            ghost_v_index = ghost_impl_thread_aux.ghost_impl_deleted_first;
            ghost_impl_thread_aux.ghost_impl_deleted_first =
                    ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_v_next;
            --ghost_impl_thread_aux.ghost_impl_deleted_count;

        } else {

            /* see if we need to grow */
            if (ghost_impl_thread_aux.ghost_impl_count == ghost_impl_thread_aux.ghost_impl_capacity) {
                ghost_impl_thread_slot_t* ghost_impl_new_slots;
                ghost_size_t ghost_impl_new_capacity = ghost_impl_thread_aux.ghost_impl_capacity * 2;
                if (ghost_impl_new_capacity < 8)
                    ghost_impl_new_capacity = 8;
                ghost_impl_new_slots = ghost_alloc_array(ghost_impl_thread_slot_t, ghost_impl_new_capacity);
                ghost_ensure(ghost_impl_new_slots != ghost_null, "Failed to allocate aux thread slots");
                ghost_memcpy(ghost_impl_new_slots, ghost_impl_thread_aux.ghost_impl_slots,
                        sizeof(ghost_impl_thread_slot_t) * ghost_impl_thread_aux.ghost_impl_capacity);
                ghost_free(ghost_impl_thread_aux.ghost_impl_slots);
                ghost_impl_thread_aux.ghost_impl_slots = ghost_impl_new_slots;
                ghost_impl_thread_aux.ghost_impl_capacity = ghost_impl_new_capacity;
            }

            ghost_v_index = ghost_static_cast(int, ghost_impl_thread_aux.ghost_impl_count++);
        }

        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_returned = false;
        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_detached = false;
        /* We don't assign the thread id yet because the thread hasn't started.
         * The thread will assign it on startup. */
        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_v_next = -1;

        ghost_mutex_unlock(ghost_impl_mutex);
        return ghost_v_index;
    }

    ghost_impl_inline
    void ghost_impl_thread_aux_assign_thread_id(int ghost_v_index) {
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);
        ghost_assert(ghost_static_cast(ghost_size_t, ghost_v_index) < ghost_impl_thread_aux.ghost_impl_count, "invalid index");
        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_returned = false;
        ghost_mutex_unlock(ghost_impl_mutex);
    }

    /*
     * Detach a thread in the map (or remove it if it has already exited.)
     */
    ghost_impl_inline
    void ghost_impl_thread_aux_detach(int ghost_v_index) {
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);
        ghost_assert(ghost_static_cast(ghost_size_t, ghost_v_index) < ghost_impl_thread_aux.ghost_impl_count, "invalid index");
        ghost_assert(!ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_detached, "thread already detached");
        if (ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_returned) {
            ghost_impl_thread_aux_impl_remove_locked(ghost_v_index);
        } else {
            ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_detached = true;
        }
        ghost_mutex_unlock(ghost_impl_mutex);
    }

    /*
     * Assign a return value to a thread in the map (or remove it if it was detached.)
     */
    ghost_impl_inline
    void ghost_impl_thread_aux_return(int ghost_v_index, void* ghost_impl_return_value) {
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);
        ghost_impl_thread_aux_return_locked(ghost_v_index, ghost_impl_return_value);
        ghost_mutex_unlock(ghost_impl_mutex);
    }

    /*
     * Assign a return value to the current thread in the map (or remove it
     * if it was detached.)
     */
    ghost_impl_inline
    void ghost_impl_thread_aux_exit(void* ghost_impl_return_value) {
        int ghost_v_index;
        int ghost_impl_v_count = ghost_static_cast(int, ghost_impl_thread_aux.ghost_impl_count);
        ghost_thread_id_t ghost_v_thread_id = ghost_thread_id_current();
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);

        /* find the thread via linear search */
        for (ghost_v_index = 0; ghost_v_index != ghost_impl_v_count; ++ghost_v_index) {
            if (ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_v_next == -1)
                continue;
            if (ghost_thread_id_equal(ghost_v_thread_id,
                        ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_v_thread_id))
                break;
        }
        ghost_ensure(ghost_v_index != ghost_impl_v_count, "Exiting thread not found");

        ghost_impl_thread_aux_return_locked(ghost_v_index, ghost_impl_return_value);
        ghost_mutex_unlock(ghost_impl_mutex);
    }

    /*
     * Join a thread that has already exited, removing it from the map and
     * returning its stored return value.
     */
    ghost_impl_inline
    void* ghost_impl_thread_aux_join(int ghost_v_index) {
        void* ghost_impl_return_value;
        ghost_mutex_t* ghost_impl_mutex = ghost_impl_thread_aux_mutex();
        ghost_mutex_lock(ghost_impl_mutex);
        ghost_impl_return_value = ghost_impl_thread_aux.ghost_impl_slots[ghost_v_index].ghost_impl_ret;
        ghost_impl_thread_aux_impl_remove_locked(ghost_v_index);
        ghost_mutex_unlock(ghost_impl_mutex);
        return ghost_impl_return_value;
    }

    GHOST_IMPL_FUNCTION_CLOSE

    #define ghost_has_ghost_impl_thread_aux 1
#endif

#endif
