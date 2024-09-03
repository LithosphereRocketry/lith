#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "lith/print.hpp"
#include "lith/test.hpp"

using namespace lith::print;

int main(int, char**) {
    try {
        {
            lith::test::testcase tc("dont_break_char*");
            std::ostringstream s;
            char mcarr[] = "ab";
            const char ccarr[] = "cd";
            char* mcptr = mcarr;
            const char* ccptr = ccarr;
            s << mcarr << ccarr << mcptr << ccptr;
            tc.assertEqual(s.str(), "abcdabcd");
        }
        {
            lith::test::testcase tc("dont_break_str");
            std::ostringstream s;
            std::string str = "ab";
            s << str;
            tc.assertEqual(s.str(), "ab");
        }
        {
            lith::test::testcase tc("pair");
            std::ostringstream s;
            std::pair<int, std::string> p(3, "test");
            s << p;
            tc.assertEqual(s.str(), "<3 : test>");
        }
        {
            lith::test::testcase tc("vector");
            std::vector<int> v = {};

            std::ostringstream s_empty;
            s_empty << v;
            tc.assertEqual(s_empty.str(), "[]", "Wrong output on empty vector");

            v.push_back(1);
            std::ostringstream s_single;
            s_single << v;
            tc.assertEqual(s_single.str(), "[1]", "Wrong output on single-element vector");

            v.push_back(2);
            std::ostringstream s_two;
            s_two << v;
            tc.assertEqual(s_two.str(), "[1, 2]", "Wrong output on multi-element vector");   
        }
        {
            lith::test::testcase tc("map");
            std::map<int, std::string> m;
            m[1] = "one";
            m[2] = "two";
            m[3] = "three";
            std::ostringstream s;
            s << m;
            tc.assertEqual(s.str(), "[<1 : one>, <2 : two>, <3 : three>]");
        }
        {
            lith::test::testcase tc("nested");
            std::vector<std::vector<int>> v = {{1, 2}, {3, 4}};
            std::ostringstream s;
            s << v;
            tc.assertEqual(s.str(), "[[1, 2], [3, 4]]");
        }
    } catch(const lith::test::test_failed& f) {
        std::cout << "Test failed: " << f.what() << "\n";
        return -1;
    }
}