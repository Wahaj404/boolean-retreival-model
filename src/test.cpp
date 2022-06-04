#include "inverted_index.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using QueryTest = bool (*)(InvertedIndex const &);

bool gold1(InvertedIndex const &);
bool gold2(InvertedIndex const &);
bool gold3(InvertedIndex const &);
bool gold4(InvertedIndex const &);
bool gold5(InvertedIndex const &);
bool gold6(InvertedIndex const &);
bool gold7(InvertedIndex const &);
bool gold8(InvertedIndex const &);
bool gold9(InvertedIndex const &);
bool gold10(InvertedIndex const &);
bool gold11(InvertedIndex const &);
bool gold12(InvertedIndex const &);

bool self1(InvertedIndex const &);
bool self2(InvertedIndex const &);
bool self3(InvertedIndex const &);

bool match(std::vector<std::size_t> const &res,
           std::vector<std::size_t> const &ans) {
    if (res.size() != ans.size()) {
        return false;
    }
    for (std::size_t i = 0; i < res.size(); ++i) {
        if (res[i] + 1 != ans[i]) {
            return false;
        }
    }
    return true;
}

bool runTests(std::initializer_list<QueryTest> const &tests,
              InvertedIndex const &idx) {
    std::size_t passed = 0;
    for (auto test : tests) {
        assert(test(idx));
        passed += test(idx);
    }
    return passed == tests.size();
}

bool gold(InvertedIndex const &idx) {
    return runTests({gold1, gold2, gold3, gold4, gold5, gold6, gold7, gold8,
                     gold9, gold10, gold11, gold12},
                    idx);
}

bool self(InvertedIndex const &idx) {
    return runTests({self1, self2, self3}, idx);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> fnames(argv + 1, argv + argc);
    auto cut = [](std::string const &str) -> std::string {
        int i = str.find_first_of("/") + 1;
        int j = str.find_last_of(".");
        return str.substr(i, j - i);
    };
    std::sort(fnames.begin(), fnames.end(),
              [cut](std::string const &a, std::string const &b) -> bool {
                  return std::stoi(cut(a)) < std::stoi(cut(b));
              });
    InvertedIndex idx(fnames);
    assert(gold(idx));
    assert(self(idx));
    std::cout << "green\n";
}

bool gold1(InvertedIndex const &idx) {
    std::string q = "image AND restoration";
    std::vector<std::size_t> ans = {359, 375};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold2(InvertedIndex const &idx) {
    std::string q = "deep AND learning";
    std::vector<std::size_t> ans = {
        23,  24,  174, 175, 176, 177, 213, 245, 247, 250, 254, 258,
        267, 272, 273, 278, 279, 281, 325, 333, 345, 346, 347, 348,
        352, 357, 358, 360, 362, 371, 373, 374, 375, 380, 381, 382,
        396, 397, 401, 404, 405, 415, 421, 432, 444};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold3(InvertedIndex const &idx) {
    std::string q = "autoencoders";
    std::vector<std::size_t> ans = {187, 273, 279, 325, 333, 405};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold4(InvertedIndex const &idx) {
    std::string q = "temporal AND deep AND learning";
    std::vector<std::size_t> ans = {279, 358, 373, 405};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold5(InvertedIndex const &idx) {
    std::string q = "time AND series";
    std::vector<std::size_t> ans = {
        40,  54,  110, 111, 112, 113, 158, 163, 173, 180, 181, 202, 220, 237,
        238, 239, 240, 258, 277, 283, 295, 305, 350, 405, 421, 437, 438, 445};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold6(InvertedIndex const &idx) {
    std::string q = "time AND series AND classification";
    std::vector<std::size_t> ans = {40, 237, 283, 445};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold7(InvertedIndex const &idx) {
    std::string q = "time AND series OR classification";
    std::vector<std::size_t> ans = {
        4,   6,   9,   10,  16,  22,  24,  33,  34,  38,  40,  43,  45,  46,
        49,  51,  54,  55,  56,  58,  59,  60,  63,  64,  66,  67,  71,  73,
        75,  76,  77,  80,  84,  85,  94,  95,  98,  99,  106, 107, 110, 111,
        112, 113, 120, 121, 122, 123, 125, 126, 128, 140, 143, 147, 158, 163,
        164, 165, 167, 168, 169, 171, 173, 174, 175, 176, 177, 180, 181, 182,
        187, 193, 197, 198, 202, 208, 210, 213, 215, 220, 228, 229, 234, 235,
        236, 237, 238, 239, 240, 245, 247, 248, 249, 252, 256, 258, 259, 261,
        265, 268, 272, 273, 277, 280, 283, 286, 287, 289, 295, 299, 302, 303,
        305, 310, 313, 316, 317, 321, 327, 328, 334, 338, 341, 345, 348, 350,
        352, 353, 354, 357, 363, 369, 371, 375, 377, 378, 382, 384, 385, 386,
        387, 395, 397, 404, 405, 408, 420, 421, 424, 425, 427, 432, 437, 438,
        439, 442, 445};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold8(InvertedIndex const &idx) {
    std::string q = "pattern";
    std::vector<std::size_t> ans = {
        9,   10,  18,  21,  23,  26,  30,  34,  40,  50,  73,  118, 126,
        127, 139, 145, 148, 155, 180, 186, 189, 194, 201, 209, 214, 216,
        230, 231, 234, 238, 279, 280, 288, 326, 343, 350, 351, 368, 369,
        383, 394, 406, 412, 413, 424, 425, 429, 446, 447};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold9(InvertedIndex const &idx) {
    std::string q = "pattern AND clustering";
    std::vector<std::size_t> ans = {40, 73, 180, 216, 326, 350, 351, 413, 446};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold10(InvertedIndex const &idx) {
    std::string q = "pattern AND clustering AND heart";
    std::vector<std::size_t> ans = {73};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold11(InvertedIndex const &idx) {
    std::string q = "neural information /2";
    std::vector<std::size_t> ans = {26};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool gold12(InvertedIndex const &idx) {
    std::string q = "feature track /5";
    std::vector<std::size_t> ans = {13, 212};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool self1(InvertedIndex const &idx) {
    std::string q = "NOT pattern OR NOT clustering";
    std::vector<std::size_t> ans = {
        1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
        15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,
        29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  41,  42,  43,
        44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,
        58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
        72,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
        87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
        101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
        143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
        157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
        171, 172, 173, 174, 175, 176, 177, 178, 179, 181, 182, 183, 184, 185,
        186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
        200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
        214, 215, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
        229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
        243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256,
        257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270,
        271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284,
        285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298,
        299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 327,
        328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341,
        342, 343, 344, 345, 346, 347, 348, 349, 352, 353, 354, 355, 356, 357,
        358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371,
        372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385,
        386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
        400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 414,
        415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428,
        429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442,
        443, 444, 445, 447, 448};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool self2(InvertedIndex const &idx) {
    std::string q = "NOT deep OR NOT learning";
    std::vector<std::size_t> ans = {
        1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
        15,  16,  17,  18,  19,  20,  21,  22,  25,  26,  27,  28,  29,  30,
        31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
        45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,
        59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,
        73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,
        87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
        101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
        143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
        157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
        171, 172, 173, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188,
        189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202,
        203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 214, 215, 216, 217,
        218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231,
        232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 246,
        248, 249, 251, 252, 253, 255, 256, 257, 259, 260, 261, 262, 263, 264,
        265, 266, 268, 269, 270, 271, 274, 275, 276, 277, 280, 282, 283, 284,
        285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298,
        299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 326, 327,
        328, 329, 330, 331, 332, 334, 335, 336, 337, 338, 339, 340, 341, 342,
        343, 344, 349, 350, 351, 353, 354, 355, 356, 359, 361, 363, 364, 365,
        366, 367, 368, 369, 370, 372, 376, 377, 378, 379, 383, 384, 385, 386,
        387, 388, 389, 390, 391, 392, 393, 394, 395, 398, 399, 400, 402, 403,
        406, 407, 408, 409, 410, 411, 412, 413, 414, 416, 417, 418, 419, 420,
        422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 433, 434, 435, 436,
        437, 438, 439, 440, 441, 442, 443, 445, 446, 447, 448};
    auto res = idx.answerAsDocIDs(q);
    return match(res.getIDs(), ans);
}

bool self3(InvertedIndex const &idx) {
    std::string q = "";
    std::vector<std::size_t> ans = {};
    return true;
}