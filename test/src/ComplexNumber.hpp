#ifndef COMPLEXNUMBER_HPP_
#define COMPLEXNUMBER_HPP_

class ComplexNumber {

private:

    double m_a{0.0};
    double m_b{0.0};

public:

    ComplexNumber() noexcept :
        m_a{0.0}, m_b{0.0}
    {
    }

    ComplexNumber(double a) noexcept :
        m_a{a}, m_b{0.0}
    {
    }

    ComplexNumber(double a, double b) noexcept :
        m_a{a}, m_b{b}
    {
    }

    double getA() const noexcept
    {
        return m_a;
    }

    void setA(double a) noexcept
    {
        m_a = a;
    }

    double getB() const noexcept
    {
        return m_b;
    }

    void setB(double b)
    {
        m_b = b;
    }

    bool operator==(const ComplexNumber& other) const noexcept
    {
        return (getA() == other.getA()) && (getB() == other.getB());
    }

    bool operator!=(const ComplexNumber& other) const noexcept
    {
        return (getA() != other.getA()) || (getB() != other.getB());
    }

    ComplexNumber operator+(const ComplexNumber& other) const noexcept
    {
        return ComplexNumber(getA() + other.getA(), getB() + other.getB());
    }

    ComplexNumber operator+(double x) const noexcept
    {
        return *this + ComplexNumber(x, 0.0);
    }

    ComplexNumber operator*(const ComplexNumber& other) const noexcept
    {
        return ComplexNumber(getA() * other.getA() - getB() * other.getB(), getA() * other.getB() - getB() * other.getA());
    }

    ComplexNumber operator*(double x) const noexcept
    {
        return *this * ComplexNumber(x);
    }

};

ComplexNumber operator+(double x, const ComplexNumber& other) noexcept
{
    return ComplexNumber(x) + other;
}

ComplexNumber operator*(double x, const ComplexNumber& other) noexcept
{
    return ComplexNumber(x) * other;
}

#endif /* COMPLEXNUMBER_HPP_ */
