#!/bin/bash

if [ ! -f "parser" ]; then
    make
fi

./parser <test/test.in >test/test_your.out # output your answer
diff test/test.out test/test_your.out

./parser <test/test1.in >test/test_your1.out # output your answer
diff test/test1.out test/test_your1.out
