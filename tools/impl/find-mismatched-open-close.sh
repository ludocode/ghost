#!/bin/sh
A=$(mktemp)
B=$(mktemp)

echo GHOST_IMPL_CXX_FUNCTION_OPEN
grep -lr GHOST_IMPL_CXX_FUNCTION_OPEN include/ | sort > $A
grep -lr GHOST_IMPL_CXX_FUNCTION_CLOSE include/ | sort > $B
diff $A $B

echo GHOST_IMPL_FUNCTION_OPEN
grep -lr GHOST_IMPL_FUNCTION_OPEN include/ | sort > $A
grep -lr GHOST_IMPL_FUNCTION_CLOSE include/ | sort > $B
diff $A $B

echo GHOST_EXTERN_C_PUSH
grep -lr GHOST_EXTERN_C_PUSH include/ | sort > $A
grep -lr GHOST_EXTERN_C_POP include/ | sort > $B
diff $A $B

rm $A $B
