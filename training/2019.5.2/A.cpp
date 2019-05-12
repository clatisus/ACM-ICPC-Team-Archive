//
// Created by nonsensetime on 19-5-2.
//

#include <bits/stdc++.h>

std::vector<std::string> words;

bool iscapital(const std::string &word) {
    if (word.length() < 2) return false;
    if (!isupper(word[0])) return false;
    for (int i = 1; i < word.length(); ++i) {
        if (!islower(word[i])) return false;
    }
    return true;
}

char c;

bool alpha = false;

int main() {
    freopen("abbreviation.in", "r", stdin);
    freopen("abbreviation.out", "w", stdout);
    std::string word = "";
    while ((c = getchar()) != EOF) {
       bool flag = isalpha(c);
       if (flag != alpha && word != "") {
           words.push_back(word);
           word = "";
       }
       word += c;
       alpha = flag;
    }
    if (word != "") words.push_back(word);
    for (int i = 0, j; i < words.size(); i = j) {
        if (iscapital(words[i])) {
            for (j = i + 2; j < words.size(); j += 2) {
                if (words[j - 1] != " ") break;
                if (!iscapital(words[j])) break;
            }
            --j;
            if (i + 1 == j) {
                printf("%s", words[i].c_str());
            } else {
                for (int k = i; k < j; k += 2) {
                    printf("%c", words[k][0]);
                }
                printf(" (");
                for (int k = i; k < j; ++k) {
                    printf("%s", words[k].c_str());
                }
                printf(")");
            }
        } else {
            printf("%s", words[i].c_str());
            j = i + 1;
        }
    }
}