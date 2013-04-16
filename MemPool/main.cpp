/**
* memcached memory management
*/

#include <stdlib.h>
#include <iostream>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

using namespace std;

#define ITEM_SLABBED 4

#define ITEM_FETCHED 8

#define default_size 48
#define POWER_LARGEST 200
#define max_slabclass_number  (POWER_LARGEST + 1)
#define CHUNK_ALIGN_BYTES 8

static unsigned int MAX_SIZE = 1048576;

static size_t mem_limit = 0;
static size_t mem_malloced = 0;
static int power_largest;

static void * mem_base = NULL;
static void * mem_current = NULL;
static size_t mem_avail = 0;

typedef struct _item {
    struct _item *next;
    struct _item *prev;
    struct _item *h_next;   /*hash chain next*/

    unsigned int time;      /*least recent access*/
    unsigned int exptime;   /*expire time*/
    int nbytes;             /*size of data*/
    unsigned short refcount;
    uint8_t nsuffix;        /*length of flags-and-length string*/
    uint8_t it_flags;       /*ITEM_* above*/
    uint8_t slabs_clid;     /*slab class id*/
    uint8_t nkey;           /*key length w/terminating null and padding*/
    /*?why data write like this?*/
    union {
        uint64_t cas;
        char end;
    } data[];
} item;

typedef struct {
    unsigned int size;      /*size of items*/
    unsigned int perslab;   /*how many items per slab*/

    void *slots;            /*list of items ptrs*/
    unsigned int sl_curr;   /*total free items in list*/

    unsigned int slabs;     /*how many slabs were allocated for this class*/

    void **slab_list;       /*array of slab pointers*/
    unsigned int list_size; /*size of prev array?????*/

    unsigned int killing;   /*index+1 of dying slab, or zero if none*/
    size_t  requested;      /*the number of request bytes*/
} slabclass_t;

static slabclass_t slabclass[max_slabclass_number];

static int grow_slab_list(const unsigned int id) {
    slabclass_t *p = &slabclass[id];
    if (p->slabs == p->list_size) {
        size_t newsize = (p->list_size != 0) ? p->list_size * 2 : 16;
        void *newlist = realloc(p->slab_list, newsize * sizeof(void *));
        if (newlist == NULL)
            return 0;
        p->list_size = newsize;
        p->slab_list = &newlist;
    }
    return 1;
}

static void * memory_allocate(size_t size) {
    void *ret;
    if(mem_base == NULL) {
        ret = malloc(size);
    } else {
        ret = mem_current;
        if (size > mem_avail) {
            return NULL;
        }
        if(size % CHUNK_ALIGN_BYTES)
            size += CHUNK_ALIGN_BYTES - (size % CHUNK_ALIGN_BYTES);
        mem_current = (char *) mem_current + size;
        mem_avail -= size;
    }
    return ret;
}

static void do_slabs_free(const void *ptr, const size_t size, const size_t id) {
    assert(((item *)ptr)->slabs_clid == 0);
    assert(id >= 1 && id <= power_largest);

    slabclass_t *p = &slabclass[id];
    item *it = (item *)ptr;
    it->it_flags = ITEM_SLABBED;
    it->prev = 0;
    it->next = (item *)p->slots;
    if(it->next) it->next->prev = it;
    p->slots = it;

    p->sl_curr++;
    p->requested -= size;
    return;
}

static void split_slab_page_into_freelist(const char *ptr, const size_t id) {
    slabclass_t *p = &slabclass[id];
    int i;
    for(i=0; i<p->perslab; i++) {
        do_slabs_free(ptr, 0, id);
        ptr += p->size;
    }
}

static int slabs_newslab(const int index) {
    slabclass_t *ptr = &slabclass[index];
    int len = ptr->size * ptr->perslab;
    char *p;
    if ((mem_limit && mem_malloced + len > mem_limit && ptr->slabs > 0) ||
        (grow_slab_list(index) == 0) ||
        ((p = (char *)memory_allocate(size_t(len))) == 0)
        ) {
            cerr << "slabs id: " << index << "alloc error!" << endl;
            return 0;
    }
    memset(p, 0, (size_t)len);
    split_slab_page_into_freelist(p, index);

    ptr->slab_list[ptr->slabs++] = p;
    mem_malloced += len;
    return 1;
}

static void slabs_preallocate(const int maxslabs) {
    int i;
    unsigned int prealloc = 0;
    for(i=1; i<=POWER_LARGEST; i++) {
        if(++prealloc > maxslabs)
            return;
        slabs_newslab(i);
    }
}

void slabs_init(const size_t limit, const double factor) {
    unsigned int size = sizeof(item) + default_size;
    /*init memory*/
    mem_limit = limit;
    mem_base = malloc(limit);
    if (mem_base != NULL) {
        mem_current = mem_base;
        mem_avail = mem_limit;
    } else {
        cerr << "error when init the mem_base" <<endl;
    }
    memset(slabclass, 0, sizeof(slabclass));
    int i = 0;
    while((++i < POWER_LARGEST)
        && (size <= (MAX_SIZE / factor))) {
        if (size % CHUNK_ALIGN_BYTES)
            size += CHUNK_ALIGN_BYTES - (size % CHUNK_ALIGN_BYTES);
        slabclass[i].size = size;
        slabclass[i].perslab = MAX_SIZE / size;
        size *= factor;
    }
    power_largest = i;
    slabclass[power_largest].size = MAX_SIZE;
    slabclass[power_largest].perslab = 1;

    /*pre alloc memory*/
    slabs_preallocate(power_largest);
}

int main()
{
    //cout << "Hello world!" << endl;
    cout << sizeof(item) << endl;
    item a;
    memset(&a, 0, sizeof(item));
    cout << sizeof(a) << endl;
    slabs_init(60*1024*1024, 1.25);
    for(int i=1; i<power_largest; i++) {
        cout << "total free :" << slabclass[i].sl_curr << "total item :"
        << slabclass[i].perslab << "item size :" << slabclass[i].size << endl;
    }
    return 0;
}
