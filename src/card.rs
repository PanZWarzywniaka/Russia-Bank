
pub enum CardValue {
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _10,
    J,
    Q,
    K,
    A
}


pub enum CardColor {
    Clubs, //żołądź / trefl
    Diamonds,
    Hearts,
    Spades
}


pub struct Card {
    color : CardColor,
    value : CardValue
}