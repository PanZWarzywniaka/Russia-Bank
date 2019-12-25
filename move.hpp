#include"card.hpp"
#include <stdexcept>

class Move
{
private:
    const std::stack<Card>* skad; //skąd bierzemy karte
    const std::stack<Card>* dokad;
    Card karta_w_reku;
public:

    Move() = delete;
    Move(const std::stack<Card>*, const std::stack<Card>*, Card&&);//skąd, dokąd, co,
    //getery
    const std::stack<Card>* get_origin() const;
    const std::stack<Card>* get_destination() const;
    Card get_card() const;
};
