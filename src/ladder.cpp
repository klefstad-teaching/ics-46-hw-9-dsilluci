#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error for words " << word1 << " and " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const string &str1, const string &str2, int d) {
    // i dont get d param for auto grader, im just going to calculate here and figure it out
    d = str1.size() - str2.size();
    if (d > 1 || d < -1)
        return false;
    else if (d == 0) {
        int diff_count = 0;
        // if d is 0, they are the same size. so diff count must be 1 to be neighbors
        for (int i = 0; i < str1.size(); ++i)
            if (str1[i] != str2[i])
                ++diff_count;
        return diff_count < 2 ? true : false;
    }
    // if d is -1 or 1, they are diff size. to be neighbors, one character is added or removed.
    // if d is -1, a character is added to str1 to get to str2.
    else if (d == -1) {
        // We can iterate through str2 until we see a mismatch. A mismatch means that we are at the removed
        // character in str1, so we skip it. If beyond this point we find another mismatch, they are not neighbors.
        int i = 0, j = 0;
        while (i < str1.size() && j < str2.size()) {
            if (str1[i] != str2[j++])
                continue;
            ++i;
        }
        if (j != str2.size() && j == i) return true;
        // if j - i != 1, then there was not only one mismatch
        return j - i == 1 ? true : false;
    }
    else {
        // same, but a character is added to str1 to get to str2.
        // we can just treat this backwards to get a very similar process to before
        int i = 0, j = 0;
        while (j < str1.size() && i < str2.size()) {
            if (str2[i] != str1[j++])
                continue;
            ++i;
        }
        if (j != str1.size() && j == i) return true;
        return j - i == 1 ? true : false;
    }
}

bool is_adjacent(const string &word1, const string &word2) {
    int size_difference = word1.size() - word2.size();
    return edit_distance_within(word1, word2, size_difference);
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
    return {"NO_LADDER_FOUND"};
}

void load_words(set<string> &word_list, const string &file_name) {
    string word;
    ifstream in(file_name);
    while (in >> word)
        word_list.insert(word);
}

void print_word_ladder(const vector<string> &ladder) {
    if (ladder.size() == 0 || ladder[0] == "NO_LADDER_FOUND")
        cout << "No word ladder found.";
    else {
    cout << "Word ladder found: ";
    for (auto s : ladder)
        cout << s << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}