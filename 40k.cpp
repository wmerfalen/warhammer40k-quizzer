#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <functional>
#include <assert.h>
#include <fstream>

#define REGISTER_MINI(MINI_NAME) minis.emplace_back(mini::create(mini::MINI_NAME()));

namespace grammar {
    const char* example = "\n"
        "# Example miniature file\n"
        "########################\n"
        "\n"
        "# Any line starting with # is a comment\n"
        "#######################################\n"
        "\n"
        "
        "shrike {\n"
        "   movement: 14\n"
        "   weapon_skill: 2\n"
        "   balistic_skill: 2\n"
        "   strength: 4\n"
        "   toughness: 4\n"
        "   wounds: 6\n"
        "   attacks: 6\n"
        "   leadership: 9\n"
        "   save_roll: 3\n"

};

namespace mini {
    struct m {
        int movement;
        int weapon_skill;
        int balistic_skill;
        int strength;
        int toughness;
        int wounds;
        int attacks;
        int leadership;
        int save_roll;
        std::string model_name;
    };
    template <typename TMini> mini::m create(const TMini& mini){
        mini::m dest;
        dest.movement = mini.movement;
        dest.weapon_skill = mini.weapon_skill;
        dest.balistic_skill = mini.balistic_skill;
        dest.strength = mini.strength;
        dest.toughness = mini.toughness;
        dest.wounds = mini.wounds;
        dest.attacks = mini.attacks;
        dest.leadership = mini.leadership;
        dest.save_roll = mini.save_roll;
        dest.model_name = mini.model_name;
        return dest;
    }
    int import(std::string file_name){
        ifstream fp(file_name.c_str());
        if(!fp.is_open() || !fp.good()){
            return -1;
        }
        int count = 0;

    }
};

namespace quiz {
#define TQUIZ(item) \
    void what_is_ ##item(mini::m mini){\
        std::cout << "[QUIZ]::What is the " << #item << " skill for " << mini.model_name << "? -> "; \
        int expected = mini.item;\
        int answer = 0;\
        std::cin >> answer;\
        if(expected == answer){ std::cout << "***[[[ CORRECT ]]]***\n"; }\
        else{ std::cerr << "***[[[ WRONG ]]]***\n"; }\
    }

    TQUIZ(movement);
    TQUIZ(weapon_skill);
    TQUIZ(balistic_skill);
    TQUIZ(strength);
    TQUIZ(toughness);
    TQUIZ(wounds);
    TQUIZ(attacks);
    TQUIZ(leadership);
    TQUIZ(save_roll);

    void ask_random_skill_numbers(unsigned number_of_questions){
        std::vector<std::function<void(mini::m)>> questions = {
            [](mini::m in_mini) -> void {
                what_is_movement(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_weapon_skill(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_balistic_skill(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_strength(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_toughness(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_wounds(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_attacks(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_leadership(in_mini);
            },
            [](mini::m in_mini) -> void {
                what_is_save_roll(in_mini);
            }
        };
        std::vector<mini::m> minis;

        srand(88172364);
        for(unsigned i=number_of_questions; i > 0;--i){
            int random_number = rand() % questions.size();
            int mini_number = rand() % minis.size();
            questions[random_number](minis[mini_number]);
        }
    };
    int get_wound_roll(int weapon_str, int victim_toughness){
        if(weapon_str / 2 >= victim_toughness){
            return 2;
        }
        if(weapon_str > victim_toughness){
            return 3;
        }
        if(weapon_str == victim_toughness){
            return 4;
        }
        if(weapon_str < victim_toughness &&
                weapon_str * 2 > victim_toughness){
            return 5;
        }
        if(victim_toughness >= weapon_str * 2){
            return 6;
        }
        return 0;
    }

};

namespace unit_tests {
    void test_wound_rolls(){
#define W(expect,str,tough) assert(quiz::get_wound_roll(str,tough) == expect); std::cout << "[STR:" << str << "]::[TOUGH:" << tough << "]::[expect " << expect << ": " << quiz::get_wound_roll(str,tough) << "]\n";
        W(5,4,5);
        W(5,3,5);
        W(6,2,5);
        W(6,2,4);
        W(6,1,4);
        W(6,1,2);
    }

};

namespace quiz {
    void wound_rolls(){
        for(unsigned i = 10; i > 0;--i){
            int rand_1 = rand() % 6;
            int rand_2 = rand() % 6;
            std::cout << "Wound roll test\n"
                << "Weapon Strength: " << rand_1 << "\n"
                << "Victim Tough: " << rand_2 << "\n"
                << "What is the wound roll? -> " 
                ;
            int answer = 0;
            std::cin >> answer;
            if(answer == quiz::get_wound_roll(rand_1,rand_2)){
                std::cout << "***[ CORRECT ]***\n";
            }else{
                std::cout << "***[ WRONG ]***\n";
            }
        }
    }
};
int main(int argc,char** argv){
    srand(9812948);
    quiz::ask_random_skill_numbers(10);
    return 0;
}
