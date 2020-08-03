#include "library.h"
#include "yam.h"

#include <cmath>

void *afl_custom_init (afl_t *afl, unsigned int seed)
{
  srand(seed);
  yam *y = new yam;

  return y;
}

int rand_in_range (int min, int max);

size_t
afl_custom_fuzz (void *data, uint8_t *buf, size_t buf_size, uint8_t **out_buf, uint8_t *add_buf, size_t add_buf_size, size_t max_size)
{
  yam *y = reinterpret_cast<yam *>(data);

  y->set_buffer(buf, buf_size);

  if (!y->has_ehdr ())
    {
      *out_buf = nullptr;
      return 0;
    }

    if (y->has_shdr ())
      {
        int r = rand_in_range(0, 2);
        if (r == 0)
          y->mutate_elf_header();
        else
          y->mutate_section_header();
      }
    else
      y->mutate_elf_header();

  *out_buf = buf;
  return buf_size;
}

void afl_custom_deinit (void *data)
{
  delete reinterpret_cast<yam *>(data);
}
