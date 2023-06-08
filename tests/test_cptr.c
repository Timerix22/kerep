#include "tests.h"

const char* strings[]={
    "",
    "abab",
    "ab_ab",
    "abab_",
    "_abab",
    "_ab_ab_",
    "_ab_ab",
    "_abab_",
    "_ab_ab_",
    "str_not_containing_a_b",
    ""
};

#define test_startsWith(str, fragm) \
    kprintf("\e[37m'"str"' starts with '"fragm"'"); \
    if(cptr_startsWith(str,fragm)) kprintf("\e[92m true\n"); \
    else { kprintf("\e[91m false\n"); throw(ERR_UNEXPECTEDVAL); }

#define test_DoesntStartWith(str, fragm) \
    kprintf("\e[37m'"str"' doesnt start with '"fragm"'"); \
    if(!cptr_startsWith(str,fragm)) kprintf("\e[92m true\n"); \
    else { kprintf("\e[91m false\n"); throw(ERR_UNEXPECTEDVAL); }

#define test_endsWith(str, fragm) \
    kprintf("\e[37m'"str"' ends with '"fragm"'"); \
    if(cptr_endsWith(str,fragm)) kprintf("\e[92m true\n"); \
    else { kprintf("\e[91m false\n"); throw(ERR_UNEXPECTEDVAL); }

#define test_DoesntEndWith(str, fragm) \
    kprintf("\e[37m'"str"' doesnt end with '"fragm"'"); \
    if(!cptr_endsWith(str,fragm)) kprintf("\e[92m true\n"); \
    else { kprintf("\e[91m false\n"); throw(ERR_UNEXPECTEDVAL); }

#define test_seekChar(str, fragm, start, count, expected) \
    kprintf("\e[37mseek "#fragm" in '"str"' startIndex "#start" count "#count); \
    pos=cptr_seekChar(str, fragm, start, count); \
    if(pos == expected) kprintf("\e[92m %i\n", pos); \
    else { kprintf("\e[91m %i\n", pos); throw(ERR_UNEXPECTEDVAL); }

#define test_seekCharReverse(str, fragm, start, count, expected) \
    kprintf("\e[37mseek reverse "#fragm" in '"str"' startIndex "#start" count "#count); \
    pos=cptr_seekCharReverse(str, fragm, start, count); \
    if(pos == expected) kprintf("\e[92m %i\n", pos); \
    else { kprintf("\e[91m %i\n", pos); throw(ERR_UNEXPECTEDVAL); }

#define test_seek(str, fragm, start, count, expected) \
    kprintf("\e[37mseek '"fragm"' in '"str"' startIndex "#start" count "#count); \
    pos=cptr_seek(str, fragm, start, count); \
    if(pos == expected) kprintf("\e[92m %i\n", pos); \
    else { kprintf("\e[91m %i\n", pos); throw(ERR_UNEXPECTEDVAL); }

#define test_seekReverse(str, fragm, start, count, expected) \
    kprintf("\e[37mseek reverse '"fragm"' in '"str"' startIndex "#start" count "#count); \
    pos=cptr_seekReverse(str, fragm, start, count); \
    if(pos == expected) kprintf("\e[92m %i\n", pos); \
    else { kprintf("\e[91m %i\n", pos); throw(ERR_UNEXPECTEDVAL); }

const int strings_len=sizeof(strings)/sizeof(strings[0]);

void test_cptr(){
    optime(__func__,1,
        kprintf("\e[96m-------------[test_cptr]--------------\n");
        // compare
        kprintf("\e[94m--------------[compare]---------------\n");
        for(int i=0; i<strings_len-1; i++){
            // != next
            kprintf("\e[37m'%s'!='%s'", strings[i], strings[i+1]);
            bool not_eq= ! cptr_equals(strings[i],strings[i+1]);
            if(not_eq) kprintf("\e[92m true\n");
            else {
                kprintf("\e[91m false\n");
                throw(ERR_UNEXPECTEDVAL);
            }
            // == self
            kprintf("\e[37m'%s'=='%s'", strings[i], strings[i]);
            bool eq=cptr_equals(strings[i],strings[i]);
            if(eq) kprintf("\e[92m true\n");
            else {
                kprintf("\e[91m false\n");
                throw(ERR_UNEXPECTEDVAL);
            }
        }
        
        kprintf("\e[94m-------------[startsWith]-------------\n");
        test_startsWith("abab","ab");
        test_startsWith("abab","abab");
        test_DoesntStartWith("","");
        test_DoesntStartWith("abab","ababc");
        test_DoesntStartWith("abab","");
        test_DoesntStartWith("","abab");
        
        kprintf("\e[94m--------------[endsWith]--------------\n");
        test_endsWith("cab","ab");
        test_endsWith("abab","abab");
        test_DoesntEndWith("","");
        test_DoesntEndWith("abab","ababc");
        test_DoesntEndWith("abab","");
        test_DoesntEndWith("","abab");

        i32 pos=-1;
        kprintf("\e[94m--------------[seekChar]--------------\n");
        test_seekChar("", '\0', 0, -1, -1)
        test_seekChar("", 'u', 0, -1, -1)
        test_seekChar("ab", '\0', 0, -1, -1)
        test_seekChar("ab", 'u', 0, -1, -1)
        test_seekChar("ab", 'a', 0, -1, 0)
        test_seekChar("ab", 'b', 0, -1, 1)
        test_seekChar("ab", '\0', 0, 2, -1)
        test_seekChar("ab", 'b', 1, 2, 1)
        test_seekChar("ab", 'b', 1, 1, 1)
        
        kprintf("\e[94m----------[seekCharReverse]-----------\n");
        test_seekCharReverse("", 'u', 0, -1, -1)
        test_seekCharReverse("ab", 'u', 0, -1, -1)
        test_seekCharReverse("ab", 'a', 0, -1, 0)
        test_seekCharReverse("ab", 'b', 1, -1, 1)
        test_seekCharReverse("ab", 'a', -1, -1, 0)
        test_seekCharReverse("ab", 'b', -1, -1, 1)
        test_seekCharReverse("ab", '\0', -1, -1, -1)
        test_seekCharReverse("ab", '\0', 2, 2, -1)
        test_seekCharReverse("ab", 'b', 1, 2, 1)
        test_seekCharReverse("ab", 'b', 1, 1, 1)
        
        kprintf("\e[94m----------------[seek]----------------\n");
        test_seek("", "", 0, -1, -1)
        test_seek("", "u", 0, -1, -1)
        test_seek("ab", "", 0, -1, -1)
        test_seek("ab", "u", 0, -1, -1)
        test_seek("ab", "a", 0, -1, 0)
        test_seek("ab", "b", 0, -1, 1)
        test_seek("ab", "ab", 0, -1, 0)
        test_seek("ab_ab", "ab", 0, -1, 0)
        test_seek("ab_ab", "ab", 1, -1, 3)
        test_seek("ab_ab", "ab", 1, 5, 3)
        test_seek("ab_ab", "ab", 1, 4, -1)
        
        kprintf("\e[94m------------[seekReverse]-------------\n");
        test_seekReverse("", "u", 0, -1, -1)
        test_seekReverse("ab", "u", 0, -1, -1)
        test_seekReverse("ab", "a", 0, -1, 0)
        test_seekReverse("ab", "b", 1, -1, 1)
        test_seekReverse("ab", "a", -1, -1, 0)
        test_seekReverse("ab", "b", -1, -1, 1)
        test_seekReverse("ab", "", -1, -1, -1)
        test_seekReverse("ab", "", 2, 2, -1)
        test_seekReverse("ab", "b", 1, 2, 1)
        test_seekReverse("ab", "b", 1, 1, 1)

        // TODO cptr_replace
    );
}
