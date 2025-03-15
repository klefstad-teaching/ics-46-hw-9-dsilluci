#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error for words " << word1 << " and " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const string &str1, const string &str2, int d) {
    return true;
}

bool is_adjacent(const string &word1, const string &word2) {
    return true;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    vector<string> ladder = {begin_word};
    vector<string> new_ladder;
    string last_word;
    queue<vector<string>> ladder_queue;
    ladder_queue.push(ladder);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        ladder = ladder_queue.front();
        ladder_queue.pop();
        last_word = ladder.back();
        for (auto word : word_list)
            if (is_adjacent(last_word, word))
                if (!visited.contains(word)) {
                    visited.insert(word);
                    new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
            }
    }
    return ladder; // no ladder found
}

void load_words(set<string> &word_list, const string &file_name) {
    cout << "load_words" << endl;
}

void print_word_ladder(const vector<string> &ladder) {
    for (auto s : ladder)
        cout << s << " ";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}