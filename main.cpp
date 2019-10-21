#include <iostream>
#include <glibmm.h>
#include <giomm.h>
#include <thread>
#include <utility>

using namespace std::literals;

int main(int argc, char** argv) 
{
    Gio::init();

    std::vector<Glib::VariantBase> grauds;

    grauds.push_back(Glib::Variant<bool>::create(false));
    grauds.push_back(Glib::Variant<bool>::create(false));
    grauds.push_back(Glib::Variant<bool>::create(false));
    grauds.push_back(Glib::Variant<bool>::create(false));
    std::cout << Glib::Variant<std::vector<Glib::VariantBase>>::create(grauds).print() << std::endl;
    //    [<false>, <false>, <false>, <false>]

    std::map<Glib::ustring, Glib::VariantBase> info 
    {
        {"address", Glib::Variant<std::string>::create("127.0.0.1")},
        {"port", Glib::Variant<uint16_t>::create(8080)},
    };

    std::map<Glib::ustring, Glib::VariantBase> props
    {
        {"name", Glib::Variant<std::string>::create("job")},
        {"grauds", Glib::Variant<std::vector<Glib::VariantBase>>::create(grauds)},
        {"ipv4", Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(info)}
    };

    auto obj = Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(props);
    auto tuple = Glib::VariantContainerBase::create_tuple(std::vector<Glib::VariantBase>
    {
        obj,
        Glib::Variant<bool>::create(true),
        Glib::Variant<int>::create(10899)
    });

    std::cout << tuple.print() << std::endl; 
    //    ({'grauds': <[<false>, <false>, <false>, <false>]>, 'ipv4': <{'address': <b'127.0.0.1'>, 'port': <uint16 8080>}>, 'name': <b'job'>}, true, 10899)
    
    
    
    std::cout << tuple.get_type_string() << std::endl;
    //    (a{sv}bi)


    return 0;
}
