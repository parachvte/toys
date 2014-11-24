/**
 * Problem  : KMP Algorithm
 * Link     : http://hihocoder.com/contest/hiho3/problem/1
 * Author   : Ryannnnnnn
 * Date     : July 20, 2014
 * Note     :
 *  受到HihoCoder的邮件，于是来做个题（哎发觉太久不写都不会KMP了）。
 *  稍微记录一下，免得以后想找个自己看得懂的KMP模板都找不到...
 */
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_LENGTH 10000

int testCaseN;
string pattern, testString;
int lastMatch[MAX_LENGTH + 1]; // the next array

int doKMPCount(string pattern, string testString) {
    int len = pattern.length();
    lastMatch[0] = -1;                              // initialize, p[0] -> -1 never match any position
    for (int i = 0, j = -1; i < len; )
        if (j == -1 || pattern[i] == pattern[j])    // while pattern is not started, or matches p[i] and p[j]
            lastMatch[++i] = ++j;
        else
            j = lastMatch[j];                       // jump back to last match position

    int lenTestString = testString.length();
    int matches = 0;
    for (int i = 0, j = 0; i < lenTestString; ) {   // start matching the `testString`, start with j = 0
        if (j == -1 || testString[i] == pattern[j]) // the same as above
            ++i, ++j;
        else
            j = lastMatch[j];
        if (j == len) matches ++, j = lastMatch[j]; // `pattern` is fully matched, `j` jump back to last match position and go on
                                                    // here (i - len) is the start position of testString that matches the pattern
    }
    return matches;
}

int main() {
    cin >> testCaseN;
    while (testCaseN --) {
        cin >> pattern;
        cin >> testString;
        cout << doKMPCount(pattern, testString) << endl;
    }
    return 0;
}
