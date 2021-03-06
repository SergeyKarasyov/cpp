// when piecewise object construction is complicated, Builder provides and API for doing that succintly.
// FluentBuilder makes possible to add chaining for calls, i.e. make code more readable.
// For that we need function to return changed object

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
using namespace std;

class HtmlBuilder;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;
    HtmlElement() {}
    HtmlElement(const string &name, const string &text)
        : name{name},
          text{text}
    {
    }
    string str(int indent = 0) const
    {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;

        if (text.size() > 0)
        {
            oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
        }

        for (const auto &e : elements)
        {
            oss << e.str(indent + 1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
    static HtmlBuilder build(std::string root_name);
    static std::unique_ptr<HtmlBuilder> create(std::string root_name)
    {
        return std::make_unique<HtmlBuilder>(root_name);
    }
};

//builder class
struct HtmlBuilder
{
    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder &add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    HtmlBuilder *add_child_2(std::string child_name, std::string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }
    //in order to convert from builder to htmlelement
    operator HtmlElement() { return root; }
    HtmlElement root;

    std::string str() const
    {
        return root.str();
    }
};

HtmlBuilder HtmlElement::build(std::string root_name)
{
    return HtmlBuilder{root_name};
}

int main()
{

    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li1", "hello1").add_child("li2", "hello2");

    HtmlElement e = HtmlElement::build("ul").add_child("li1", "hello1").add_child("li2", "hello2");
    cout << builder.str() << endl;
    cout << e.str() << endl;
    auto ee = HtmlElement::create("ul")
                  ->add_child_2("li", "hello")
                  ->add_child_2("li", "world");

    std::cout << "Pointa" << std::endl;
    cout << ee->str() << endl;
}