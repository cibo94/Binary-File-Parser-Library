//
// Created by onionka on 10/08/15.
//

#include <boost/test/unit_test.hpp>
#include <bfp.hpp>
#include "support.hpp"


BOOST_AUTO_TEST_SUITE(bfp_supp_functions)

      BOOST_AUTO_TEST_CASE(dereference_pointer_test)
        {
          char _c = 'a';
          char *a = &_c;
          char **b = &a;
          char ***c = &b;
          char ****d = &c;

          BOOST_CHECK(::bfp::dereference(a) == _c);
          BOOST_CHECK(::bfp::dereference(b) == _c);
          BOOST_CHECK(::bfp::dereference(c) == _c);
          BOOST_CHECK(::bfp::dereference(d) == _c);
        }

      BOOST_AUTO_TEST_CASE(find_in_string)
        {
          ::std::vector<::std::string> _strs{"text", "text2", "text3"};

          BOOST_MESSAGE(
              "finding ::std::string in ::std::vector<::std::string>");
          auto _founded = ::bfp::find(_strs.begin(), _strs.end(),
                                      ::std::string("text2"));
          BOOST_CHECK(_founded != _strs.end());
          BOOST_CHECK(*_founded == "text2");

          BOOST_MESSAGE("finding const char* in ::std::vector<::std::string>");
          _founded = ::bfp::find(_strs.begin(), _strs.end(), "text2");
          BOOST_CHECK(_founded != _strs.end());
          BOOST_CHECK(*_founded == "text2");

          BOOST_MESSAGE(
              "finding const char* in ::std::vector<::std::string> at the end of vector");
          _founded = ::bfp::find(_strs.begin(), _strs.end(), "text3");
          BOOST_CHECK(_founded != _strs.end());
          BOOST_CHECK(*_founded == "text3");
        }

      BOOST_AUTO_TEST_CASE(search_in_string)
        {
          ::std::vector<::std::string> _strs{
              "text", "text2", "text", "text3", "text"
          };

          BOOST_MESSAGE(
              "search: ::std::string in ::std::vector<::std::string>");
          auto _founded = ::bfp::search(_strs.begin(), _strs.end(),
                                        ::std::string("text"));
          BOOST_CHECK(_founded.size() == 3);
          for (auto _text : _founded)
            BOOST_CHECK(_text == "text");

          BOOST_MESSAGE("search: const char* in ::std::vector<::std::string>");
          _founded = ::bfp::search(_strs.begin(), _strs.end(), "text");
          BOOST_CHECK(_founded.size() == 3);
          for (auto _text : _founded)
            BOOST_CHECK(_text == "text");

          BOOST_MESSAGE(
              "search: const char* in ::std::vector<::std::string> at the end of vector");
          _founded = ::bfp::search(_strs.begin(), _strs.end(), "text3");
          BOOST_CHECK(_founded.size() == 1);
          for (auto _text : _founded)
            BOOST_CHECK(_text == "text3");
        }

      BOOST_AUTO_TEST_CASE(apply_on_string)
        {
          ::std::vector<::std::string> _strs{"text", "text", "text"};
          int i = 0;

          BOOST_MESSAGE(
              "apply: adding int at the end of each string in ::std::vector<::std::string>");
          ::bfp::apply(_strs.begin(), _strs.end(),
                       [&](::std::string &_str) -> void
                         {
                           _str += ::std::to_string(i++);
                         });
          i = 0;
          for (auto _str : _strs)
            {
              BOOST_CHECK(
                  _str == (::std::string("text") + ::std::to_string(i++)));
            }

          BOOST_MESSAGE("apply: checking return code of apply function");
          i = 0;
          int _ret = ::bfp::apply(_strs.begin(), _strs.end(), [](
              ::std::string &_str,
              int *_i) -> int
            {
              return (_str == "text2") ? ++(*_i) : 0;
            }, &i);
          BOOST_CHECK(_ret == i);
          BOOST_CHECK(_ret == 1);
        }

      BOOST_AUTO_TEST_CASE(filter_on_string)
        {
          ::std::vector<::std::string> _strs{
              "text", "text1", "text", "text", "text2", "text3"
          };

          BOOST_MESSAGE(
              "filter: ::std::vector<::std::string> with one lambda by reference");
          auto _founded = ::bfp::filter(_strs.begin(), _strs.end(),
                                        [](::std::string &_str) -> bool
                                          {
                                            return _str == "text";
                                          });
          BOOST_CHECK(_founded.size() == 3);
          for (auto _str : _founded)
            BOOST_CHECK(_str == "text");

          BOOST_MESSAGE(
              "filter: ::std::vector<::std::string> with two lambdas by reference");
          _founded = ::bfp::filter(_strs.begin(), _strs.end(),
                                   [](::std::string &_str) -> bool
                                     {
                                       return _str[0] == 't';
                                     }, [](::std::string &_str) -> bool
                                     {
                                       return _str.size() == 4;
                                     });
          BOOST_CHECK(_founded.size() == 3);
          for (auto _str : _founded)
            {
              BOOST_CHECK(_str == "text");
            }
        }

  BOOST_AUTO_TEST_SUITE_END()