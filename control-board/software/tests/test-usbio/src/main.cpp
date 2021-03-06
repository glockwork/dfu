
#include "usb_io.h"
#include "ctrlboard_io.h"

int main( int argc, char * argv[] )
{
    CtrlboardIo io;
    bool res = io.open();
    const int CNT = 64;
    unsigned char b[ CNT ];
    int cnt, cntr = 0;
    do {
    	b[0] = 1;
    	b[1] = 1;
    	int res;
    	cnt = io.gpio( 0, 1, res );
    	res = io.version();
        cnt = io.write( &b[0], 1 );
        cnt = io.write( &b[1], 1 );
        cntr += io.read( &b[2], 2 );
        cnt = io.write( &b[0], 1 );
        cnt = io.write( &b[1], 1 );
        cntr += io.read( &b[2], CNT );
        cnt = io.write( &b[0], 1 );
        cnt = io.write( &b[1], 1 );
        cntr += io.read( &b[2], CNT );
    } while ( cnt > 0 );
    //int v = io.version();
    io.close();
    return 0;
}




