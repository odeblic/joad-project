#include <utility>


template <typename T>
class Immutable
{
  public:

    template <typename ... Args>
    explicit Immutable(Args&& ...args)
    : object(std::forward<Args>(args)...)
    {
    }

    Immutable(const Immutable&) = delete;

    Immutable& operator=(const Immutable&) = delete;

    Immutable& operator=(const Immutable&&) = delete;

    ~Immutable() = default;

    operator T() const
    {
      return object;
    }

    const T& get() const
    {
      return object;
    }

  private:

    // TODO add reference counting to prevent object deletion before reading

    const T object;
};

