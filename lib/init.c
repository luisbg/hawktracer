#include "hawktracer/init.h"

#include "internal/timeline_registry.h"

#include "hawktracer/timeline.h"
#include "hawktracer/callstack_base_timeline.h"
#include "hawktracer/alloc.h"

void
ht_init(int argc, char** argv)
{
    /* For future use */
    HT_UNUSED(argc);
    HT_UNUSED(argv);

    ht_timeline_registry_register(
                "simple_ts", sizeof(HT_Timeline), HT_TRUE, HT_FALSE,
                ht_timeline_init, ht_timeline_deinit);

    ht_timeline_registry_register(
                "callstack", sizeof(HT_CallstackBaseTimeline), HT_FALSE, HT_TRUE,
                ht_callstack_base_timeline_init, ht_callstack_base_timeline_deinit);
}

void ht_deinit(void)
{
    ht_timeline_registry_unregister_all();
}