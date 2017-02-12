/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "test.h++"

#include <core/event_loop.h++>

#include <thread>
#include <iostream>

namespace
{
  using skui::test::assert;

  int count = 0;
  void f() { ++count; }

  void test_event_loop()
  {
    skui::core::event_loop event_loop;

    std::thread thread(&skui::core::event_loop::execute, &event_loop);

    event_loop.push(std::make_unique<skui::core::command>(f));
    event_loop.push(std::make_unique<skui::core::command>(f));
    event_loop.push(std::make_unique<skui::core::command>(f));
    event_loop.stop();

    thread.join();

    assert(count == 3, "3 commands executed.");
  }
}

int main()
{
  test_event_loop();

  return skui::test::exit_code;
}