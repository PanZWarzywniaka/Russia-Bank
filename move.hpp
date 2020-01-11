#include"card.hpp"
#include"deck.hpp"
#include <stdexcept>

class Move
{
private:
    const Deck* skad; //skąd bierzemy karte
    const Deck* dokad;
    Card karta_w_reku;
public:

    Move() = delete;
    Move(const Deck*, const Deck*, Card&&);//skąd, dokąd, co,
    //getery
    const Deck* get_origin() const;
    const Deck* get_destination() const;
    Card get_card() const;
};
