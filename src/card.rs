
pub enum CardValue {
    A,
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
    K
}


pub enum CardColor {
    Hearts,
    Diamonds,
    Spades,
    Clubs //żołądź / trefl
}


pub struct Card {
    color : CardColor,
    value : CardValue
}