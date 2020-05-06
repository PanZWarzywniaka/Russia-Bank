#include"card.hpp"
#include"game.hpp"

sf::Vector2f Card::default_single_card_size = sf::Vector2f(); //przechowuje domyślny rozmiar karty
float Card::card_scale = 1.f; 
std::array<sf::Texture, 52> Card::texture_array;

Card::Card(Value val, Suit su, Colour col) // za każdym razem
{
    value = val;
    suit = su;
    colour = col;
    show_back = false;

    auto get_right_texture_addres = [val,su]() -> size_t{return 13*static_cast<int>(su)+static_cast<int>(val);};
    card_sprite.setTexture(Card::texture_array[get_right_texture_addres()]);
 
    //skalowanie dla skali Game::scale = 1, rozmiar karty y=150
    card_sprite.setScale(card_scale*Game::get_scale(),card_scale*Game::get_scale()); // skala dla x i y taka sama 0.07666
    card_sprite.setOrigin(Card::get_default_single_card_size().x*Game::get_scale()/2,Card::get_default_single_card_size().y*Game::get_scale()/2);
}


void Card::load_texuture() //wykona się raz dla całej klasy przed utworzeniem obietów
{
    sf::Image card_sheet;
    card_sheet.loadFromFile("resources/card_sheet.png");

    sf::Vector2f original_single_card_size = static_cast<sf::Vector2f>(card_sheet.getSize());
    original_single_card_size.x /=13; //dzielimy rozmiar przez 13 bo tyle jest kart w rzędzie
    original_single_card_size.y /= 4; //4 kart w kolumnie

    default_single_card_size = sf::Vector2f(150*(original_single_card_size.x/original_single_card_size.y),150); //x/y ratio
    Card::card_scale = default_single_card_size.x/original_single_card_size.x;


    //ładowanie wszystkich kart do tablicy
    size_t array_counter = 0;

    for(short kolor=0; kolor<4; ++kolor) //4 iteracje dla każdego koloru, każdy kolor to wiersz
    {
        for(short wartosc=0; wartosc<13; ++wartosc) //13 iteracji dla każdej wartości karty, każda wartość to kolumna
        {
            const sf::Vector2i rect_positon = sf::Vector2i{original_single_card_size.x*wartosc,original_single_card_size.y*kolor}; //zwróci {0,0} dla asa kier
            sf::Texture card_texture;
            card_texture.loadFromImage(card_sheet,sf::IntRect(rect_positon,static_cast<sf::Vector2i>(original_single_card_size)));
            card_texture.setSmooth(true);
            texture_array[array_counter] = card_texture;
            ++array_counter;
        }
    }
    
}

Card::Card(const Card& crd) //kopiujący
{
    value = crd.value;
    suit = crd.suit;
    card_sprite = crd.card_sprite;
    colour = crd.colour;
    show_back = crd.show_back;

    card_sprite.setOrigin(Card::get_default_single_card_size().x*Game::get_scale()/2,Card::get_default_single_card_size().y*Game::get_scale()/2);

}

Card::Card(Card&& crd) //przenoszący
{
    value = std::move(crd.value);
    suit = std::move(crd.suit);
    card_sprite = std::move(crd.card_sprite);
    colour = std::move(crd.colour);
    show_back = std::move(crd.show_back);

    card_sprite.setOrigin(Card::get_default_single_card_size().x*Game::get_scale()/2,Card::get_default_single_card_size().y*Game::get_scale()/2);

}


Card::Suit Card::get_suit() const
{
    return suit;
}


Card::Value Card::get_value() const
{
    return value;
}

void Card::rotate()
{
    if(show_back) //trzeba pokazać front
    {
        auto get_right_texture_addres = [this]() -> size_t{return 13*static_cast<int>(suit)+static_cast<int>(value);};
        card_sprite.setTexture(Card::texture_array[get_right_texture_addres()]);
    }
    else //trzeba pokazać rewers
    {
        switch (colour)
        {
            case Colour::blue:
                {
                    card_sprite.setTexture(Card::texture_array[52]);
                }
            break;
            case Colour::red:
                {
                    card_sprite.setTexture(Card::texture_array[53]);
                }
            break;
        
        default:
            throw std::runtime_error("Karta nie ma koloru");
            break;
        }
    }
    
    show_back = !show_back; //switching sides
}

bool Card::operator<(const Card& cx) const
{
    if(this->suit==cx.suit) 
    {
        return this->value<cx.value;
    }
    else return this->suit<cx.suit;
}

bool Card::operator==(const Card& card) const
{
    if(this->suit==card.suit&&this->value==card.value) return true;
        else return false;        
}

bool Card::is_black() const
{
    if(this->suit==Card::Suit::spades || this->suit==Card::Suit::clubs)
        return true;
    else
        return false;
}


void Card::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(card_sprite,states);
}


void Card::card_scaling(sf::Vector2u position)
{
    card_sprite.setPosition(position.x*Game::get_scale(),position.y*Game::get_scale());
    card_sprite.setScale(card_scale*Game::get_scale(),card_scale*Game::get_scale());
}

sf::Vector2f Card::get_default_single_card_size() 
{
    return default_single_card_size;
}

void Card::setPosition(float x, float y)
{
    card_sprite.setPosition(x,y);
}

void Card::setRotation(float angle)
{
    card_sprite.setRotation(angle);
}


std::ostream &operator<<(std::ostream& strumien,const Card& crd)
{
    auto pisz = [&](const char* a){
        strumien<<a<<' ';
    };

    switch (crd.get_suit())
    {
        case Card::Suit::spades:
            {
                pisz("pik");    
            }
            break;
        case Card::Suit::clubs:
            {
                pisz("trefl");    
            }
            break;
        case Card::Suit::hearths:
            {
                pisz("kier");    
            }
            break;
        case Card::Suit::dimonds:
            {
                pisz("karo");    
            }
            break;
        default:
            pisz("Halo coś coś się popsuło i nie było mnie słychać");
            break;
    }

    switch (crd.get_value())
    {
        case Card::Value::_2:
            pisz("2");
            break;
        case Card::Value::_3:
            pisz("3");
            break;
        case Card::Value::_4:
            pisz("4");
            break;
        case Card::Value::_5:
            pisz("5");
            break;
        case Card::Value::_6:
            pisz("6");
            break;
        case Card::Value::_7:
            pisz("7");
            break;
        case Card::Value::_8:
            pisz("8");
            break;
        case Card::Value::_9:
            pisz("9");
            break;
        case Card::Value::_10:
            pisz("10");
            break;
        case Card::Value::J:
            pisz("J");
            break;
        case Card::Value::Q:
            pisz("Q");
            break;
        case Card::Value::K:
            pisz("K");
            break;
        case Card::Value::Ace:
            pisz("As");
            break;
        default:
            pisz("Error");
            break;
    }

    return strumien;
}