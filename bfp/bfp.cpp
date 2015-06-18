/** Binary File Parser
 * @file bfp.cpp
 * @author Miroslav Cibulka
 * @brief TODO
 */

#include "bfp.hpp"

namespace BFP {
    BFD *BFD::get_unique_instance() {
        static BFD *instance = nullptr;
        if (instance == nullptr) {
            instance = new BFD();
        }
        return instance;
    }

    void BFD::Open(const char *_file_name, const char *_target) {
        if ((fd = bfd_openr(_file_name, _target)) == NULL)
            RAISE(::BFP::Exception::Opening);
    }

    BFD::~BFD() {
        if (!bfd_close(fd)) {
            RAISE(::BFP::Exception::Closing);
        }
    }

    BFD::BFD() {
        bfd_init();
    }
}