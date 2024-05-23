#include "text.h"
#include <unordered_map>

void translit(QString& string) {
    static const std::unordered_map<std::string, std::string> replaced_chars = {
        {"й", "j"},
        {"ц", "c"},
        {"у", "u"},
        {"к", "k"},
        {"е", "e"},
        {"н", "n"},
        {"г", "g"},
        {"ш", "sh"},
        {"щ", "shch"},
        {"з", "z"},
        {"ъ", "ie"},
        {"ф", "f"},
        {"ы", "y"},
        {"в", "v"},
        {"а", "a"},
        {"п", "p"},
        {"р", "r"},
        {"о", "o"},
        {"л", "l"},
        {"д", "d"},
        {"ж", "zh"},
        {"э", "e"},
        {"я", "ya"},
        {"ч", "ch"},
        {"с", "s"},
        {"м", "m"},
        {"и", "i"},
        {"т", "t"},
        {"ь", "io"},
        {"б", "b"},
        {"ю", "yu"},
        {"ё", "yo"},
        {"х", "h"}
    };
    for (auto const& replaced_char : replaced_chars) {
        string = string.replace(QString::fromStdString(replaced_char.first), QString::fromStdString(replaced_char.second));
    }
}
