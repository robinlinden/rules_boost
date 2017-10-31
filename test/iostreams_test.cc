#define BOOST_TEST_MODULE iostreams_test
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_iostreams )
{
  std::string uncompressed ("hello");
  std::string compressed;
  std::string expected ("\x1f\x8b\x08\x00\x00\x00\x00\x00\x04\xff\xcb\x48\xcd\xc9\xc9\x07\x00\x86\xa6\x10\x36\x05\x00\x00\x00", 25);

  boost::iostreams::filtering_ostream out;
  out.push(
      boost::iostreams::gzip_compressor(boost::iostreams::zlib::best_speed));
  out.push(boost::iostreams::back_inserter(compressed));
  boost::iostreams::write(out,
                          reinterpret_cast<const char*>(uncompressed.data()),
                          uncompressed.size());
  boost::iostreams::close(out);

  BOOST_TEST(compressed == expected);
}
