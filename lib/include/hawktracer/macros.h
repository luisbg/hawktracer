#ifndef HAWKTRACER_MACROS_H
#define HAWKTRACER_MACROS_H

#define HT_UNUSED(x) (void)(x)

#ifdef __cplusplus
#  define HT_DECLS_BEGIN  extern "C" {
#  define HT_DECLS_END    }
#else
#  define HT_DECLS_BEGIN
#  define HT_DECLS_END
#endif

#if __cplusplus >= 201103L
#  define HT_CPP11
#endif

#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#  define HT_LIKELY(expr) (__builtin_expect ((expr), 1))
#  define HT_UNLIKELY(expr) (__builtin_expect ((expr), 0))
#else
#  define HT_LIKELY(expr) (expr)
#  define HT_UNLIKELY(expr) (expr)
#endif

#ifndef __cplusplus
#  ifdef _MSC_VER
#    if (_MSC_VER < 1900)
#      define inline __inline
#    endif
#    elif !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199900)
#      define inline __inline
#    endif
#endif

#ifdef _WIN32
#  define HT_PLATFORM_WIN32
#endif

#ifdef HT_PLATFORM_WIN32
#  if defined(HT_COMPILE_SHARED_EXPORT)
#    define HT_API __declspec(dllexport)
#  else
#    define HT_API __declspec(dllimport)
#  endif
#else
#  define HT_API
#endif

#endif /* HAWKTRACER_MACROS_H */
