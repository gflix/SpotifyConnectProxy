#ifndef CONTROLLERS_GENERICDESCRIPTOR_HPP_
#define CONTROLLERS_GENERICDESCRIPTOR_HPP_

class GenericDescriptor
{
public:
    GenericDescriptor(void);
    virtual ~GenericDescriptor();

    void close(void);

    int descriptor(void) const;
    bool isConnected(void) const;

protected:
    int m_descriptor;

    void resetDescriptor(void);
};

#endif /* CONTROLLERS_GENERICDESCRIPTOR_HPP_ */
