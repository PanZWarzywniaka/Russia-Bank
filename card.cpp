#include"card.hpp"

sf::Image Card::card_sheet = sf::Image();
sf::Vector2f Card::single_card_size = sf::Vector2f();

Card::Card(Value wart, Colour kol) // za każdym razem
{
    wartosc = wart;
    kolor = kol;
    
    const sf::Vector2i rect_positon = sf::Vector2i{single_card_size.x*static_cast<int>(wartosc),single_card_size.y*static_cast<int>(kolor)}; //zwróci {0,0} dla asa kier

    card_texture.loadFromImage(Card::card_sheet,sf::IntRect(rect_positon,static_cast<sf::Vector2i>(single_card_size)));
    card_sprite.setTexture(card_texture); //card sprite nie przechowuje tekstury tylko trzyma do niej wskaźnik, card_sheet nie powinno być kopiowane

    //skalowanie dla skali Game::scale = 1, rozmiar karty y=150
    float ratio = single_card_size.x/single_card_size.y;  //x/y ratio

    sf::Vector2f target_card_size(150*ratio,150); // x = 96.62 y = 150
    sf::Vector2f factor(target_card_size.x/single_card_size.x,target_card_size.y/single_card_size.y); // skala dla x i y taka sama 0.07666

    card_sprite.setScale(card_sprite.getScale().x*factor.x ,card_sprite.getScale().y*factor.y);
}


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


void Card::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(card_sprite,states);
}

void Card::setPosition(float x, float y)
{
    card_sprite.setPosition(x,y);
}