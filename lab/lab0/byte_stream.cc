#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity), num_written(0), num_read(0), _error(false) { }


size_t ByteStream::write(const string &data) {
    size_t free_space = _capacity - (num_written - num_read);
    size_t num = (free_space > data.size() ? data.size() : free_space);

    for (size_t i = 0; i < num; i++)
        buffer.push_back(data[i]);

    num_written += num;

    return num;
}


string ByteStream::peek_output(const size_t len) const { 
    size_t num = (len > (num_written - num_read)) ? (num_written - num_read) : len;
    string output;

    output.assign(buffer.begin(), buffer.begin() + num);

    return output;
}


void ByteStream::pop_output(const size_t len) { 
    size_t num = (len > buffer.size()) ? buffer.size() : len;

    for (size_t i = 0; i < num; i++)
        buffer.pop_front();

    num_read += len;
}


string ByteStream::read(const size_t len) {
    size_t num = (len > buffer.size()) ? buffer.size() : len;

    auto output = peek_output(num);
    pop_output(num);

    return output;
}


void ByteStream::end_input() { stream_end = true; }

bool ByteStream::input_ended() const { return stream_end; }

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { return buffer.size() == 0; }

bool ByteStream::eof() const {return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return num_written; }

size_t ByteStream::bytes_read() const { return num_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - (num_written - num_read); }
