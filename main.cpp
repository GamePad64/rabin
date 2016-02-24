#include <cstdio>
#include "rabin.h"
#include <iostream>
#include <iomanip>
#include <cstring>

// 1MiB buffer
uint8_t buf[1024*1024];
size_t bytes;

int main() {
	std::unique_ptr<rabin_t> hasher = std::make_unique<rabin_t>();

    hasher->average_bits = 20;
    hasher->minsize = (512*1024);
    hasher->maxsize = (8*1024*1024);

    // Open a pull request if you need these to be configurable
    hasher->mask = ((1<<hasher->average_bits)-1);
    hasher->polynomial = 0x3DA3358B4DC173LL;
    hasher->polynomial_degree = 53;
    hasher->polynomial_shift = (hasher->polynomial_degree-8);

	rabin_init(hasher.get());

    unsigned int chunks = 0;

    while (!feof(stdin)) {
        size_t len = fread(buf, 1, sizeof(buf), stdin);
        uint8_t *ptr = &buf[0];

        bytes += len;

        while (1) {
            int remaining = rabin_next_chunk(hasher.get(), ptr, len);

            if (remaining < 0) {
                break;
            }

            len -= remaining;
            ptr += remaining;

	        std::ostringstream os;
	        os << hasher->chunk_length << " " << std::setfill('0') << std::setw(16) << std::hex << hasher->chunk_cut_fingerprint << std::endl;
	        std::cout << os.str();

            chunks++;
        }
    }

	if (rabin_finalize(hasher.get()) != 0) {
		std::ostringstream os;
		os << hasher->chunk_length << " " << std::setfill('0') << std::setw(16) << std::hex << hasher->chunk_cut_fingerprint << std::endl;
		std::cout << os.str();

		chunks++;
	}

    unsigned int avg = 0;
    if (chunks > 0)
        avg = bytes / chunks;
    printf("%d chunks, average chunk size %d\n", chunks, avg);

    return 0;
}
