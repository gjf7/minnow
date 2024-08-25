#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buffer_() {}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( string data )
{
  if ( !available_capacity() || has_error() || is_closed() )
    return;

  size_t len = min(available_capacity(), data.length());
  buffer_ += data.substr(0, len);
  bytes_pushed_ += len;
}

void Writer::close()
{
  set_closed();
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.length();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  return writer().is_closed() && buffer_.empty();
}


uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}

string_view Reader::peek() const
{
  return buffer_;
}

void Reader::pop( uint64_t len )
{
  if (buffer_.empty())
    return;

  size_t pop_len = min(len, buffer_.length());
  buffer_.erase(0, pop_len);
  bytes_popped_ += pop_len;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}

