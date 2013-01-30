/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <cstdio> // for printf
#include <iostream> // for std::cin.get

#include <Scratch.h>

static INDEX _ctTests = 0;
static INDEX _ctFailed = 0;

#define TEST(expr) {                            \
  BOOL bSuccess = (expr);                       \
  _ctTests++;                                   \
  ASSERT(bSuccess);                             \
  printf("  Test #%d: (%s) ", _ctTests, #expr); \
  if(!bSuccess) {                               \
    _ctFailed++;                                \
    printf("FAILED!\n");                        \
  } else {                                      \
    printf("OK\n");                             \
  }                                             \
}

/// String testing
void TestString()
{
  printf("Testing strings\n");

  CString strTest;
  strTest += "Lib";
  strTest += "Scratch";
  strTest = strTest.ToLower();
  TEST(strTest == "libscratch");

  strTest += " is great";
  CStackArray<CString> astrParse = strTest.Split(" ");
  TEST(astrParse[2] == "great");
  TEST(astrParse[2][1] == 'r');

  CString strTest2 = strTest.Replace("great", "cool");
  TEST(strTest2 == "libscratch is cool");
}

/// Stack array testing
void TestStackArray()
{
  printf("Testing stack arrays\n");

  CStackArray<INDEX> aiNumbers;
  TEST(aiNumbers.Count() == 0);

  aiNumbers.Push() = 5;
  aiNumbers.Push() = 10;
  aiNumbers.Push() = 15;
  TEST(aiNumbers.Count() == 3);
  TEST(aiNumbers[0] == 5);
  TEST(aiNumbers[1] == 10);
  TEST(aiNumbers[2] + aiNumbers[0] == 20);

  TEST(aiNumbers.Pop() == 15);
  TEST(aiNumbers.Count() == 2);
}

/// Dictionary testing
void TestDictionary()
{
  printf("Testing dictionary\n");

  CDictionary<CString, INDEX> diTest;
  TEST(!diTest.HasKey("Test"));

  diTest["Test"] = 100;
  diTest["Test2"] = 200;
  TEST(diTest.HasKey("Test"));
  TEST(diTest["Test"] == 100);

  diTest.RemoveByKey("Test");
  TEST(diTest.Count() == 1);
  TEST(!diTest.HasKey("Test"));
}

int main()
{
  // perform tests
  TestString();
  TestStackArray();
  TestDictionary();

  // report test results
  printf("\n\nResults: %d out of %d went OK.\n\n", _ctTests - _ctFailed, _ctTests);

  // check if all went OK
  if(_ctFailed == 0) {
    // it did! no failures. :)
    printf("All OK!\n");
  } else {
    // oops, there's a bug somewhere. please report!
    printf("Some problems seem to have popped up. Please report a bug.\n");
  }

  std::cin.get();
  return 0;
}
