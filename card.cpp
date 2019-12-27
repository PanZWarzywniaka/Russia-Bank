#include"card.hpp"

Card::Card(Value wart, Colour kol)
{
    wartosc = wart;
    kolor = kol;
    
    card_sprite.setTexture(card_sheet); //card sprite nie przechowuje tekstury tylko trzyma do niej wskaźnik, card_sheet nie powinno być kopiowane

    sf::Vector2u card_sheet_size = card_sheet.getSize();
    card_sheet_size.x /=13; //dzielimy rozmiar przez 13 bo tyle jest kart w rzędzie
    card_sheet_size.y /= 4; //4 kart w kolumnie

    const sf::Vector2i rect_positon = sf::Vector2i{card_sheet_size.x*static_cast<int>(wartosc),card_sheet_size.y*static_cast<int>(kolor)}; //zwróci {0,0} dla asa kier

    card_sprite.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(card_sheet_size),rect_positon)); //pierwsze dwa to rozmiar niezmienny
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

void Card::load_texuture()
{
    card_sheet.loadFromFile("/home/olek/Projekty/Russian-Bank/Skany Kart/Docelowe/card_sheet.png");
}