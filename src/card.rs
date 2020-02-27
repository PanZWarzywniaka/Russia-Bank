
#[derive(Eq,PartialEq,PartialOrd,Ord)]
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

#[derive(PartialEq,Eq)]
pub enum CardColor {
    Hearts,
    Diamonds,
    Spades,
    Clubs //żołądź / trefl
}

impl CardColor {
    pub fn is_red(&self) -> bool {
        match self {
            CardColor::Hearts => true,
            CardColor::Diamonds => true,
            _ => false
        }
    }
    pub fn is_black(&self) -> bool {
        !self.is_red()
    }
}


pub struct Card {
    color : CardColor,
    value : CardValue
}

impl Card {
    pub fn is_red(&self) -> bool {
        self.color.is_red()
    }
    pub fn is_black(&self) -> bool {
        self.color.is_black()
    }
    pub fn covers_ace_stack(&self,cov:&Card) -> bool {
        if cov.color != self.color {
            return false
        }
        self.value < cov.value
    }
    pub fn covers_king_stack(&self,cov:&Card) -> bool {
        if cov.value < self.value || self.value == CardValue::A {
            return false
        }
        match cov.is_red() {
            true => self.is_black(),
            false => self.is_red()
        }
    }
}