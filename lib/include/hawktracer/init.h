#ifndef HAWKTRACER_INIT_H
#define HAWKTRACER_INIT_H

#include <hawktracer/macros.h>

HT_DECLS_BEGIN

HT_API void ht_init(int argc, char** argv);

HT_API void ht_deinit(void);

HT_DECLS_END

#endif /* HAWKTRACER_INIT_H */
