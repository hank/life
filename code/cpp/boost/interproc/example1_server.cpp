#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <sstream>

#define ALLOC_BYTES 1024

int main()
{
    namespace ip = boost::interprocess;
    struct shm_remove
    {
        shm_remove()
        {
            ip::shared_memory_object::remove("Erik");
        }
        ~shm_remove()
        {
            ip::shared_memory_object::remove("Erik");
        }
    } remover;
    ip::managed_shared_memory segment(ip::create_only, "Erik", 32768);
    std::size_t free_memory = segment.get_free_memory();
    void* shptr = segment.allocate(ALLOC_BYTES);

    if(free_memory <= segment.get_free_memory())
    {
        return EXIT_FAILURE;
    }

    strcpy((char*)shptr, "Manatees!");
    ip::managed_shared_memory::handle_t handle =
        segment.get_handle_from_address(shptr);
    std::cout << "Handle is " << handle << std::endl;
    pause();
    return EXIT_SUCCESS;
}
