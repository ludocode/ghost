#!/bin/bash
cd $(dirname $0)/../../include/ghost/type

doit() {
    from=${1}t
    to=${2}t
    bits=$3

    rm -r $to
    cp -r $from $to
    cp ghost_${1}all.h ghost_${2}all.h
    perl-rename "s/32/$bits/" $to/*
    for f in ghost_${2}all.h $to/*; do sed -i "s/32/$bits/g" $f; done

    if [ "$bits" = 8 ]; then
        for f in $to/*; do sed -i "s/2147483648/128/g" $f; done
        for f in $to/*; do sed -i "s/2147483647/127/g" $f; done
        for f in $to/*; do sed -i "s/4294967295/255/g" $f; done
    elif [ "$bits" = 16 ]; then
        for f in $to/*; do sed -i "s/2147483648/32768/g" $f; done
        for f in $to/*; do sed -i "s/2147483647/32767/g" $f; done
        for f in $to/*; do sed -i "s/4294967295/65535/g" $f; done
    elif [ "$bits" = 64 ]; then
        for f in $to/*; do sed -i "s/2147483648/9223372036854775808/g" $f; done
        for f in $to/*; do sed -i "s/2147483647/9223372036854775807/g" $f; done
        for f in $to/*; do sed -i "s/4294967295/18446744073709551615/g" $f; done
    fi
}

doit int32_ int8_ 8
doit int32_ int16_ 16
doit int32_ int64_ 64
doit uint32_ uint8_ 8
doit uint32_ uint16_ 16
doit uint32_ uint64_ 64
doit int_least32_ int_least8_ 8
doit int_least32_ int_least16_ 16
doit int_least32_ int_least64_ 64
doit uint_least32_ uint_least8_ 8
doit uint_least32_ uint_least16_ 16
doit uint_least32_ uint_least64_ 64
