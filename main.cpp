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

    Glib::VariantBase item;
    Glib::VariantIter itr(tuple);
    while(itr.next_value(item))
    {
        if (item.is_of_type(Glib::VARIANT_TYPE_DICTIONARY))
        {
            Glib::VariantBase item2;
            Glib::VariantIter itr2(item);
            while (itr2.next_value(item2))
            {
                auto pair = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(item2);
                auto name = Glib::VariantBase::cast_dynamic<Glib::Variant<std::string>>(pair.get_child(0)).get();
                auto value = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(pair.get_child(1)).get_child(); // Array 和 Dict 的项是放在某个容器内的？

                if (name == "grauds")
                {
                    std::cout << name << ":[";
                    if (value.is_of_type(Glib::VARIANT_TYPE_ARRAY))
                    {
                        auto arr = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(value);
                        for (int i=0;i<arr.get_n_children();i++)
                        {
                            auto tmp = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(arr.get_child(i));    // Array 和 Dict 的项是放在某个容器内的？
                            auto value = Glib::VariantBase::cast_dynamic<Glib::Variant<bool>>(tmp.get_child());
                            std::cout << value.get() << ',';
                        }
                    }
                    std::cout << ']';
                }
                else if (name == "ipv4")
                {
                    //...
                }
            }
        }
        else if (item.is_of_type(Glib::VARIANT_TYPE_BOOL)) //而为什么这些基本的没有呢？难道<>包裹的需要？
        {
            auto value = Glib::VariantBase::cast_dynamic<Glib::Variant<bool>>(item);
            std::cout << value.get() << ',';
        }
        else if (item.is_of_type(Glib::VARIANT_TYPE_INT32))
        {
            auto value = Glib::VariantBase::cast_dynamic<Glib::Variant<int32_t>>(item);
            std::cout << value.get() << ',';
        }
    }

    //还有一个需要说明的是调用  call_sync时， 参数是 Glib::VariantContainerBase::create_tuple()，字符串参数是用Glib::Variant<Glib::ustring>，不要用std::string ~ 恶心至极

    return 0;
}
