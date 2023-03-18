/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Assert.hpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

//
// Definitions
//

#ifdef NDEBUG

#define Assert(condition, message) 0
#define Unreachable(message)       0
#define Assert(condition)          0

#else

#include <string>
namespace Common::Internal
{
int
AssertMsgFailure(char const* file,
                 int         line,
                 char const* func,
                 std::string message);

int
UnreachableFailure(char const* file,
                   int         line,
                   char const* func,
                   std::string message);

}  // namespace Common::Internal

#if defined __cplusplus
#define __J_ASSERT_FN __PRETTY_FUNCTION__
#else
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#define __JULES_ASSERT_FUNCTION __func__
#else
#define __JULES_ASSERT_FUNCTION ((const char*)0)
#endif
#endif

#define Assert(condition)                                            \
    ((condition)                                                     \
         ? 0                                                         \
         : Common::Internal::AssertMsgFailure(                       \
               __FILE__, __LINE__, __J_ASSERT_FN, #condition))

#define AssertMsg(condition, message)                                \
    ((condition) ? 0                                                 \
                 : Common::Internal::AssertMsgFailure(               \
                       __FILE__, __LINE__, __J_ASSERT_FN, message))

#define Unreachable()                                                \
    Common::Internal::UnreachableFailure(                            \
               __FILE__, __LINE__, __J_ASSERT_FN, "")

#define UnreachableMsg(message)                                      \
    Common::Internal::UnreachableFailure(                            \
                       __FILE__, __LINE__, __J_ASSERT_FN, message)

#endif