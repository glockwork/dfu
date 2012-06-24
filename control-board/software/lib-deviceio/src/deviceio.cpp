
#include "deviceio.h"

inline static bool LSB()
{
    int i = 1;
    unsigned char * p = reinterpret_cast<unsigned char *>( &i );
    bool res = (p[0] != 0);
    return res;
}

inline static int toUInt16( unsigned char d[] )
{
    int res;
    if ( LSB() )
        res = (static_cast<int>( d[0] ) << 8) + d[1];
    else
        res = (static_cast<int>( d[1] ) << 8) + d[0];
    return res;
}

DeviceIo::DeviceIo()
: UsbIo()
{
}

DeviceIo::~DeviceIo()
{
}

int  DeviceIo::version()
{
    execFunc( FUNC_VERSION );
    unsigned char d[2];
    int sz = readQueue( d, 2 );
    if ( sz < 2 )
        return -1;
    int res = 256 * d[0] + d[1];
    return res;
}

bool DeviceIo::gpioConfig( int index, int pins, int mode )
{
    putUInt8( static_cast<unsigned char>( index ) );
    putUInt16( static_cast<unsigned short>( pins ) );
    putUInt16( static_cast<unsigned short>( mode ) );
    execFunc( FUNC_GPIO_CONFIG );
    return true;
}

bool DeviceIo::gpioSet( int index, int pins, int vals )
{
    putUInt8( static_cast<unsigned char>( index ) );
    putUInt16( static_cast<unsigned short>( pins ) );
    putUInt16( static_cast<unsigned short>( vals ) );
    execFunc( FUNC_GPIO_SET );
    return true;
}

bool DeviceIo::gpio( int index, int pins, int & vals )
{
    putUInt8( static_cast<unsigned char>( index ) );
    execFunc( FUNC_GPIO );
    unsigned char d[2];
    int sz = readQueue( d, 2 );
    if ( sz < 2 )
        return false;
    vals = 256 * d[0] + d[1];
    return true;
}

bool DeviceIo::adcEnable( int pins )
{
    /*putUInt8( 0, static_cast<unsigned char>( index ) );
    putUInt8( 1, val ? 1 : 0 );
    execFunc( CMD_ADC_ENABLE );*/
    return true;
}

bool DeviceIo::adc( std::basic_string<int> & vals )
{
    /*putUInt8( 0, static_cast<unsigned char>( index ) );
    execFunc( CMD_ADC );
    int sz = queueSize();
    unsigned char d[2];
    int cnt = readQueue( d, 2 );
    if ( cnt < 2 )
        return -1;
    int res = toUInt16( d );
    return res;*/
    return 1;
}


bool DeviceIo::twiEnable( bool val )
{
    return true;
}

bool DeviceIo::twiSetAddress( int addr )
{
    return true;
}

bool DeviceIo::twiSetSpeed( int val )
{
    return true;
}

bool DeviceIo::twiWriteRead( int addr, TIo wr, TIo & rd )
{
    return true;
}






