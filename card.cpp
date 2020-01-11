#include"card.hpp"

Card::Card(Value wart, Colour kol) // za każdym razem
{
    wartosc = wart;
    kolor = kol;
    
    card_sprite.setTexture(card_sheet); //card sprite nie przechowuje tekstury tylko trzyma do niej wskaźnik, card_sheet nie powinno być kopiowane

    const sf::Vector2i rect_positon = sf::Vector2i{single_card_size.x*static_cast<int>(wartosc),single_card_size.y*static_cast<int>(kolor)}; //zwróci {0,0} dla asa kier

    card_sprite.setTextureRect(sf::IntRect(rect_positon,static_cast<sf::Vector2i>(single_card_size))); //pierwsze dwa to rozmiar niezmienny
}

sf::Texture Card::card_sheet = sf::Texture();

void Card::load_texuture() //wykona się raz
{
    card_sheet.loadFromFile("Skany Kart/Docelowe/card_sheet.png");

    single_card_size = static_cast<sf::Vector2f>(card_sheet.getSize());
    single_card_size.x /=13; //dzielimy rozmiar przez 13 bo tyle jest kart w rzędzie
    single_card_size.y /= 4; //4 kart w kolumnie
}




Card::Card(const Card& karta)
{
    this->wartosc=karta.wartosc;
    this->kolor=karta.kolor;
    this->card_sprite=karta.card_sprite;
}

Card::Card(Card&& karta)
{
    wartosc = std::move(karta.wartosc);
    kolor = std::move(karta.kolor);
    card_sprite = std::move(karta.card_sprite);
}


Card::Colour Card::get_colour() const
{
    return kolor;
}


Card::Value Card::get_value() const
{
    return wartosc;
}

bool Card::operator<(const Card& cx) const
{
    if(cx.kolor>this->kolor)
    {
        return cx.wartosc>this->wartosc;
    }
    else return false;
}

bool Card::is_black() const
{
    if(this->kolor==Card::Colour::spades || this->kolor==Card::Colour::clubs)
        return true;
    else
        return false;
}


/*
sf::Vector2f Card::single_card_size(sf::View)
{
    return card_sprite.;
}
*/