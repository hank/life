#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <sstream>

#define ALLOC_BYTES 1024

int main(int argc, char** argv)
{
    namespace ip = boost::interprocess;
    ip::managed_shared_memory segment(ip::open_only, "Erik");
    ip::managed_shared_memory::handle_t handle = 0;
    std::stringstream s;
    s << argv[1];
    s >> handle;
    void* message = segment.get_address_from_handle(handle);
    printf("Message: %s\n", (char*)message);
    segment.deallocate(message);
    return EXIT_SUCCESS;
}
