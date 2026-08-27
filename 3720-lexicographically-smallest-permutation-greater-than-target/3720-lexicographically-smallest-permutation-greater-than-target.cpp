class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++; // Store available character counts

        string result = "";
        int n = target.length();

        // 1. Try to find the longest matching prefix with the target
        int match_len = 0;
        while (match_len < n && count[target[match_len] - 'a'] > 0) {
            count[target[match_len] - 'a']--;
            match_len++;
        }

        // 2. Backtrack from the match point to find where we can pick a larger character
        for (int i = match_len; i >= 0; i--) {
            // Restore the character if we are moving leftward
            if (i < match_len) {
                count[target[i] - 'a']++;
            }

            if (i == n) continue; // Cannot exceed target length

            // Look for the next smallest available character strictly larger than target[i]
            for (int j = (target[i] - 'a') + 1; j < 26; j++) {
                if (count[j] > 0) {
                    // Found it! Construct the prefix
                    result = target.substr(0, i) + (char)('a' + j);
                    count[j]--;

                    // Fill all remaining slots with the smallest characters left
                    for (int k = 0; k < 26; k++) {
                        while (count[k] > 0) {
                            result += (char)('a' + k);
                            count[k]--;
                        }
                    }
                    return result;
                }
            }
        }

        return ""; // Return empty if no permutation can beat target
    }
};
