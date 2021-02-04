// ads1115++
#include "ads1115++/fileno.hpp"

// stl
#include <cerrno>
#include <cstdio>
#include <fstream>

// gcc
#include <ext/stdio_filebuf.h>
#include <ext/stdio_sync_filebuf.h>

/*! Similar to fileno(3), but taking a C++ stream as argument instead of a
 * FILE*.  Note that there is no way for the library to track what you do with
 * the descriptor, so be careful.
 * \return  The integer file descriptor associated with the stream, or -1 if
 *   that stream is invalid.  In the latter case, for the sake of keeping the
 *   code as similar to fileno(3), errno is set to EBADF.
 * \see  The <A HREF="https://www.ginac.de/~kreckel/fileno/">upstream page at
 *   https://www.ginac.de/~kreckel/fileno/</A> of this code provides more
 *   detailed information.
 */
template <typename charT, typename traits>
int fileno_hack(const std::basic_ios<charT, traits>& stream)
{

    // This applies to cin, cout and cerr when not synced with stdio:
    typedef __gnu_cxx::stdio_filebuf<charT, traits> unix_filebuf_t;
    unix_filebuf_t* fbuf = dynamic_cast<unix_filebuf_t*>(stream.rdbuf());
    if (fbuf != nullptr) {
        return fbuf->fd();
    }

    // This applies for filestreams:
    typedef std::basic_filebuf<charT, traits> filebuf_t;
    filebuf_t* bbuf = dynamic_cast<filebuf_t*>(stream.rdbuf());
    if (bbuf != nullptr) {
        // This subclass is only there for accessing the FILE*.
        struct my_filebuf : public std::basic_filebuf<charT, traits> {
            int fd()
            {
                return this->_M_file.fd();
            }
        };
        return static_cast<my_filebuf*>(bbuf)->fd();
    }

    // This applies to cin, cout and cerr when synced with stdio:
    typedef __gnu_cxx::stdio_sync_filebuf<charT, traits> sync_filebuf_t;
    sync_filebuf_t* sbuf = dynamic_cast<sync_filebuf_t*>(stream.rdbuf());
    if (sbuf != nullptr) {
        return ::fileno(sbuf->file());
    }

    errno = EBADF;
    return -1;
}

//! 8-Bit character instantiation: fileno(ios)
template <>
int fileno<char>(const std::ios& stream)
{
    return fileno_hack(stream);
}

//! Wide character instantiation: fileno(wios).
template <>
int fileno<wchar_t>(const std::wios& stream)
{
    return fileno_hack(stream);
}
