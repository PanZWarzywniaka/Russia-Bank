#include "card.hpp"
#include "deck.hpp"
#include <stdexcept>
#include <memory>
#include <optional>

class Move
{
private:

    const std::shared_ptr<Deck> skad;
    std::shared_ptr<Deck> dokad;
    Card karta_w_reku;

public:

    Move() = delete;
    Move(const std::shared_ptr<Deck>, Card);
    Move(const std::shared_ptr<Deck> lhs, const std::shared_ptr<Deck> rhs, Card&&);//skąd, dokąd, co,
    //getery
    const std::shared_ptr<Deck> get_origin() const;
    const std::shared_ptr<Deck> get_destination() const;
    Card get_card() const;
    //setery
    void set_destination(std::shared_ptr<Deck>);
};
