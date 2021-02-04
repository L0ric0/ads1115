// ads1115++
#include "ads1115++/fileno.hpp"

// gtest
#include <gtest/gtest.h>

// stl
#include <fstream>
#include <iostream>
#include <sstream>

TEST(Fileno, SyncStdioStreamsCIn)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::cin);
    ASSERT_EQ(fd, 0);
}

TEST(Fileno, SyncStdioStreamsCOut)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::cout);
    ASSERT_EQ(fd, 1);
}

TEST(Fileno, SyncStdioStreamsCErr)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::cerr);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, SyncStdioStreamsCLog)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::clog);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, SyncStdioWStreamsCIn)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::wcin);
    ASSERT_EQ(fd, 0);
}

TEST(Fileno, SyncStdioWStreamsCOut)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::wcout);
    ASSERT_EQ(fd, 1);
}

TEST(Fileno, SyncStdioWStreamsCErr)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::wcerr);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, SyncStdioWStreamsCLog)
{
    std::ios_base::sync_with_stdio(true);
    int fd = fileno(std::wclog);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, StreamsCIn)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::cin);
    ASSERT_EQ(fd, 0);
}

TEST(Fileno, StreamsCOut)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::cout);
    ASSERT_EQ(fd, 1);
}

TEST(Fileno, StreamsCErr)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::cerr);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, StreamsCLog)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::clog);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, WStreamsCIn)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::wcin);
    ASSERT_EQ(fd, 0);
}

TEST(Fileno, WStreamsCOut)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::wcout);
    ASSERT_EQ(fd, 1);
}

TEST(Fileno, WStreamsCErr)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::wcerr);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, WStreamsCLog)
{
    std::ios_base::sync_with_stdio(false);
    int fd = fileno(std::wclog);
    ASSERT_EQ(fd, 2);
}

TEST(Fileno, IFStream)
{
    int fd = fileno(std::ifstream("/dev/zero"));
    ASSERT_EQ(fd, 4);
}

TEST(Fileno, OFStream)
{
    int fd = fileno(std::ofstream("/dev/zero"));
    ASSERT_EQ(fd, 4);
}

TEST(Fileno, StringStream)
{
    int fd = fileno(std::stringstream());
    ASSERT_EQ(fd, -1);
}

TEST(Fileno, WIFStream)
{
    int fd = fileno(std::wifstream("/dev/zero"));
    ASSERT_EQ(fd, 4);
}

TEST(Fileno, WOFStream)
{
    int fd = fileno(std::wofstream("/dev/zero"));
    ASSERT_EQ(fd, 4);
}

TEST(Fileno, WStringStream)
{
    int fd = fileno(std::wstringstream());
    ASSERT_EQ(fd, -1);
}
