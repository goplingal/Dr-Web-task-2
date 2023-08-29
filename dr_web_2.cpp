#include <iostream>
#include <string>
#include <map>

template <class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};

template <class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};

template <class K>
class exception : public not_found_exception <K>
{
public:
    exception(K k) : key(k)
    {

    }
    const K& get_key() const noexcept override
    {
        return key;
    }
private:
    const K key;
};

template <class K, class V>
class my_dictionary : public dictionary <K, V>
{
public:
    ~my_dictionary() = default;
    void set (const K &k, const V &v) override
    {
        a[k] = v;
    }
    const V& get(const K &key) const override
    {
        auto i = a.find(key);
        if (i != a.end())
        {
            return i->second;
        }
        else
        {
            throw exception <K> (key);
        }
    }
    bool is_set(const K &key) const override
    {
        if (a.find(key) != a.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    std::map <K, V> a;
};

int main()
{
    my_dictionary <std::string, int> m;
    m.set("a", 1);
    m.set("b", 2);
    m.set("c", 3);
    m.set("d", 4);
    m.set("e", 5);
    std::cout << m.is_set("c") << std::endl;
    try
    {
        std::cout << m.get("x");
    }
    catch (exception <std::string> &e)
    {
        std::cout << e.get_key();
    }
    return 0;
}
