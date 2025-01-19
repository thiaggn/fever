
struct rsc_text {
    char *bytes;
    size_t size;
};

struct rsc_image {
    unsigned char *bytes;
    int width, height, channel_count;

    void release();
};

struct rsc_text rsc_read_text(const char *path);

struct rsc_image rsc_read_image(const char *path);
