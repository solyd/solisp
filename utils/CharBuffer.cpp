#include "CharBuffer.h"

#include <algorithm>

#include "BufferUnderflowException.h"

namespace utils {

CharBuffer::CharBuffer(const std::string& str) : m_str(&str), m_pos(0) {}

CharBuffer::CharBuffer(const char *str) : m_str(new std::string(str)), m_pos(0) {}

const char& CharBuffer::read() {
  assert_has_remaining();
  return m_str->at(m_pos++);
}

const char& CharBuffer::peek() const {
  assert_has_remaining();
  return m_str->at(m_pos);
}

void CharBuffer::set_position(size_t pos) {
  if (pos > m_str->length())
    throw BufferUnderflowException();

  m_pos = pos;
}

size_t CharBuffer::remaining() const {
  return m_str->length() - m_pos;
}

size_t CharBuffer::position() const {
  return m_pos;
}

void CharBuffer::skip_whitespace() {
  m_pos = (size_t)
      (std::find_if(m_str->begin() + m_pos, m_str->end(),
                   std::not1(std::ptr_fun<int, int>(std::isspace)))
       - m_str->begin());
}

const std::string& CharBuffer::get_str() const {
  return *m_str;
}

std::string CharBuffer::get_remaining_str() const {
  return m_str->substr(m_pos, m_str->length());
}

void CharBuffer::assert_has_remaining() const {
  if (!has_remaining())
    throw BufferUnderflowException();
}

}


